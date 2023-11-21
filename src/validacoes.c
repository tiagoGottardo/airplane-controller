#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/validacoes.h"

void Pistas(void **parametros) {
  int *qtdDePistas = (int *)parametros[0];
  printf("Chamou a função Pistas\n");
  if(*qtdDePistas < 1) {
    printf("Voce precisa de pelo menos uma pista!\n\n");
    return;
  }

  printf("\n");
  InicializaPistas(*qtdDePistas);
}

void InsereAviao(void **parametros) {
  int* pista = (int *)parametros[0];
  int* codigo = (int *) parametros[1];
  char* modelo = (char *)parametros[2];
  char* destino = (char *)parametros[3];
  int* distancia = (int *)parametros[4];
  int* tempoEstimado = (int *)parametros[5];

  if(!local.quantidadeDePistas) return;
  printf("Chamou a função InsereAviao\n");
  if(*pista > local.quantidadeDePistas || *pista < 1) {
    printf("Essa pista nao existe!\n\n");
    return;
  }

  if(*distancia < 1) {
    printf("A distancia precisa ser maior que 0!\n\n");
    return;
  }

  if(*tempoEstimado < 1) {
    printf("O tempo estimado precisa ser maior que 0!\n\n");
    return;
  }

  printf("\n");
  SpawnaAviao(*pista, *codigo, strdup(modelo), strdup(destino), *distancia, *tempoEstimado);
}

void Decolar(void **parametros) {
  int *pista = (int *)parametros[0];
  
  if(!local.quantidadeDePistas) return;
  printf("Chamou a função Decolar\n");
  if(*pista > local.quantidadeDePistas || *pista < 1) {
    printf("Essa pista nao existe!\n\n");
    return;
  }
  if(!local.pista[*pista - 1]) {
    printf("Nao tem nenhum aviao nessa pista!\n\n");
    return;
  }

  Decola(*pista);
}

void IniciarSimulacao(void **parametros) {
  int *qtdDeTurnos = (int *)parametros[0];

  if(!local.quantidadeDePistas) return;
  printf("Chamou a função IniciaSimulacao\n");
  if(*qtdDeTurnos < 1) {
    printf("A simulacao precisa mais tempo!\n\n");
    return;
  }
  printf("\n");

  IniciaSimulacao(*qtdDeTurnos); 
}

void Tempestade(void **parametros) {
  int* turno = (int *) parametros[0];

  printf("Chamou a função Tempestade no turno %d\n", *turno);

  if(!local.quantidadeDePistas) return;
  if(*turno < 1) {
    printf("O tempo da tempestade 'e invalido!\n");
    return;
  }

  printf("\n");
  InsereDesventura(TEMPESTADE, *turno);
}
void Turbulencia(void **parametros) {
  int* turno = (int *) parametros[0];

  printf("Chamou a função Turbulencia no turno %d\n", *turno);

  if(!local.quantidadeDePistas) return;
  if(*turno < 1) {
    printf("O tempo da turbulencia 'e invalido!\n");
    return;
  }

  printf("\n");
  InsereDesventura(TURBULENCIA, *turno);
}

void Neblina(void **parametros) {
  int* turno = (int *) parametros[0];

  printf("Chamou a função Neblina no turno %d\n", *turno);

  if(!local.quantidadeDePistas) return;
  if(*turno < 1) {
    printf("O tempo da neblina 'e invalido!\n");
    return;
  }

  printf("\n");
  InsereDesventura(NEBLINA, *turno);
}

void Fim(void **parametros) {
  printf("Chamou a função fim\n\n");
  Finaliza(); 
}
