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
    
    ChamaFuncoes(elementos, numElementos);
  }

  fclose(arquivo);

  return;
}


void Pistas(void **parametros) {
  int *qtdDePistas = (int *)parametros[0];
  printf("Chamou a função Pistas\n");
  printf("Parametro 1: %d\n\n", *qtdDePistas); 
}

void InsereAviao(void **parametros) {
  char *p1 = (char *)parametros[0];
  int *p2 = (int *)parametros[1];
  char *p3 = (char *)parametros[2];
  char *p4 = (char *)parametros[3];
  int *p5 = (int *)parametros[4];
  int *p6 = (int *)parametros[5];
  printf("Chamou a função InsereAviao\n");
  printf("Parametro 1: %s\n", p1); 
  printf("Parametro 2: %d\n", *p2); 
  printf("Parametro 3: %s\n", p3); 
  printf("Parametro 4: %s\n", p4); 
  printf("Parametro 5: %d\n", *p5); 
  printf("Parametro 6: %d\n\n", *p6); 
}

void Decolar(void **parametros) {
  int *p1 = (int *)parametros[0];
  int *p2 = (int *)parametros[1];
  int *p3 = (int *)parametros[2];
  printf("Chamou a função Decolar\n");
  printf("Parametro 1: %d\n", *p1); 
  printf("Parametro 2: %d\n", *p2); 
  printf("Parametro 3: %d\n\n", *p3); 
}

void IniciaSimulacao2(void **parametros) {
  int *p1 = (int*)parametros[0];
  printf("Chamou a função IniciaSimulacao\n");
  printf("Parametro 1: %d\n\n", *p1); 
}


void ChamaFuncoes(char **elementos, int numElementos) {
  FuncaoInfo mapeamento[] = {
    {"pistas", 1, (TipoParametro[]){TIPO_INT}, Pistas},
    {"insere_aviao", 6, (TipoParametro[]){TIPO_STRING, TIPO_INT, TIPO_STRING, TIPO_STRING, TIPO_INT, TIPO_INT}, InsereAviao},
    {"decolar", 3, (TipoParametro[]){TIPO_INT, TIPO_INT, TIPO_INT}, Decolar},
    {"iniciasimulacao", 1, (TipoParametro[]){TIPO_INT}, IniciaSimulacao2}
  };

  for (int i = 0; i < sizeof(mapeamento) / sizeof(mapeamento[0]); ++i) {
    if (strcmp(elementos[0], mapeamento[i].nome) == 0) {
      
      if(mapeamento[i].numParametros != numElementos - 1) {
        printf("A quantidade de parametros esta errada! ):");
        return;
      };
      
      void **parametros = malloc(mapeamento[i].numParametros * sizeof(void *));
           

      for (int j = 0; j < mapeamento[i].numParametros; ++j) {
        switch (mapeamento[i].tiposParametros[j]) {
          case TIPO_INT: {
            parametros[j] = malloc(sizeof(int));
            *(int *)parametros[j] = atoi(elementos[j + 1]);
            break;
          }
          case TIPO_FLOAT: {
            parametros[j] = malloc(sizeof(float));
            *(float *)parametros[j] = *(float *) elementos[j + 1]; 
            break;
          }
          case TIPO_STRING: {
            parametros[j] = malloc(strlen(elementos[j + 1]) + 1); // +1 para o caractere nulo
            strcpy((char *)parametros[j], elementos[j + 1]);
            break;
          }
        }
      }

      mapeamento[i].funcao(parametros);

      for (int j = 0; j < mapeamento[i].numParametros; ++j) {
        free(parametros[j]);
      }
  
      free(parametros);
      return;
    }
  }

    printf("Função não encontrada\n");
    return;
}
