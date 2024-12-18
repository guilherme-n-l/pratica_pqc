# Laboratório de Post-Quantum Cryptography - Open Quantum Safe

Nesse laboratório iremos conhecer e explorar a biblioteca Open Quantum Safe (liboqs) (https://github.com/open-quantum-safe/liboqs), uma iniciativa promissora da Linux Foundation. A implementção de criptografia é uma atividade sensível, para isso, a indústria costuma utilizar módulos criptográficos implementados cuidadosamente por especialistas. 

O programa Cryptographic Module Validation Program (CMVP) (https://csrc.nist.gov/Projects/cryptographic-module-validation-program), um esforço conjunto do NIST e do Canadian Centre for Cyber Security, tem como objetivo analisar módulos criptográficos implementados para verificar se atendem aos padrões rígidos de segurança determinados nas FIPS. Módulos pós-quânticos ainda não começaram a ser avaliados, porém, várias iniciativas já estão se preparando. 

Conheça algumas iniciativas: 

- liboqs (https://github.com/open-quantum-safe/liboqs)
- pqcrypto (https://pqcrypto.org/)
- pqclean (https://github.com/PQClean/PQClean)

Nessa prática, utilizaremos a liboqs.

# Instalação

A instalação da biblioteca liboqs não é uma atividade trivial, para isso, abaixo segue a sugestão de um método facilitado. 

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

3. Abra o editor de variáveis de sistema 

![image](https://github.com/user-attachments/assets/28fbedc8-b826-40d9-899e-89cc6f418ea0)

# Exercícios

### Exercício 1 













