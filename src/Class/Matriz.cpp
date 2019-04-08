#include <iostream>

#include "../Headers/Matriz.h"

using namespace std;

Matriz::Matriz(int tam)
{
  if(tam < 1)
  {
    cout << "Tamanho invalido do grafo!" << endl;
    return;
  }
  n = tam;
  
  mat =  new int*[n];

  for(int i = 0; i <  n; i++)
    mat[i] =  new int[n];
}

Matriz::~Matriz()
{
  for(int i = 0; i <  n; i++)
    delete [] mat[i];
  delete [] mat;
}

bool Matriz::validaPosicao(int x, int y)
{
  if(x >= 0 && y >=0 && x < n && y < n)
    return true;
  else  
    return false;
}

void Matriz::insereAresta(int x, int y, int peso) 
{
  if(validaPosicao(x, y))
  {
    mat[x][y] = peso;
    mat[y][x] = peso;
  }
  else
    cout << "Posicao invalida!" << endl;
}

void Matriz::removeAresta(int x, int y)
{
  if(validaPosicao(x, y))
    mat[x][y] = 0;
  else
    cout << "Posicao invalida!" << endl;
}

void Matriz::imprime()
{
  if(n == 0)
    cout << "Matriz de adjacencia vazia" << endl;

  else
  {
    for(int i = 0; i<n; i++)
    {
      for(int j = 0; j<n; j++)
        cout << mat[i][j] << ", " << endl;
      cout << endl;
    }
  } 
}