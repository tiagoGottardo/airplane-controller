#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/parser.h"
#include "../include/listas.h"
#include "../include/eventos.h"

Aviao** pista = NULL;
Aviao* ceu = NULL;
Aviao* destino = NULL;

int main() {
  srand(((unsigned int)time(NULL)));

  // LeArquivo();

  InicializaPistas(2);

  SpawnaAviao("f1", 1, "A220", "SP", 409, 50);
  SpawnaAviao("f1", 2, "A320", "Brasilia", 409, 50);
  // SpawnaAviao("f2", 2, "A320", "Brasilia", 409, 50);
  SpawnaAviao("f2", 3, "A420", "New York", 409, 50);

  Decola(1);
  Decola(1);
  Decola(2);
  
  printf("Ceu Antes:\n");
  MostraPista(ceu);

  // printf("Pista 1:\n");
  // MostraPista(pista[0]);
  
  // printf("Pista 2:\n");
  // MostraPista(pista[1]);
  
  printf("Ceu:\n");
  MostraPista(ceu);

  return 0;
}
