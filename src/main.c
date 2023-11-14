#include <stdio.h>

#include "../include/parser.h"
#include "../include/listas.h"

int main() {
  Aviao *pista = NULL;

  Aviao *voando = NULL;
  // LeArquivo();

  AdicionaAviao(&pista, 2);
  AdicionaAviao(&pista, 4);
  AdicionaAviao(&pista, 6);

  Aviao* retirado = RetiraNoInicio(&pista); 
  Indexa(retirado, &voando);

  retirado = RetiraNoInicio(&pista); 
  Indexa(retirado, &voando);
  
  MostraPista(pista);

  MostraPista(voando);


  return 0;
}
