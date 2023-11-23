#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>

#include"../include/log.h"

void logMessage(const char *format, ...) {
  FILE *logFile = fopen("logfile.txt", "a");
  if (logFile == NULL) {
    printf("ERRO: não foi possível abrir o arquivo de LOG");
    return;
  }

    // Escrever a mensagem formatada no arquivo de log
  va_list args;
  va_start(args, format);
  vfprintf(logFile, format, args);
  va_end(args);

    // Adicionar uma quebra de linha
  fprintf(logFile, "\n");

    // Fechar o arquivo de log
  fclose(logFile);
}

void logInitPistas(int numPista){
  logMessage("Entrada inicializou %i pistas", numPista);
}

void logInitAvioes(){
  logMessage("Entrada inseriu avião");
}
