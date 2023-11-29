#include "../include/interface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void MostrarComandos() {
    printf("\n");
    printf(" - reiniciar\n");
    printf(" - voltar\n");
    printf(" - pistas(quantidade)\n");
    printf(" - insere_aviao(pista, codigo, modelo, destino, distancia, tempo de voo)\n");
    printf(" - decolar(pista)\n");
    printf(" - tempestade(minuto)\n");
    printf(" - turbulencia(minuto)\n");
    printf(" - neblina(minuto)\n");
    printf(" - iniciasimulacao(minutos)\n");
    printf("\n");
    return;
}

void Cli() {
  char input[128];

  printf("========================== Aeroporto ==========================\n");
  printf("\nDigite 'ajuda' para conhecer todos os comandos.\n\n");

  while (1) {
    int numElementos;
    char **elementos;

    printf("Comando: ");
    scanf(" %[^\n]", input);

    if (!strcmp(input, "ajuda")) {
        MostrarComandos();
    } else if (!strcmp(input, "reiniciar")) {
      system("clear");
      Finaliza();
      Cli(); return;
    } else if (!strcmp(input, "voltar")) {
      system("clear");
      Finaliza();
      IniciaInterface(); return;
    } else if (strcmp(input, "\n")) {
      SeparaElementos(input, &elementos, &numElementos);
      ChamaFuncoes(elementos, numElementos);
    }
  }

}

void IniciaInterface() {
  char input[128];
  
  while(1) {

    printf("================== Simulador de tráfego aéreo =================\n\n");
    printf("Importar um (a)rquivo | Digitar comandos (m)anualmente [a, m]:");
    
    scanf(" %[^\n]", input);  
    initLogFile();

    system("clear");
  
    switch(input[0]) {
      case 'a': LeArquivo(); break;
      case 'm': Cli(); break;
    }

  }
}
