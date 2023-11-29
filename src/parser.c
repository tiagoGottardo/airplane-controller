#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

void SeparaElementos(const char *linha, char ***elementos, int *numElementos) {
  if(!linha) return;
  *numElementos = 0;

  char *linhaCopia = strdup(linha);
  char *tokenCount = strtok(linhaCopia, " ,()\n");

  while (tokenCount != NULL) {
    (*numElementos)++;
    tokenCount = strtok(NULL, " ,()\n");
  }

  free(linhaCopia);

  *elementos = (char **)malloc(*numElementos * sizeof(char *));

  char *linhaCopia2 = strdup(linha);
  char *token = strtok(linhaCopia2, " ,()\n");

  for (int i = 0; i < *numElementos; i++) {
    (*elementos)[i] = strdup(token);
    token = strtok(NULL, " ,()\n");
  }

  free(linhaCopia2);
}

void LeArquivo() {
  FILE *arquivo = fopen("entrada.txt", "r");

  if (arquivo == NULL) {
    logErro("parser_learquivo","Erro ao abrir o arquivo");
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

void ChamaFuncoes(char **elementos, int numElementos) {
  FuncaoInfo mapeamento[] = {
    {"pistas", 1, (TipoParametro[]){TIPO_INT}, Pistas},
    {"insere_aviao", 6, (TipoParametro[]){TIPO_INT, TIPO_INT, TIPO_STRING, TIPO_STRING, TIPO_INT, TIPO_INT}, InsereAviao},
    {"decolar", 1, (TipoParametro[]){TIPO_INT}, Decolar},
    {"iniciasimulacao", 1, (TipoParametro[]){TIPO_INT}, IniciarSimulacao},
    {"tempestade", 1, (TipoParametro[]){TIPO_INT}, Tempestade},
    {"turbulencia", 1, (TipoParametro[]){TIPO_INT}, Turbulencia},
    {"neblina", 1, (TipoParametro[]){TIPO_INT}, Neblina},
    {"fim", 0, (TipoParametro[]){}, Fim},
  };

  for (int i = 0; i < sizeof(mapeamento) / sizeof(mapeamento[0]); ++i) {
    if (strcmp(elementos[0], mapeamento[i].nome) == 0) {
      
      if((numElementos - 1) < mapeamento[i].numParametros) {
        printf("\n A quantidade de parâmetros está incorreta.\n\n");
        return;
      }

      void **parametros = malloc(mapeamento[i].numParametros * sizeof(void *));

      for (int j = 0; j < mapeamento[i].numParametros; ++j) {
        switch (mapeamento[i].tiposParametros[j]) {
          case TIPO_INT: {
            parametros[j] = malloc(sizeof(int));
            *(int *)parametros[j] = atoi(elementos[j + 1]);
            break;
          }
          case TIPO_STRING: {
            parametros[j] = malloc(strlen(elementos[j + 1]) + 1); // +1 para o caractere nulo
            strcpy((char *)parametros[j], elementos[j + 1]);
            break;
          }
        }
      }

      logParserFunctions(mapeamento[i].nome);
      mapeamento[i].funcao(parametros);

      for (int j = 0; j < mapeamento[i].numParametros; ++j) {
        free(parametros[j]);
      }
  
      free(parametros);
      return;
    }
  }

    logErro("parser_chamafunções", "Função não encontrada");
    printf("\n Essa função não existe.\n\n");
    return;
}
