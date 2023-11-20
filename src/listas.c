#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/listas.h"
#include "../include/eventos.h"
// *IndexaOrdenado
// *IndexaNoInicio
// *Reordena
// *InsereDesventura
// *InsereNoFim
// *RetiraNoInicio
// *RetiraPorCodigo
// *Desaloca

void DesalocaAviao(Aviao** lista) {
  if(!(*lista)) return;

  if((*lista)->proximo) {
    DesalocaAviao(&(*lista)->proximo);
  }

  free(*lista);
  *lista = NULL;
}

void DesalocaDesventura(Desventura** lista) {
  if(!(*lista)) return;

  if((*lista)->proximo) {
    DesalocaDesventura(&(*lista)->proximo);
  }

  free(*lista);
  *lista = NULL;
}

void LogGlobal() {
  Aviao* iterator;
  for(int i = 0; i < local.quantidadeDePistas; i++) {
    printf("Pista %d:\n", i + 1);
    if(local.pista[i]) {
      iterator = local.pista[i];

      while(iterator) {
        printf("Codigo:%3d | Modelo: %6s | Velocidade: (%3.4f;%3.4f;%3.4f) | Coordenada: (%3.4f;%3.4f;%3.4f)\n", iterator->codigo, iterator->modelo, iterator->velocidade.x, iterator->velocidade.y, iterator->velocidade.z, iterator->coordenada.x, iterator->coordenada.y, iterator->coordenada.z);

        iterator = iterator->proximo;
      }
    }
    printf("\n");
  }

  printf("Ceu:\n");
  if(local.ceu) {
    iterator = local.ceu;
    while(iterator) {
      printf("Codigo:%3d | Modelo: %6s | Velocidade: (%3.4f;%3.4f;%3.4f) | Coordenada: (%3.4f;%3.4f;%3.4f)\n", iterator->codigo, iterator->modelo, iterator->velocidade.x, iterator->velocidade.y, iterator->velocidade.z, iterator->coordenada.x, iterator->coordenada.y, iterator->coordenada.z);
      printf("Distancia restante: %f\n", iterator->distancia - sqrt(pow(iterator->coordenada.x, 2) + pow(iterator->coordenada.y, 2))   );

      iterator = iterator->proximo;
    } 
    printf("\n");
  }
  printf("-----------------------------------------------------------------------------------------\n");
}

//Funcao Ilustrativa
void MostraLista(Desventura* lista) {
  if(!lista) return;
  Desventura* iterator = lista;

  while(iterator) {
    switch(iterator->tipo) {
      case NEBLINA:
        printf("Neblina no turno %d.\n", iterator->turno);
      break;
      case TEMPESTADE:
        printf("Tempestade no turno %d.\n", iterator->turno);
      break;
      case TURBULENCIA:
        printf("Turbulencia no turno %d.\n", iterator->turno);
      break;
    }
    
      iterator = iterator->proximo;
  }
  printf("\n");
}

void InsereDesventura(TipoDesventura tipo, int turno) {
  if(turno < 1) {
    printf("O turno escolhido 'e invalido!\n");
    return;
  }

  Desventura* novo = (Desventura *) malloc(sizeof(Desventura));
  novo->tipo = tipo;
  novo->turno = turno;
  IndexaDesventuraOrdenado(novo, &desventura);
}

//Ilustrativa
void Reordena(Aviao** lista, int codigo) {

  Aviao* elemento = RetiraPorCodigo(lista, codigo);
 
  if(!elemento) {
    printf("Um aviao com esse codigo nao se encontra no ceu!\n");
    return;
  }

  IndexaOrdenado(elemento, lista);
}

Aviao* InsereNoFim(Aviao** cabeca) {
  if(!(*cabeca)) {
    *cabeca = (Aviao *) malloc(sizeof(Aviao));
    (*cabeca)->proximo = NULL;
    (*cabeca)->anterior = NULL;
    return *cabeca;
  }

  Aviao* node = (Aviao *) malloc(sizeof(Aviao));
  
  Aviao* iterator = *cabeca;

  while(iterator->proximo) iterator = iterator->proximo;

  node->anterior = iterator;
  iterator->proximo = node;

  return node;
}

void IndexaNoInicio(Aviao* elemento, Aviao** lista){
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

void IndexaDesventuraOrdenado(Desventura* elemento, Desventura** lista) {
  if(!(*lista)) {
    *lista = elemento;
    return;
  }

  if(elemento->turno <= (*lista)->turno) {
    elemento->proximo = (*lista);
    (*lista) = elemento;
    return;
  } else {
    Desventura* iterator = (*lista);

    while(iterator->proximo) {
       
      if(elemento->turno <= iterator->proximo->turno) {
        elemento->proximo = iterator->proximo;
        iterator->proximo = elemento;
        return;
      }
      
      iterator = iterator->proximo;
    }
    
    iterator->proximo = elemento;
  }
  
}

void DeletaDesventura(Desventura** cabeca) {
  if(!(*cabeca)) return;
  
  Desventura* proximo = (*cabeca)->proximo;

  (*cabeca)->proximo = NULL;
  free(*cabeca);
  *cabeca = NULL;

  if(proximo) *cabeca = proximo;
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
