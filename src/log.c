#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../include/log.h"

void logErro(char* functionName,char * errorBody);

void logMessage(const char *format, ...) {
  FILE *logFile = fopen("logfile.txt", "a");
  if (logFile == NULL) {
    logErro("log_logmessage","ERRO: não foi possível abrir o arquivo de LOG");
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

void vlogMessage(const char *format, va_list args) {
  FILE *logFile = fopen("logfile.txt", "a");
  if (logFile == NULL) {
    logErro("log_logmessage","ERRO: não foi possível abrir o arquivo de LOG");
    return;
  }

  vfprintf(logFile, format, args);

  fprintf(logFile, "\n");

  fclose(logFile);
}

void initLogFile(){
  FILE *logFile = fopen("logfile.txt", "w");
  if (logFile == NULL) {
    logErro("log_initlogfile", "ERRO: Não foi possível criar arquivo de log, o programa tem permição para isso?");
    return;
  }

  fprintf(logFile, "[Início do arquivo de Log]\n");
  fclose(logFile);
}

void logErro(char* functionName,char * errorBody){
  // printf("\n[ERRO] A função [%s] retornou erro: \n[ERRO]:{%s}\n\n", functionName, errorBody);
  logMessage("[ERRO] A função [%s] retornou erro: \n[ERRO]:{%s}", functionName, errorBody);
}

void logParserFunctions(char * functionName){
  logMessage("O arquivo de entrada foi lido e chamou a função %s", functionName); 
}

void logEvent(const char *format, ...){
  va_list args;
  va_list copyargs;

  va_start(args, format);
  va_copy(copyargs, args);
  vlogMessage(format, args);
  vprintf(format, copyargs);
  va_end(args);
  
  //getchar();

}