#include <stdio.h>
#include <string.h>

#include "../include/validacoes.h"

void Pistas(void **parametros) {
  int *qtdDePistas = (int *)parametros[0];
  if(*qtdDePistas < 1) {
    // logErro("validações_pistas", "Voce precisa de pelo menos uma pista.");
    printf("\n Você precisa de pelo menos uma pista.\n\n");
    return;
  }

  if(local.quantidadeDePistas > 0) {
    printf("\n Você já inicializou as pistas. Caso deseja mudar o número de pistas, reinicie.\n\n");
    return;
  }

  InicializaPistas(*qtdDePistas);
  printf("\n O aeroporto tem %d pistas.\n\n", *qtdDePistas);
}

void InsereAviao(void **parametros) {
  int* pista = (int *)parametros[0];
  int* codigo = (int *) parametros[1];
  char* modelo = (char *)parametros[2];
  char* destino = (char *)parametros[3];
  int* distancia = (int *)parametros[4];
  int* tempoEstimado = (int *)parametros[5];

  if(!local.quantidadeDePistas) {
    printf("\n As pistas ainda não foram inicializadas!\n\n");
    return;
  }
  if(*pista > local.quantidadeDePistas || *pista < 1) {
    // logErro("validações_insereavião", "Essa pista nao existe.");
    printf("\n Essa pista não existe!\n\n");
    return;
  }

  if(*distancia < 1) {
    // logErro("validações_insereavião", "A distancia precisa ser maior que 0.");
    printf("\n A distância precisa ser maior que 0!\n\n");
    return;
  }

  if(*tempoEstimado < 1) {
    // logErro("validações_insereavião", "O tempo estimado precisa ser maior que 0.");
    printf("\n O tempo estimado precisa ser maior que 0!\n\n");
    return;

  }

  printf("\n O avião %d foi adicionado na pista %d.\n\n", *codigo, *pista);
  SpawnaAviao(*pista, *codigo, strdup(modelo), strdup(destino), *distancia, *tempoEstimado);
}

void Decolar(void **parametros) {
  int *pista = (int *)parametros[0];
  
  if(!local.quantidadeDePistas) {
    printf("\n As pistas ainda não foram inicializadas!\n\n");
    return;
  }

  if(*pista > local.quantidadeDePistas || *pista < 1) {
    // logErro("validações_decolar", "Essa pista nao existe.");
    printf("\n Essa pista não existe!\n\n");
    return;
  }

  if(!local.pista[*pista - 1]) {
    // logErro("validações_decolar", "Nao tem nenhum aviao nessa pista!\n\n");
    printf("\n Não tem nenhum aviao nessa pista!\n\n");
    return;
  }

  printf("\n O avião %d decolou!\n\n", local.pista[*pista - 1]->codigo);
  Decola(*pista);
}

void IniciarSimulacao(void **parametros) {
  int *qtdDeTurnos = (int *)parametros[0];

  if(!local.quantidadeDePistas) {
    printf("\n As pistas ainda não foram inicializadas!\n\n");
    return;
  }

  if(*qtdDeTurnos < 1) {
    // logErro("validações_iniciarsimulação", "A simulacao precisa de tempo maior ou igual a 1.");
    printf("\n A simulação precisa de tempo maior que 0!\n\n");
    return;
  }

  IniciaSimulacao(*qtdDeTurnos); 
}

void Tempestade(void **parametros) {
  int* turno = (int *) parametros[0];
  
  if(!local.quantidadeDePistas) {
    printf("\n As pistas ainda não foram inicializadas!\n\n");
    return;
  }

  if(*turno < 1) {
    // logErro("validações_insereavião", "O tempo da tempestade precisa ser maior ou igual a 1");
    printf("\n A tempestade precisa de tempo maior que 0!\n\n");
    return;
  }

  printf("\n Uma tempestade acontecerá no turno %d!\n\n", *turno);
  InsereDesventura(TEMPESTADE, *turno);
}
void Turbulencia(void **parametros) {
  int* turno = (int *) parametros[0];

  if(!local.quantidadeDePistas) {
    printf("\n As pistas ainda não foram inicializadas!\n\n");
    return;
  }

  if(*turno < 1) {
    // logErro("validações_insereavião", "O tempo da turbulencia precisa ser maior ou igual a 1");
    printf("\n A turbulencia precisa de tempo maior que 0!\n\n");
    return;
  }

  printf("\n Uma turbulência acontecerá no turno %d!\n\n", *turno);
  InsereDesventura(TURBULENCIA, *turno);
}

void Neblina(void **parametros) {
  int* turno = (int *) parametros[0];

  if(!local.quantidadeDePistas) {
    printf("\n As pistas ainda não foram inicializadas!\n\n");
    return;
  }

  if(*turno < 1) {
    // logErro("validações_insereavião", "O tempo da neblina precisa ser maior ou igual a 1");
    printf("\n A neblina precisa de tempo maior que 0!\n\n");
    return;
  }

  printf("\n Uma neblina acontecerá no turno %d!\n\n", *turno);
  InsereDesventura(NEBLINA, *turno);
}

void Fim(void **parametros) {
  Finaliza(); 
}
