#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

void SeparaElementos(const char *linha, char ***elementos, int *numElementos) {
  *numElementos = 0;

  char *linhaCopia = strdup(linha);
  char *tokenCount = strtok(linhaCopia, " ,<>\n");

  while (tokenCount != NULL) {
    (*numElementos)++;
    tokenCount = strtok(NULL, " ,<>\n");
  }

  free(linhaCopia);

  *elementos = (char **)malloc(*numElementos * sizeof(char *));

  char *linhaCopia2 = strdup(linha);
  char *token = strtok(linhaCopia2, " ,<>\n");

  for (int i = 0; i < *numElementos; i++) {
    (*elementos)[i] = strdup(token);
    token = strtok(NULL, " ,<>\n");
  }

  free(linhaCopia2);
}

void MostraArray(char **array, int numStrings) {
  for(int i = 0; i < numStrings; i++) {
    printf("(%s) ", array[i]);
  }
  printf("\n");
}

void LeArquivo() {
  FILE *arquivo = fopen("entrada.txt", "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo");
      return;
  }

  char linha[100];

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    int numElementos;
    char **elementos;
    SeparaElementos(linha, &elementos, &numElementos);
    MostraArray(elementos, numElementos);
  }

  fclose(arquivo);

  return;
}
