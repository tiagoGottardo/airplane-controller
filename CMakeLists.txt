cmake_minimum_required(VERSION 3.10)
project(AirplaneController)

set(CMAKE_INSTALL_MESSAGE NEVER)

# Adiciona todos os arquivos fonte do diretório src
file(GLOB SOURCES "src/*.c")

# Adiciona todos os arquivos de cabeçalho do diretório include
file(GLOB HEADERS "include/*.h")

# Adiciona os diretórios de inclusão
include_directories(include)

# Cria o executável
add_executable(AirplaneController ${SOURCES} ${HEADERS})
