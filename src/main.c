#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/parser.h"
#include "../include/listas.h"
#include "../include/eventos.h"

Local local;
Desventura* desventura = NULL;

int main() {
  srand(((unsigned int)time(NULL)));

  // LeArquivo();

  InicializaPistas(2);

  SpawnaAviao("f1", 1, "A220", "SP", 409, 50);
  SpawnaAviao("f1", 2, "A320", "Brasilia", 409, 50);
  SpawnaAviao("f2", 6, "A320", "Brasilia", 409, 50);
  SpawnaAviao("f2", 3, "A420", "New York", 409, 50);
  
  // LogGlobal();
  
  Decola(1);
  Decola(2);

  InsereDesventura(TEMPESTADE, 4); 
  InsereDesventura(NEBLINA, 2); 
  InsereDesventura(TURBULENCIA, 10); 
  InsereDesventura(NEBLINA, 4); 

  IniciaSimulacao(6);
  // MostraLista(desventura);

  // LogGlobal();

  return 0;
}
