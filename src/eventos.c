//*InicializaPistas
//*SpawnaAviao
//*Decola
//*IniciaSimulacao
//Aterrissa
//*Finaliza
//VerificaColisoes
//*MoveAviao
//*AplicaDesventura

#define MAX_ALTITUDE 12.000
#define MIN_ALTITUDE 10.000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../include/listas.h"
#include "../include/eventos.h"

int NumeroEntre(int a, int b){
  if(a <= b)  return (rand() % (b - a + 1)) + a; 
  else return (rand() % (a - b + 1)) + b;
}


void AviaoMove(Aviao** lista) {
  Aviao* iterator = *lista;

  while(iterator) {
    if(sqrt(pow(iterator->coordenada.x, 2) + pow(iterator->coordenada.y, 2)) >= iterator->distancia * 0.9) {
      iterator->estado = ATERRISSANDO;
      printf("Chegando perto");
    }

    iterator->coordenada.x += iterator->velocidade.x;
    iterator->coordenada.y += iterator->velocidade.y;
    iterator->coordenada.z += iterator->velocidade.z;


    if(iterator->coordenada.z > MAX_ALTITUDE) iterator->coordenada.z = MAX_ALTITUDE;
    if(iterator->coordenada.z < MIN_ALTITUDE) iterator->coordenada.z = MIN_ALTITUDE;

    
    iterator = iterator->proximo;
  }


}


void AplicaDesventura(Aviao** aviao) {
  switch(desventura->tipo) {
    case TEMPESTADE:
      printf("Aconteceu uma tempestade com o %s.\n", (*aviao)->modelo);
      if(NumeroEntre(0, 1)) 
        (*aviao)->coordenada.z += 0.3;
      else 
        (*aviao)->coordenada.z -= 0.3;

      if(NumeroEntre(0, 1)) {
        (*aviao)->velocidade.x *= 1.1;
        (*aviao)->velocidade.y *= 1.1;
      } else {
        (*aviao)->velocidade.x *= 0.9;
        (*aviao)->velocidade.y *= 0.9;
      }
    break;
    case NEBLINA:
      printf("Aconteceu uma neblina com o %s.\n", (*aviao)->modelo);
      if(NumeroEntre(0, 1)) 
        (*aviao)->coordenada.z += 0.5;
      else 
        (*aviao)->coordenada.z -= 0.5;

      if(NumeroEntre(0, 1)) {
        (*aviao)->velocidade.x *= 1.05;
        (*aviao)->velocidade.y *= 1.05;
      } else {
        (*aviao)->velocidade.x *= 0.95;
        (*aviao)->velocidade.y *= 0.95;
      }
      break;
    case TURBULENCIA:
      printf("Aconteceu uma turbulencia com o %s.\n", (*aviao)->modelo);
      (*aviao)->velocidade.x *= 0.85;
      (*aviao)->velocidade.y *= 0.85;
    break;
  }

  DeletaDesventura(&desventura);
}

int Sorteio(Aviao** aviao, int ticket) {
  if((*aviao)->proximo) {
    if((*aviao)->estado == VOANDO) {
      int resultado = Sorteio(&(*aviao)->proximo, ticket + 1);
      if(resultado == ticket) {
        AplicaDesventura(aviao);
        Reordena(&local.ceu, (*aviao)->codigo);   
      }
      return resultado;
    } else {
      return Sorteio(&(*aviao)->proximo, ticket);
    }

  } else {
    return NumeroEntre(1, ticket);
  }
}

void VerificaDesventuras(int* turnoAtual) {
  if(!desventura) return;
  if(desventura->turno == *turnoAtual) {
    Sorteio(&local.ceu, 1);
    VerificaDesventuras(turnoAtual);
  } 
}

void IniciaSimulacao(int totalDeTurnos) {
  for(int i = 1; i <= totalDeTurnos; i++) {

    AviaoMove(&local.ceu);

  while(desventura->turno == i) {
    Sorteio(&local.ceu, 1);
  } 

    printf("Turno (%d)\n", i);
    LogGlobal();
  }

  Finaliza(); 
}

//Nao Terminado
void Decola(int numPista) {
  Aviao* retirado = RetiraNoInicio(&local.pista[numPista - 1]);

  float deslocamentoNaDecolagem = NumeroEntre(1500, 2500)/1000.0;
  printf("Velocidade na decolagem = %3.4f\n", deslocamentoNaDecolagem);
  printf("Direcao = %3.4f\n", retirado->direcao);

  if(NumeroEntre(0, 1))
    retirado->coordenada.x = (deslocamentoNaDecolagem)/(sqrt(pow(retirado->direcao, 2) + 1));
  else
    retirado->coordenada.x = -(deslocamentoNaDecolagem)/(sqrt(pow(retirado->direcao, 2) + 1));

  retirado->coordenada.y = retirado->velocidade.x * retirado->direcao;
  retirado->coordenada.z = NumeroEntre(10000, 12000)/1000.0;
  
  printf("Prova real: %3.4f == %3.4f\n\n", pow(retirado->velocidade.x, 2) + pow(retirado->velocidade.y, 2), pow(deslocamentoNaDecolagem, 2));

  retirado->velocidade.x = (retirado->distancia/retirado->tempoEstimado)/sqrt(pow(retirado->direcao, 2) + 1); 
  retirado->velocidade.y = retirado->velocidade.x * retirado->direcao;
  retirado->velocidade.z = 0;

  retirado->estado = VOANDO;
  // etc...

  IndexaOrdenado(retirado, &(local.ceu));  

}

void InicializaPistas(int quantidadeDePistas) {
  local.pista = (Aviao **) malloc(quantidadeDePistas * sizeof(Aviao *));

  local.quantidadeDePistas = quantidadeDePistas;

  for(int i = 0; i < quantidadeDePistas; i++) {
    local.pista[i] = (Aviao *) malloc(sizeof(Aviao));
    local.pista[i] = NULL;
  }
}

void SpawnaAviao(char* idPista, int codigo, char* modelo, char* cidadeDestino, float distancia, int tempoEstimadoDeVoo) {
  int numPista;
  sscanf(idPista, "f%d", &numPista);

  Aviao* novoAviao = InsereNoFim(&local.pista[numPista - 1]);
  
  novoAviao->numPista = numPista;
  novoAviao->codigo = codigo;
  novoAviao->modelo = modelo;
  novoAviao->distancia = distancia;
  novoAviao->tempoEstimado = tempoEstimadoDeVoo;
  novoAviao->tempoReal = 0;
  novoAviao->coordenada.x = 0;
  novoAviao->coordenada.y = 0;
  novoAviao->coordenada.z = 0;
  novoAviao->velocidade.x = 0;
  novoAviao->velocidade.y = 0;
  novoAviao->velocidade.z = 0;
  novoAviao->estado = ESPERANDO;
  novoAviao->destino = cidadeDestino;
  
  novoAviao->direcao = tan(NumeroEntre(0, 360)*M_PI/180.0);

}

void Finaliza() {
  for(int i = 0; i < local.quantidadeDePistas; i++) {
    DesalocaAviao(&local.pista[i]);
  }
  
  DesalocaAviao(&local.ceu);
  DesalocaAviao(&local.destino);

  DesalocaDesventura(&desventura);
}

