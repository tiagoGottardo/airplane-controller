#include "../include/interface.h"
#include <stdio.h>
#include <string.h>

void printajuda() {
    printf("Ajuda");
    return;
}

void inputcli() {
  char input[128];

  printf("Digite os inputs\n");
  printf("Digite ? para ser listado os inputs possíveis\n");

  fflush(stdin);

  while (1) {
    int numElementos;
    char **elementos;

    fgets(input, sizeof(input), stdin);

    if (!strcmp(input, "ajuda\n")) {
        printajuda();
    } else if (!strcmp(input, "reiniciar\n")) {
      inputcli();
      return;
    } else if(strcmp(input, "\n")){
      SeparaElementos(input, &elementos, &numElementos);
      ChamaFuncoes(elementos, numElementos);
    }
  }
}

void interface() {
  int input;
  printf("Simulador de controle de tráfego aereo - INTERFACE\n");
  printf("1- Usar arquivo como entrada\n");
  printf("2- Digitar entrada\n");
  scanf("%i", &input);
  initLogFile();

  if (input == 1) {
    LeArquivo();
  } else if (input == 2) {
    inputcli();
  } else {
    printf("ERRO: entrada invalida");
    return;
  }
}