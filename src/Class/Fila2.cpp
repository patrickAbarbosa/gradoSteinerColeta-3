#include <iostream>

#include "../Headers/Vertice.h"
#include "../Headers/NoFila2.h"
#include "../Headers/Fila2.h"

Fila2::Fila2()
{
  primeiro = ultimo = NULL;
}

Fila2::~Fila2()
{
  NoFila2 *aux;
  while(primeiro != NULL)
  {
    aux = primeiro;
    primeiro = primeiro->getProX();
    delete aux;
  }
}

bool Fila2::vazia()
{
  if(primeiro == NULL)
    return 1;
  return 0;
}

void Fila2::insere(Vertice *p)
{
  NoFila2 *aux = new NoFila2(p);
  if(primeiro == NULL)
  {
    primeiro = aux;
    ultimo = aux;
  }
  else
  {
    ultimo->setProx(aux);
    ultimo = aux;
  }
}

Vertice* Fila2::retira()
{
  if(primeiro == NULL)
    return NULL;
  Vertice *vertice = primeiro->getInfo();
  NoFila2 *aux = primeiro->getProX();

  delete primeiro;
  primeiro = aux;

  return vertice;
}