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
  int pista;
  char *codigo;
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
