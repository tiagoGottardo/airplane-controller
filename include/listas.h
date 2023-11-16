typedef struct Coordenada {
  float x;
  float y;
  float z;
} Coordenada;

typedef enum {
  ESPERANDO,
  VOANDO,
  ATERRISSANDO,
  CONCLUIDO
} Estado;

typedef struct Aviao {
  int numPista;
  int codigo;
  char *modelo;
  float distancia;
  int tempoEstimado;
  int tempoReal;
  Coordenada coordenada;
  Coordenada velocidade;
  Estado estado;
  char *destino;
  float direcao;
  struct Aviao *proximo;
  struct Aviao *anterior;
} Aviao;

extern Aviao** pista;
extern Aviao* ceu;
extern Aviao* destino; 

void MostraPista(Aviao* pista);
void AdicionaAviao (Aviao** pista, int value);
Aviao* InsereNoFim(Aviao **cabeca);
Aviao* RetiraNoInicio(Aviao** cabeca);
void IndexaNoInicio(Aviao* elemento, Aviao** lista);
void IndexaOrdenado(Aviao* elemento, Aviao** lista);
Aviao* RetiraPorCodigo(Aviao** lista, int codigo);
void Reordena(Aviao** lista, int codigo);
void LogGlobal(int n);
void Desaloca(Aviao** lista);
