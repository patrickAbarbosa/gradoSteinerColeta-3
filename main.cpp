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

int main(){
  cout << "Grupo 03 - Steiner com Coleta de Prêmios" << endl;
  
  Grafo *a;

  a =  new Grafo("file.txt");
  delete a;
  return 0;
}
