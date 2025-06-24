# [Inteli] Laboratório de Post-Quantum Cryptography - Open Quantum Safe

Nesse laboratório iremos conhecer e explorar a biblioteca Open Quantum Safe (liboqs) (https://github.com/open-quantum-safe/liboqs), uma iniciativa promissora da Linux Foundation. A implementação de criptografia é uma atividade sensível, para isso, a indústria costuma utilizar módulos criptográficos implementados cuidadosamente por especialistas. 

O programa Cryptographic Module Validation Program (CMVP) (https://csrc.nist.gov/Projects/cryptographic-module-validation-program), um esforço conjunto do NIST e do Canadian Centre for Cyber Security, tem como objetivo analisar módulos criptográficos implementados para verificar se atendem aos padrões rígidos de segurança determinados nas FIPS. Módulos pós-quânticos ainda não começaram a ser avaliados, porém, várias iniciativas já estão se preparando. 

Conheça algumas iniciativas: 

- liboqs (https://github.com/open-quantum-safe/liboqs)
- pqcrypto (https://pqcrypto.org/)
- pqclean (https://github.com/PQClean/PQClean)

Nessa prática, utilizaremos a liboqs.

# Instalação

A instalação da biblioteca liboqs não é uma atividade trivial, para isso, abaixo segue a sugestão de um método facilitado. 

### 0. Dependências Comuns

Baixe e instale o Git e o Python.

### 1. Visual Studio e MSVC

Precisamos de um compilador para C e C++, como o Microsoft C/C++ Compiler (MSVC), que está disponível de forma nativa no Visual Studio.

1. Baixe e instale o Visual Studios (https://visualstudio.microsoft.com/pt-br/vs/community).

*Lembre-se de adicionar ao PATH na instalação. 

### 2. CMake

O CMake é uma ferramenta de automação de construção de software. Ele não compila diretamente o código, mas é responsável por gerar os arquivos de configuração necessários para que sistemas de build (como Ninja, Make ou até o próprio Visual Studio) possam compilar o código-fonte.

1. Baixe e instale o CMake (https://cmake.org/download/).

*Lembre-se de instalar todos os módulos associados a C/C++ no instalador, além de adicionar ao PATH. 

### 3. Ninja

O Ninja é um sistema de build simples, rápido e eficiente, projetado para automatizar a compilação de software, especialmente em projetos grandes e complexos.

1. Baixe a release do Ninja (https://github.com/ninja-build/ninja/releases/tag/v1.12.1).

2. Crie uma pasta chamada ninja em algum local do seu computador e coloque o arquivo ninja.exe dentro. 

3. Abra o editor de variáveis de sistema e adicione ao PATH do usuário e do sistema o caminho da pasta onde o executável baixado está. 

### 4. Open Quantum Safe

Clone o repositório do projeto

```bash
git clone -b main https://github.com/open-quantum-safe/liboqs.git
cd liboqs
```

Crie um diretório de build dentro do projeto:

```bash
mkdir build
cd build
```

Abra o terminal x64 Native Tools, disponibilizado após a instalação do Visual Studio. 

Vá até o diretório build criado. Por exemplo:

```bash
cd C:\liboqs\build
```

Na pasta build, execute o CMake.

```bash
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=cl ..
```

Execute o comando abaixo para compilar a biblioteca

```bash
ninja
```

*Alguns problemas comuns estão associados com a presença de outros compiladores, como o MinGW. Para isso, retire as variáveis associadas a esses compiladores do PATH. 

Se quiser testar a biblioteca, baixe o pytest (substitua pelo caminho correto):

```bash
C:\Users\nomeusuario\AppData\Local\Programs\Python\Python313\python.exe -m pip install pytest pytest-xdist pyyaml
```

E execute os testes no diretório build:


```bash
ninja run_tests
```



# Uso

# Build c/ CMake

```sh
mkdir -p build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
```

Importe a biblitoeca no seu programa da seguinte forma:

#include "oqs/oqs.h"

Para compilar faça na x64 Native Tools, utilizando o caminho correto:

```bash
cl teste.cpp /I"C:\liboqs\build\include" /link "C:\liboqs\build\lib\oqs.lib" advapi32.lib
``` 

Além de referenciar a liboqs, usamos a advapi32.lib para o suporte à geração de números aleatórios seguros no Windows.

# Prática

#### 1. Descreva as dificuldades encontradas na instalação da biblioteca. 

#### 2. Tire um print da biblioteca em funcionamento. 

#### 3. Analise o programa alice_kem.cpp. Observe que existem lugares para comentários demarcados como blocos n. Junto com seu grupo, coloque um comentário em cada uma dessas marcações descrevendo o que o trecho do programa está fazendo. 

#### 4. Modifique o programa para o ML-KEM operar com chaves de 1024 bits. 

#### 5. Faça o programa bob_kem.cpp (Encapsulamento). Ele deve gerar uma pré-chave simétrica e encriptá-la utilizando a chave pública gerada e disponbilizada por Alice, gerando um encriptado. Saída: chave às claras e chave encriptada. 

#### 6. Faça o programa alice2_kem.cpp (Desencapsulamento). O programa deve receber o encriptado de Bob, e através da chave privada obter a chave simétrica compartilhada. Saída: chave às claras.

#### 7. Verifique se o processo foi feito corretamente. A chave às claras do programa bob_kem.cpp deve dar match com as chave às claras do programa alice2_kem.cpp

#### 8. Após a pré-chave ser combinada, pesquise e escolha um método para gerar uma chave de maneira segura e de tamanho adequado para o uso no AES. Implemente um programa em Python (não em C) que leia o segredo compartilhado, gere uma chave para o AES e use-o através de alguma lib em Python (ex: PyCryptodome, como mostrada na aula passada). Garanta o funcionamento.

#### EXTRA. Crie um programa alice_signature.cpp que leia qualquer tipo de arquivo, gere o conjunto de chaves, assine usando o algoritmo pós-quântico ML-DSA. A saída deverá ser as chaves e a hash do arquivo assinado. Crie um porgrama bob_signature que verifique a assiantura utilizando a chave pública. 
