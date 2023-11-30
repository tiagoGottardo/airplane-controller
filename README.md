# airplane-controller
Um simulador de inteligência artificial para gerenciamento de tráfego aéreo.

## Dependências para compilar o programa
Para rodar o projeto estamos utilizando
- [gcc](https://gcc.gnu.org/releases.html)
- [cmake](https://cmake.org/download/)
- [make](https://www.gnu.org/software/make/)

A intalação pode variar de acordo com o sistama operacional que você estiver utilizando, no windows pode ser feita com:
```sh
choco install cmake.install --version=3.13.1
choco install make
```

### Verifique se tudo está instalado corretamente
```sh
gcc --version
make --version
cmake --version
```

### Adicione crun como alias
No arquivo de configuração do seu terminal adicione o alias:
#### windows
~~~sh
alias crun='clear; cd build; cmake -G "MinGW Makefiles" .. > /dev/null; make > /dev/null; cd ..; ./build/AirplaneController.exe'
~~~
#### linux
~~~sh
alias crun='clear; cd ./build; cmake .. > /dev/null; make > /dev/null; cd ../; ./build/AirplaneController'
~~~
### MemTest
```sh
clear; cd ./build; cmake .. > /dev/null; make >/dev/null; cd ../; valgrind --leak-check=full ./build/AirplaneController
```

### Contribuição com o projeto
Para adicionar qualquer biblioteca é só adicionar o arquivo .c em /src e o arquivo .h em /include

