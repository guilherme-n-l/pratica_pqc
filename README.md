# Laboratório de Post-Quantum Cryptography - Open Quantum Safe

Nesse laboratório iremos conhecer e explorar a biblioteca Open Quantum Safe (liboqs) (https://github.com/open-quantum-safe/liboqs), uma iniciativa promissora da Linux Foundation. A implementção de criptografia é uma atividade sensível, para isso, a indústria costuma utilizar módulos criptográficos implementados cuidadosamente por especialistas. 

O programa Cryptographic Module Validation Program (CMVP) (https://csrc.nist.gov/Projects/cryptographic-module-validation-program), um esforço conjunto do NIST e do Canadian Centre for Cyber Security, tem como objetivo analisar módulos criptográficos implementados para verificar se atendem aos padrões rígidos de segurança determinados nas FIPS. Módulos pós-quânticos ainda não começaram a ser avaliados, porém, várias iniciativas já estão se preparando. 

Conheça algumas iniciativas: 

- liboqs (https://github.com/open-quantum-safe/liboqs)
- pqcrypto (https://pqcrypto.org/)
- pqclean (https://github.com/PQClean/PQClean)

Nessa prática, utilizaremos a liboqs.

# Instalação

### 1. Visual Studio e MSVC

Precisamos de um compilador para C e C++, como o Microsoft C/C++ Compiler (MSVC), que está disponível de forma nativa no Visual Studio.

1. Baixe e instale o Visual Studios (https://visualstudio.microsoft.com/pt-br/vs/community).

*Lembre-se de instalar todos os módulos associados a C/C++ no instalador, além de adicionar ao PATH. 

### 2. CMake

Precisamos do CMake para configurar o projeto e criar os arquivos de build, ele não compila diretamente o código, mas é responsável por gerar os arquivos de configuração necessários para que sistemas de build possam compilar o código-fonte. Lembre-se de adicionar ao PATH na instalação. 

### 2. Ninja









