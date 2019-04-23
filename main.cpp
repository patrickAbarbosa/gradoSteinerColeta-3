/*
 * Graph Stenier 
 * 
 * Local: Federal Univercity of Juiz de Fora
 * Authors: Leonardo Nunes and Patrick Barbosa
 * Course: Science Computer
 * 
 * Licence: MIT
 */

#include <iostream>
#include "src/Headers/Grafo.h"

using namespace std;

int main(int argc, char *argv[])
{
  cout << "Grupo 03 - Steiner com Coleta de Prêmios" << endl;

  Grafo *a = NULL;

  switch (argc)
  {
  case 1:
    a = new Grafo();
    break;
  case 2:
    a = new Grafo(argv[1]);
    break;
  case 3:
    a = new Grafo(argv[1], argv[2]);
    break;
  default:
    break;
  }

  if (a)
  {
    a->menu();
    delete a;  
  }
  return 0;
}
