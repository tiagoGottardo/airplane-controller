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

typedef enum {
  TEMPESTADE,
  NEBLINA,
  TURBULENCIA
} TipoDesventura;

typedef struct Desventura {
  TipoDesventura tipo;
  int turno;
  struct Desventura* proximo;
} Desventura;

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

typedef struct Local {
  Aviao** pista;
  int quantidadeDePistas;
  Aviao* ceu;
  Aviao* destino;
} Local;

extern Local local;
extern Desventura* desventura;

Aviao* InsereNoFim(Aviao **cabeca);
Aviao* RetiraNoInicio(Aviao** cabeca);
Aviao* RetiraPorCodigo(Aviao** lista, int codigo);
void MostraLista(Desventura* pista);
void IndexaDesventuraOrdenado(Desventura* elemento, Desventura** lista);
void AdicionaAviao (Aviao** pista, int value);
void IndexaNoInicio(Aviao* elemento, Aviao** lista);
void IndexaOrdenado(Aviao* elemento, Aviao** lista);
void Reordena(Aviao** lista, int codigo);
void LogGlobal();
void DesalocaAviao(Aviao** lista);
void InsereDesventura(TipoDesventura tipo, int turno);
void DeletaDesventura(Desventura** cabeca);
void DesalocaDesventura(Desventura** lista);
