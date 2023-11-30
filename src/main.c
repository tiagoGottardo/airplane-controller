#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/interface.h"

Local local;
Desventura* desventura = NULL;

int main() {
  srand(((unsigned int)time(NULL)));

  IniciaInterface();

  return 0;
}
