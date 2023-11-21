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
  // for(int i = 0; i < local.quantidadeDePistas; i++) {
  //   printf("Pista %d:\n", i + 1);
  //   if(local.pista[i]) {
  //     iterator = local.pista[i];

  //     while(iterator) {
  //       printf("Modelo: %6s | Velocidade: (%3.4f;%3.4f;%3.4f) | Coordenada: (%3.4f;%3.4f;%3.4f)\n", iterator->modelo, iterator->velocidade.x, iterator->velocidade.y, iterator->velocidade.z, iterator->coordenada.x, iterator->coordenada.y, iterator->coordenada.z);

  //       iterator = iterator->proximo;
  //     }
  //   }
  //   printf("\n");
  // }


  printf("Ceu:\n");
  if(local.ceu) {
    iterator = local.ceu;
    while(iterator) {
      printf("Codigo: %3d | Velocidade: (%3.2f;%3.2f;%3.2f) | Coordenada: (%3.2f;%3.2f;%3.2f) | ", iterator->codigo, iterator->velocidade.x, iterator->velocidade.y, iterator->velocidade.z, iterator->coordenada.x, iterator->coordenada.y, iterator->coordenada.z);
      printf("Distancia restante: %f\n", iterator->distancia - sqrt(pow(iterator->coordenada.x, 2) + pow(iterator->coordenada.y, 2))   );

      iterator = iterator->proximo;
    } 
  }
  printf("\n");

  printf("Destino:\n");
  if(local.destino) {
    iterator = local.destino;
    while(iterator) {
      printf("Codigo: %3d| Velocidade: (%3.2f;%3.2f;%3.2f) | Coordenada: (%3.2f;%3.2f;%3.2f)\n", iterator->codigo, iterator->velocidade.x, iterator->velocidade.y, iterator->velocidade.z, iterator->coordenada.x, iterator->coordenada.y, iterator->coordenada.z);

      iterator = iterator->proximo;
    } 
  }
  printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
}

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
  Desventura* novo = (Desventura *) malloc(sizeof(Desventura));
  novo->tipo = tipo;
  novo->turno = turno;
  novo->proximo = NULL;
  IndexaDesventuraOrdenado(novo, &desventura);
}

void ReordenaCeu(Aviao* aviao) {
  if(((!aviao->anterior) || aviao->anterior->coordenada.z <= aviao->coordenada.z) && ((!aviao->proximo) || aviao->proximo->coordenada.z > aviao->coordenada.z)) return;

  Aviao* elemento = Retira(&local.ceu, aviao);
 
  if(!elemento) {
    printf("Um aviao com esse codigo nao se encontra no ceu!\n");
    return;
  }

  IndexaOrdenado(elemento, &local.ceu);
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

  node->proximo = NULL;

  return node;
}

void IndexaNoFim(Aviao* elemento, Aviao** lista){
  if(!(*lista))  {
    *lista = elemento;
    return;
  } 
  
  Aviao* iterator = *lista;

  while(iterator->proximo) iterator = iterator->proximo;

  elemento->anterior = iterator;
  iterator->proximo = elemento;

}

Aviao* Retira(Aviao** lista, Aviao* aviao) {
  if(!(*lista)) return NULL;

  if(aviao->proximo) aviao->proximo->anterior = aviao->anterior;
  if(aviao->anterior) {
   aviao->anterior->proximo = aviao->proximo;
  } else {
   *lista = aviao->proximo;
  }

  aviao->proximo = NULL;
  aviao->anterior = NULL;

  return aviao;
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
  (*cabeca)->turno = 0;
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
