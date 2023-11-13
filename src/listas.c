#include <stdio.h>
#include <stdlib.h>
#include "../include/listas.h"

// IndexaOrdenado
// MoveOrdenado
// InsereNoFim
// RetiraNoInicio
// RetiraPorCodigo
// Desaloca

void InsereNoInicio(Aviao **cabeca) {
  if(*cabeca == NULL) *cabeca = (Aviao *) malloc(sizeof(Aviao));

  Aviao* node = (Aviao *) malloc(sizeof(Aviao*));
  node->proximo = *cabeca;
  (*cabeca)->anterior = node;
  *cabeca = node;   
}

