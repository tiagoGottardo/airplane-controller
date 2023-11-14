#include <stdio.h>
#include <stdlib.h>
#include "../include/listas.h"

// IndexaOrdenado
// Reordena
// *InsereNoFim
// *RetiraNoInicio
// RetiraPorCodigo
// Desaloca

//Funcao Ilustrativa
void MostraPista(Aviao* pista) {
  Aviao* iterator = pista;

  while(iterator) {
    printf("%.0f ", iterator->coordenada.z);
  
    iterator = iterator->proximo;
  }
  printf("\n");
}

//Funcao Ilustrativa
void AdicionaAviao(Aviao** pista, int value) {
  Aviao *aviao = InsereNoFim(pista);

  aviao->coordenada.z = value; 
}

Aviao* InsereNoFim(Aviao** cabeca) {
  if(!(*cabeca)) return *cabeca = (Aviao *) malloc(sizeof(Aviao));

  Aviao* node = (Aviao *) malloc(sizeof(Aviao));
  
  Aviao* iterator = *cabeca;

  while(iterator->proximo) iterator = iterator->proximo;

  node->anterior = iterator;
  iterator->proximo = node;

  return node;
}

//Funcao Ilustrativa
void Indexa(Aviao* elemento, Aviao** lista){
  if(!(*lista))  {
    *lista = elemento;
  } else {
    elemento->proximo = *lista;
    (*lista)->anterior = elemento;
    *lista = elemento;
  }
}

Aviao* RetiraNoInicio(Aviao** cabeca) {
  if(!(*cabeca)) {
    Aviao* retirado = (*cabeca);
    retirado->proximo = NULL;
    *cabeca = NULL;
    return retirado;
  }

  Aviao* novaCabeca = (*cabeca)->proximo;

  Aviao* retirado = novaCabeca->anterior;
  retirado->proximo = NULL;
  novaCabeca->anterior = NULL;
  *cabeca = novaCabeca;

  return retirado;
}

