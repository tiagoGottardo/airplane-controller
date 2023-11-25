#include <stdio.h>
#include <string.h>

#include "../include/validacoes.h"

void Pistas(void **parametros) {
  int *qtdDePistas = (int *)parametros[0];
  if(*qtdDePistas < 1) {
    logErro("validações_pistas", "Voce precisa de pelo menos uma pista.");
    return;
  }

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
  if(*pista > local.quantidadeDePistas || *pista < 1) {
    logErro("validações_insereavião", "Essa pista nao existe.");
    return;
  }

  if(*distancia < 1) {
    logErro("validações_insereavião", "A distancia precisa ser maior que 0.");
    return;
  }

  if(*tempoEstimado < 1) {
    logErro("validações_insereavião", "O tempo estimado precisa ser maior que 0.");
    return;
  }

  SpawnaAviao(*pista, *codigo, strdup(modelo), strdup(destino), *distancia, *tempoEstimado);
}

void Decolar(void **parametros) {
  int *pista = (int *)parametros[0];
  
  if(!local.quantidadeDePistas) return;
  if(*pista > local.quantidadeDePistas || *pista < 1) {
    logErro("validações_decolar", "Essa pista nao existe.");
    return;
  }
  if(!local.pista[*pista - 1]) {
    logErro("validações_decolar", "Nao tem nenhum aviao nessa pista!\n\n");
    return;
  }

  Decola(*pista);
}

void IniciarSimulacao(void **parametros) {
  int *qtdDeTurnos = (int *)parametros[0];

  if(!local.quantidadeDePistas) return;
  if(*qtdDeTurnos < 1) {
    logErro("validações_iniciarsimulação", "A simulacao precisa de tempo maior ou igual a 1.");
    return;
  }

  IniciaSimulacao(*qtdDeTurnos); 
}

void Tempestade(void **parametros) {
  int* turno = (int *) parametros[0];

  if(!local.quantidadeDePistas) return;
  if(*turno < 1) {
    logErro("validações_insereavião", "O tempo da tempestade precisa ser maior ou igual a 1");
    return;
  }

  InsereDesventura(TEMPESTADE, *turno);
}
void Turbulencia(void **parametros) {
  int* turno = (int *) parametros[0];

  if(!local.quantidadeDePistas) return;
  if(*turno < 1) {
    logErro("validações_insereavião", "O tempo da turbulencia precisa ser maior ou igual a 1");
    return;
  }

  InsereDesventura(TURBULENCIA, *turno);
}

void Neblina(void **parametros) {
  int* turno = (int *) parametros[0];

  if(!local.quantidadeDePistas) return;
  if(*turno < 1) {
    logErro("validações_insereavião", "O tempo da neblina precisa ser maior ou igual a 1");
    return;
  }

  InsereDesventura(NEBLINA, *turno);
}

void Fim(void **parametros) {
  Finaliza(); 
}
