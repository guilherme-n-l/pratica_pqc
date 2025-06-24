#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "oqs/kem.h"

uint8_t *read_from_file(const char *filename, size_t *length) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t *data = (uint8_t *)malloc(*length);
    if (!data) {
        perror("malloc failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (fread(data, 1, *length, file) != *length) {
        perror("Erro ao ler arquivo");
        fclose(file);
        free(data);
        exit(EXIT_FAILURE);
    }
    fclose(file);
    return data;
}


void write_to_file(const char *filename, const uint8_t *data, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }
    fwrite(data, 1, length, file);
    fclose(file);
}

void print_hex(const char *label, const uint8_t *data, size_t length) {
    printf("%s: ", label);
    for (size_t i = 0; i < length; i++) {
        printf("%02X", data[i]);
        if ((i + 1) % 16 == 0) printf("\n\t");
    }
    printf("\n");
}

uint8_t hex_char_to_int(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return c - 'a' + 10;
    if ('A' <= c && c <= 'F') return c - 'A' + 10;
    return 0;
}

uint8_t* hexstr_to_bytes(const char* hexstr, size_t* out_len) {
    size_t len = strlen(hexstr);
    if (len % 2 != 0) {
        fprintf(stderr, "Tamanho de string hex inválido\n");
        return NULL;
    }
    *out_len = len / 2;
    uint8_t* bytes = (uint8_t *)malloc(*out_len);
    if (!bytes) {
        perror("malloc failed");
        return NULL;
    }
    for (size_t i = 0; i < *out_len; i++) {
        bytes[i] = (hex_char_to_int(hexstr[2*i]) << 4) | hex_char_to_int(hexstr[2*i + 1]);
    }
    return bytes;
}

int main() {
    printf("=== Bob: Leitura do Segredo Compartilhado de key.hex ===\n");

    const char *kem_alg = OQS_KEM_alg_ml_kem_512;
    OQS_KEM *kem = OQS_KEM_new(kem_alg);
    if (!kem) {
        fprintf(stderr, "Erro ao inicializar o KEM.\n");
        return EXIT_FAILURE;
    }

    size_t key_hex_len;
    uint8_t *key_hex_data = read_from_file("key.hex", &key_hex_len);
    if (!key_hex_data) {
        OQS_KEM_free(kem);
        return EXIT_FAILURE;
    }

    char *key_hex_str = (char *)malloc(key_hex_len + 1);
    if (!key_hex_str) {
        perror("malloc failed");
        free(key_hex_data);
        OQS_KEM_free(kem);
        return EXIT_FAILURE;
    }
    memcpy(key_hex_str, key_hex_data, key_hex_len);
    key_hex_str[key_hex_len] = '\0';
    free(key_hex_data);

    size_t shared_secret_len;
    uint8_t *shared_secret = hexstr_to_bytes(key_hex_str, &shared_secret_len);
    free(key_hex_str);
    if (!shared_secret) {
        fprintf(stderr, "Falha ao converter hex para bytes.\n");
        OQS_KEM_free(kem);
        return EXIT_FAILURE;
    }

    if (shared_secret_len != kem->length_shared_secret) {
        fprintf(stderr, "Tamanho do segredo compartilhado inválido: esperado %zu, obtido %zu\n",
                kem->length_shared_secret, shared_secret_len);
        free(shared_secret);
        OQS_KEM_free(kem);
        return EXIT_FAILURE;
    }

    print_hex("Segredo compartilhado (lido de key.hex)", shared_secret, shared_secret_len);

    size_t public_key_len;
    uint8_t *public_key = read_from_file("public_key.bin", &public_key_len);
    if (!public_key) {
        free(shared_secret);
        OQS_KEM_free(kem);
        return EXIT_FAILURE;
    }

    if (public_key_len != kem->length_public_key) {
        fprintf(stderr, "Erro: Tamanho da chave pública inválido.\n");
        free(public_key);
        free(shared_secret);
        OQS_KEM_free(kem);
        return EXIT_FAILURE;
    }

    uint8_t *ciphertext = (uint8_t *)malloc(kem->length_ciphertext);
    if (!ciphertext) {
        perror("malloc failed");
        free(public_key);
        free(shared_secret);
        OQS_KEM_free(kem);
        return EXIT_FAILURE;
    }

    if (OQS_KEM_encaps(kem, ciphertext, shared_secret, public_key) != OQS_SUCCESS) {
        fprintf(stderr, "Erro ao encapsular o segredo.\n");
        free(ciphertext);
        free(public_key);
        free(shared_secret);
        OQS_KEM_free(kem);
        return EXIT_FAILURE;
    }

    write_to_file("ciphertext.bin", ciphertext, kem->length_ciphertext);
    write_to_file("shared_secret_bob.bin", shared_secret, kem->length_shared_secret);

    printf("[INFO] Dados gerados:\n");
    print_hex("Ciphertext", ciphertext, kem->length_ciphertext);
    print_hex("Segredo compartilhado (Bob)", shared_secret, kem->length_shared_secret);

    printf("[INFO] Arquivos gerados:\n");
    printf("  - ciphertext.bin\n");
    printf("  - shared_secret_bob.bin\n");

    free(public_key);
    free(ciphertext);
    free(shared_secret);
    OQS_KEM_free(kem);

    return EXIT_SUCCESS;
}
