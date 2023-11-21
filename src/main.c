#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/parser.h"

Local local;
Desventura* desventura = NULL;

int main() {
  srand(((unsigned int)time(NULL)));

  LeArquivo();

  // InicializaPistas(2);

  // SpawnaAviao(1, 1, "A220", "SP", 500, 10);
  // SpawnaAviao(1, 2, "B320", "Brasilia", 200, 50);
  // SpawnaAviao(2, 6, "C320", "Brasilia", 400, 50);
  // SpawnaAviao(2, 3, "D420", "New York", 409, 50);
  
  // LogGlobal();

  // Decola(1);
  // Decola(1);

  // Decola(2);
  // Decola(2);

  // LogGlobal();
  
  // InsereDesventura(TEMPESTADE, 2); 
  // InsereDesventura(TURBULENCIA, 10); 
  // InsereDesventura(TEMPESTADE, 4); 

  // IniciaSimulacao(5);

  // MostraLista(desventura);


  return 0;
}
