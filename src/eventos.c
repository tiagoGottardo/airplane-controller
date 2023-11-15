//*InicializaPistas
//*SpawnaAviao
//Decola
//IniciaSimulacao
//Aterrissa
//Finaliza
//VerificaColisoes
//MoveAviao
//AplicaTempestade
//AplicaNeblina
//AplicaTurbulencia
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/listas.h"

int NumeroEntre(int a, int b){

  return (rand() % (b - a)) + a + 1; 
}

//Nao Terminado
void Decola(int numPista) {
  Aviao* retirado = RetiraNoInicio(&pista[numPista - 1]);

  retirado->coordenada.z = NumeroEntre(400, 600);
  retirado->estado = VOANDO;
  // etc...
 
  IndexaOrdenado(retirado, &ceu);  

}



void InicializaPistas(int quantidadeDePistas) {
  pista = (Aviao **) malloc(quantidadeDePistas * sizeof(Aviao *));

  for(int i = 0; i < quantidadeDePistas; i++) {
    pista[i] = (Aviao *) malloc(sizeof(Aviao));
    pista[i] = NULL;
  }
}

void SpawnaAviao(char* idPista, int codigo, char* modelo, char* cidadeDestino, float distancia, int tempoEstimadoDeVoo) {
  int numPista;
  sscanf(idPista, "f%d", &numPista);

  Aviao* novoAviao = InsereNoFim(&pista[numPista - 1]);
  
  novoAviao->numPista = numPista;
  novoAviao->codigo = codigo;
  novoAviao->modelo = modelo;
  novoAviao->distancia = distancia;
  novoAviao->tempoEstimado = tempoEstimadoDeVoo;
  novoAviao->tempoReal = 0;
  novoAviao->coordenada.x = 0;
  novoAviao->coordenada.y = 0;
  novoAviao->coordenada.z = 0;
  novoAviao->estado = ESPERANDO;
  novoAviao->destino = cidadeDestino;
  novoAviao->velocidade = distancia/tempoEstimadoDeVoo;
  novoAviao->direcao = 1;
  novoAviao->sentido = 0;

}
