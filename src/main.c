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

  SpawnaAviao("f1", 1, "A220", "SP", 40, 5);
  SpawnaAviao("f1", 2, "B320", "Brasilia", 20, 5);
  SpawnaAviao("f2", 6, "C320", "Brasilia", 400, 50);
  SpawnaAviao("f2", 3, "D420", "New York", 409, 50);
  
  Decola(1);
  Decola(1);

  Decola(2);
  Decola(2);

  LogGlobal();
  InsereDesventura(TEMPESTADE, 4); 
  InsereDesventura(TEMPESTADE, 2); 
  InsereDesventura(TURBULENCIA, 10); 
  InsereDesventura(NEBLINA, 4); 

  IniciaSimulacao(10);

  MostraLista(desventura);


  return 0;
}
