#include <stdio.h>
#include <stdlib.h>
#include "../include/listas.h"
#include "../include/eventos.h"
// *IndexaOrdenado
// *Reordena
// *InsereNoFim
// *RetiraNoInicio
// *RetiraPorCodigo
// Desaloca

//Funcao Ilustrativa
void MostraPista(Aviao* pista) {
  Aviao* iterator = pista;

  while(iterator) {
    printf("Z: %.0f | Destino: %s | Codigo: %d\n", iterator->coordenada.z, iterator->destino, iterator->codigo);
  
    iterator = iterator->proximo;
  }
  printf("\n");
}

//Ilustrativa
void Reordena(Aviao** lista, int codigo) {

  Aviao* elemento = RetiraPorCodigo(lista, codigo);
  
  //Codigo a ser retirado
  elemento->coordenada.z = NumeroEntre(400, 900);

  IndexaOrdenado(elemento, lista);

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

Aviao* RetiraPorCodigo(Aviao** lista, int codigo) {
  if(!(*lista)) return NULL;

  Aviao* iterator = *lista;
  while(iterator) {
    if(codigo == iterator->codigo) {
      if(iterator->proximo) iterator->proximo->anterior = iterator->anterior;
      if(iterator->anterior) {
        iterator->anterior->proximo = iterator->proximo;
      } else {
        *lista = iterator->proximo;
      }
      iterator->proximo = NULL;
      iterator->anterior = NULL;

      return iterator;
    }

    iterator = iterator->proximo;
  }
  return NULL;
}

void IndexaOrdenado(Aviao* elemento, Aviao** lista) {
  if(!(*lista)) {
    *lista = elemento;
    return;
  }

  if(elemento->coordenada.z <= (*lista)->coordenada.z) {
    (*lista)->anterior = elemento;
    elemento->proximo = (*lista);
    (*lista) = elemento;
    return;
  } else {
    Aviao* iterator = (*lista);

    while(iterator->proximo) {
       
      if(elemento->coordenada.z <= iterator->proximo->coordenada.z) {
        elemento->proximo = iterator->proximo;
        iterator->proximo = elemento;
        elemento->anterior = iterator;
        elemento->proximo->anterior = elemento;
        return;
      }
      
      iterator = iterator->proximo;
    }
    
    iterator->proximo = elemento;
    elemento->anterior = iterator;
  }
  
}

Aviao* RetiraNoInicio(Aviao** cabeca) {
  if(!(*cabeca)->proximo) {
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
