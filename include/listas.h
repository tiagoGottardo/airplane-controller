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
  Estado estado;
  char *destino;
  float velocidade;
  float direcao;
  int sentido;
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
void IndexaOrdenado(Aviao* elemento, Aviao** lista);
Aviao* RetiraPorCodigo(Aviao** lista, int codigo);
