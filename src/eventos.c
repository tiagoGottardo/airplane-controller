//*InicializaPistas
//*SpawnaAviao
//*Decola
//IniciaSimulacao
//Aterrissa
//*Finaliza
//VerificaColisoes
//*MoveAviao
//AplicaDesventura

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
    iterator->coordenada.x += iterator->velocidade.x;
    iterator->coordenada.y += iterator->velocidade.y;
    iterator->coordenada.z += iterator->velocidade.z;

    iterator = iterator->proximo;
  }

}

//Nao Terminado
void Decola(int numPista) {
  Aviao* retirado = RetiraNoInicio(&pista[numPista - 1]);

  float deslocamentoNaDecolagem = NumeroEntre(1500, 2500)/1000.0;
  printf("Velocidade na decolagem = %3.4f\n", deslocamentoNaDecolagem);
  printf("Direcao = %3.4f\n", retirado->direcao);

  retirado->velocidade.x = (deslocamentoNaDecolagem)/(sqrt(pow(retirado->direcao, 2) + 1));
  retirado->velocidade.y = retirado->velocidade.x * retirado->direcao;
  retirado->velocidade.z = NumeroEntre(10000, 12000)/1000.0;
  
  AviaoMove(&retirado);

  printf("Prova real: %3.4f == %3.4f\n\n", pow(retirado->velocidade.x, 2) + pow(retirado->velocidade.y, 2), pow(deslocamentoNaDecolagem, 2));

  retirado->velocidade.x *= (retirado->distancia/retirado->tempoEstimado)/(deslocamentoNaDecolagem); 
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
  // novoAviao->velocidade = distancia/tempoEstimadoDeVoo;
  novoAviao->direcao = tan(NumeroEntre(0, 360)*M_PI/180.0);

}

void Finaliza() {
  for(int i = 0; i < local.quantidadeDePistas; i++) {
    Desaloca(&local.pista[i]);
  }
  
  Desaloca(&local.ceu);
  Desaloca(&local.destino);
}

