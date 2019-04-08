#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include <iostream>

class Matriz{
public:
  Matriz(int tam);
  ~Matriz();
    
  void insereAresta(int x, int y, int peso);
  void removeAresta(int x, int y);

  void imprime();

private:
  int **mat;
  int n;

  bool validaPosicao(int x, int y);
};
#endif

  