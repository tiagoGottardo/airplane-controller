#include "../include/interface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void MostrarComandos() {
    printf("\n");
    printf(" - ver\n");
    printf(" - limpar\n");
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
  printf(" ==================================================== ✈️  ");
  printf("Aeroporto");
  printf(" 👨‍✈️  ==================================================\n");
  printf("\nDigite 'ajuda' para conhecer todos os comandos.\n\n");

  while (1) {
    int numElementos;
    char **elementos;

    printf("Comando: ");
    scanf(" %[^\n]", input);

    if (!strcmp(input, "ajuda")) {
        MostrarComandos();
    } else if (!strcmp(input, "ver")) {
      VeSituacaoPreSimulacao();
    } else if (!strcmp(input, "limpar")) {
      system("clear");
    } else if (strcmp(input, "\n")) {
      SeparaElementos(input, &elementos, &numElementos);
      ChamaFuncoes(elementos, numElementos);
    }
  }

}

void IniciaInterface() {
  char input[128];
  
  while(1) {
    printf(" =========================================== ✈️");
    printf("  Simulação de trafego aéreo");
    printf(" ✈️  ==========================================\n");
    //printf("================== Simulador de tráfego aéreo =================\n\n");
    printf("\nImportar um (a)rquivo | Digitar comandos (m)anualmente [a, m]:");
    
    scanf(" %[^\n]", input);  
    initLogFile();

    system("clear");
  
    switch(input[0]) {
      case 'a': LeArquivo(); break;
      case 'm': Cli(); break;
    }

  }
}
