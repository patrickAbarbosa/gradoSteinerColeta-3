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
#include "src/Headers/Guloso.h"
#include "src/Headers/GeraCsv.h"
#include <thread>

#include <sys/resource.h>
#include <sys/time.h>

using namespace std;

int main(int argc, char *argv[])
{
  struct rlimit rl;

  // First get the time limit on CPU
  getrlimit(RLIMIT_CPU, &rl);

  printf("\n Default value is : %lld\n", (long long int)rl.rlim_cur);

  // Change the time limit
  rl.rlim_cur = 1;

  // Now call setrlimit() to set the
  // changed value.
  setrlimit(RLIMIT_CPU, &rl);

  // Again get the limit and check
  getrlimit(RLIMIT_CPU, &rl);

  printf("\n Default value now is : %lld\n", (long long int)rl.rlim_cur);

  printf("Grupo 03 - Steiner com Coleta de Prêmios\n");

  Grafo *a = NULL;
  GeraCsv *geradorDeArquivo = NULL;
  switch (argc)
  {
  case 1:
    geradorDeArquivo = new GeraCsv("teste");
    a = new Grafo("K400.3.con.red", geradorDeArquivo);
    break;
  case 2:
    a = new Grafo(argv[1]);
    break;
  case 3:
    geradorDeArquivo = new GeraCsv(argv[2]);
    a = new Grafo(argv[1], geradorDeArquivo);
    break;
  case 4:
    geradorDeArquivo = new GeraCsv(argv[2]);
    a = new Grafo(argv[1], geradorDeArquivo, argv[3]);
    break;
  default:
    break;
  }
  cout << "Arestas: " << a->getNumeroArestas() <<endl;
  //a->imprimeGrafoPNG();
  return 0;
  //Guloso guloso(a);
  Guloso guloso(a);


  float vet [10]={0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};

  Grafo * teste = guloso.calculaGuloso("5");
  teste->imprimeGrafoPNG();

  teste = guloso.gulosoRandomizado(0.50,2000);
  teste->imprimeGrafoPNG();

  teste = guloso.gulosoRandomizadoReativo(vet,10,2000,100);
  teste->imprimeGrafoPNG();
  

  if (a)
  {
    //a->menu();
    delete a;
  }
  return 0;
}
