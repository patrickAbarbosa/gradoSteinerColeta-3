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

int main(int argc, char *argv[]){
  cout << "Grupo 03 - Steiner com Coleta de Prêmios" << endl;
  
  Grafo *a;
  for(int i = 0; i<argc; i++){
    cout << "i: " << argv[i] << endl;
  }
  a =  new Grafo("K400.3.con.red");
  //a->menu();
  cout << "Busca Profunda" << endl;
  a->buscaPorProfundidade("210");
  delete a;
  return 0;
}
