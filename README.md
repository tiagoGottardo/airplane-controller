# airplane-controller
Um simulador de inteligência artificial para gerenciamento de tráfego aéreo.

Para rodar o repositório, precisamos do:
- gcc
- cmake
- make

No Linux, provavelmente tudo já está instalado por padrão, mas qualquer coisa só rodar sudo apt-get install.
No Windows, vocês já tem o MinGW, então precisa instalar os outros com esse comandos: 

- choco install cmake.install --version=3.13.1
- choco install make

Para ver se tudo está instalado corretamente:
gcc --version
make --version
cmake --version

Agora só adicionar esse alias no .bashrc e gg

alias crun='clear; cd build; cmake -G "MinGW Makefiles" .. > /dev/null; make > /dev/null; cd ..; ./build/AirplaneController.exe'
Rodando no windows
 
alias crun='clear; cd ./build; cmake .. > /dev/null; make > /dev/null; cd ../; ./build/AirplaneController'
Rodando no linux

Para adicionar qualquer biblioteca é só adicionar o arquivo .c em /src e o arquivo .h em /include
