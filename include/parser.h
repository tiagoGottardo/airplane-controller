typedef enum {
    TIPO_INT,
    TIPO_FLOAT,
    TIPO_STRING
} TipoParametro;

typedef struct {
    char nome[20];
    int numParametros;
    TipoParametro *tiposParametros;
    void (*funcao)(void**);
} FuncaoInfo;

void ChamaFuncoes(char **elementos, int numElementos);
void LeArquivo();
