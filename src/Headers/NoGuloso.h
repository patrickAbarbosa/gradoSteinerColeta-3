#include "Vertice.h"
#include "Aresta.h"

// NoSolucaoGulosa
typedef struct
{ 
  // Guarda o endereço do vertice que se encontra no resultado
  Vertice *origem;
  // Guarda a aresta com o vertice de destino
  Aresta *destino;
} NoGuloso; 