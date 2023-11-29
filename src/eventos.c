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

void delay(int milissegundos) {
    clock_t inicio = clock();

    while ((clock() - inicio) * 1000 / CLOCKS_PER_SEC < milissegundos);
}

void ResolveColisoes(Aviao* aviao, Aviao* comparacao) { 
  if((aviao->coordenada.z - 0.05) > MIN_ALTITUDE) {
    aviao->coordenada.z -= 0.05;
    ReordenaCeu(aviao);
  } else {
    comparacao->coordenada.z += 0.05;
    ReordenaCeu(comparacao);
  }
}

int VerificaColisoes(Aviao* aviao, Aviao* comparacao) {
  if(comparacao->coordenada.z - aviao->coordenada.z <= 0.1 && aviao->coordenada.z - comparacao->coordenada.z >= -0.1) {
    float diferencaAntes = aviao->coordenada.x - comparacao->coordenada.x;
    float diferencaDepois = (aviao->coordenada.x + aviao->velocidade.x) - (comparacao->coordenada.x + comparacao->velocidade.x);

    if(aviao->direcao == comparacao->direcao) {
      if((diferencaAntes < 0.0 && diferencaDepois > 0.0) || (diferencaAntes > 0.0 && diferencaDepois < 0.0) || diferencaDepois == 0.0) {
        ResolveColisoes(aviao, comparacao);
        return 1;
      }
    } else {
      if(comparacao->proximo) return VerificaColisoes(aviao, comparacao->proximo);
    }
  }
  return 0; 
}

void Aterrissa(Aviao* aviao) {
  Aviao* retirado = Retira(&local.ceu, aviao);

  if(retirado->tempoReal < retirado->tempoEstimado) logEvent("O avião %i aterrissou! \nO avião %i chegou antes do esperado!\n", retirado->codigo, retirado->codigo);
  else if(retirado->tempoReal > retirado->tempoEstimado) logEvent("O avião %i aterrissou! \nO avião %i chegou depois do esperado!\n", retirado->codigo,retirado->codigo);
  else logEvent("O avião %i aterrissou! \nO avião %i chegou no tempo esperado!\n", retirado->codigo, retirado->codigo);

  retirado->estado = CONCLUIDO;

  retirado->velocidade.x = 0; 
  retirado->velocidade.y = 0; 
  retirado->velocidade.z = 0; 
  retirado->coordenada.x = (retirado->distancia/sqrt(pow(retirado->direcao, 2) + 1)); 
  retirado->coordenada.y = retirado->coordenada.x * retirado->direcao; 
  retirado->coordenada.z = 0; 

  IndexaNoFim(retirado, &local.destino);
}

void VerificaAterrissagem(Aviao* aviao) {
  float distanciaRestante = aviao->distancia - sqrt(pow(aviao->coordenada.x, 2) + pow(aviao->coordenada.y, 2)); 
  if(distanciaRestante > (0.1 * aviao->distancia)) return;

  float velocidade = sqrt(pow(aviao->velocidade.x, 2) + pow(aviao->velocidade.y, 2));
  float desaceleracao = -((pow(velocidade, 2))/(2*distanciaRestante));

  aviao->velocidade.x += desaceleracao/sqrt(pow(aviao->direcao, 2) + 1);
  aviao->velocidade.y = aviao->direcao * aviao->velocidade.x;
  aviao->velocidade.z = (aviao->coordenada.z/(velocidade/desaceleracao));

  if(aviao->estado == VOANDO) {
    aviao->estado = ATERRISSANDO;
    logEvent("O avião %i começou a aterrissagem.", aviao->codigo);
  }

  if(distanciaRestante <= 0.2) {
    Aterrissa(aviao);
  }
}

void AviaoMove(Aviao** lista) {
  Aviao* iterator = *lista;
  int colisoes = 0;
  while(iterator) {
    while(iterator->proximo && VerificaColisoes(iterator, iterator->proximo)) colisoes++;
    if(colisoes) {
      logEvent("Uma colisão entre o avião %i e o avião %i foi evitada.\n", iterator->codigo, iterator->proximo->codigo);
      colisoes = 0;
    }

    iterator->coordenada.x += iterator->velocidade.x;
    iterator->coordenada.y += iterator->velocidade.y;
    iterator->coordenada.z += iterator->velocidade.z;
    
    iterator->tempoReal++;

    VerificaAterrissagem(iterator);

    iterator = iterator->proximo;
  }
}

void AplicaDesventura(Aviao** aviao) {
  switch(desventura->tipo) {
    case TEMPESTADE:
      logEvent("Aconteceu uma tempestade com o avião %i.\n", (*aviao)->codigo);
      if(((MAX_ALTITUDE + MIN_ALTITUDE)/2) >= (*aviao)->coordenada.z) 
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
      logEvent("Aconteceu uma neblina com o avião %i.\n", (*aviao)->codigo);
      if(((MAX_ALTITUDE + MIN_ALTITUDE)/2) >= (*aviao)->coordenada.z) 
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
      logEvent("Aconteceu uma turbulência com o avião %i.\n", (*aviao)->codigo);
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
        ReordenaCeu(*aviao);   
      }
      return resultado;
    } else {
      return Sorteio(&(*aviao)->proximo, ticket);
    }

  } else {
    int resultado = NumeroEntre(1, ticket); 
    if(resultado == ticket) {
        AplicaDesventura(aviao);
        ReordenaCeu(*aviao);   
    }
    return resultado;
  }
}

void IniciaSimulacao(int totalDeTurnos) {
  for(int i = 1; i <= totalDeTurnos; i++) {

    system("clear");

    printf(" ===============================================");
    printf(" Simulação aérea - Minuto: %d", i);
    printf(" ===============================================\n");
    LogGlobal();


    while(desventura && desventura->turno == i) Sorteio(&local.ceu, 1); 
    AviaoMove(&local.ceu);

    delay(100);
  }

  printf(" Fim da simulação.\n\n");


  Finaliza(); 
  exit(0);
}

void Decola(int numPista) {
  Aviao* retirado = Retira(&local.pista[numPista - 1], local.pista[numPista - 1]);

  float deslocamentoNaDecolagem = NumeroEntre(1500, 2500)/1000.0;

  if(NumeroEntre(0, 1))
    retirado->coordenada.x = (deslocamentoNaDecolagem)/(sqrt(pow(retirado->direcao, 2) + 1));
  else
    retirado->coordenada.x = -(deslocamentoNaDecolagem)/(sqrt(pow(retirado->direcao, 2) + 1));

  retirado->coordenada.y = retirado->coordenada.x * retirado->direcao;
  retirado->coordenada.z = NumeroEntre(10000, 12000)/1000.0;

  retirado->velocidade.x = (retirado->distancia/retirado->tempoEstimado)/sqrt(pow(retirado->direcao, 2) + 1); 
  retirado->velocidade.y = retirado->velocidade.x * retirado->direcao;
  retirado->velocidade.z = 0;

  retirado->estado = VOANDO;

  IndexaOrdenado(retirado, &(local.ceu));  

}

void InicializaPistas(int quantidadeDePistas) {
  local.pista = (Aviao **) malloc(quantidadeDePistas * sizeof(Aviao *));

  local.quantidadeDePistas = quantidadeDePistas;

  for(int i = 0; i < quantidadeDePistas; i++) {
    local.pista[i] = (Aviao *) malloc(sizeof(Aviao));
    local.pista[i] = NULL;
  }
  local.ceu = NULL;
  local.destino = NULL;
}

void SpawnaAviao(int idPista, int codigo, char* modelo, char* destino, int distancia, int tempoEstimadoDeVoo) {

  Aviao* novoAviao = InsereNoFim(&local.pista[idPista - 1]);
  
  novoAviao->numPista = idPista;
  novoAviao->codigo = codigo;
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
  novoAviao->destino = destino;
  
  int valor = 0;
  for(int i = 0; novoAviao->destino[i] != '\0'; i++) valor += novoAviao->destino[i]; 
  novoAviao->direcao = tan((valor % 360)*PI/180.0);

}

void Finaliza() {
  for(int i = 0; i < local.quantidadeDePistas; i++) {
    DesalocaAviao(&local.pista[i]);
  }
  
  DesalocaAviao(local.pista);
  local.quantidadeDePistas = 0;

  DesalocaAviao(&local.ceu);
  DesalocaAviao(&local.destino);

  DesalocaDesventura(&desventura);
}

