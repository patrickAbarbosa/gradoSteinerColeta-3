#ifndef NOFILA2_H_INCLUDED
#define NOFILA2_H_INCLUDED

#include <iostream>
#include "Vertice.h"

using namespace std;

class NoFila2
{

public:
  NoFila2(Vertice *p){info = p; prox = NULL;};
  ~NoFila2(){};

  void setProx(NoFila2 * prox){this->prox = prox;};
  NoFila2 *getProX(){return prox;};
  Vertice *getInfo(){return info;};

private:
  Vertice *info;
  NoFila2 *prox;
};
#endif // NoFila2_H_INCLUDED#ifndef NOFILA2_H_INCLUDED