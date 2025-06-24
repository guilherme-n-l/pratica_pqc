import os
import paho.mqtt.client as mqtt
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

BROKER = "localhost"
PORT = 1883
TOPIC = "test/topic"


def load_key():
    with open("key.hex", "r") as f:
        key_hex = f.read().strip()
    key = bytes.fromhex(key_hex)
    if len(key) != 32:
        raise ValueError("AES key must be 32 bytes (256 bits) long")
    return key


aes_key = load_key()
aesgcm = AESGCM(aes_key)


def encrypt_message(plaintext: str) -> bytes:
    nonce = os.urandom(12)
    ciphertext = aesgcm.encrypt(nonce, plaintext.encode(), None)
    return nonce + ciphertext


def decrypt_message(data: bytes) -> str:
    nonce = data[:12]
    ciphertext = data[12:]
    plaintext = aesgcm.decrypt(nonce, ciphertext, None)
    return plaintext.decode()


def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe(TOPIC)
    print(f"Subscribed to topic: {TOPIC}")


def on_message(client, userdata, msg):
    try:
        decrypted = decrypt_message(msg.payload)
        print(f"Received (decrypted) on {msg.topic}: {decrypted}")
    except Exception as e:
        print(f"Failed to decrypt message: {e}")


def main():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(BROKER, PORT, 60)
    client.loop_start()

    try:
        while True:
            msg = input("Enter message to publish (or 'exit' to quit): ")
            if msg.lower() == "exit":
                break
            encrypted_msg = encrypt_message(msg)
            client.publish(TOPIC, encrypted_msg)
    except KeyboardInterrupt:
        pass
    finally:
        client.loop_stop()
        client.disconnect()
        print("Disconnected from MQTT broker.")


if __name__ == "__main__":
    main()
