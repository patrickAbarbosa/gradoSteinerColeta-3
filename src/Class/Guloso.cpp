#include <iostream>

#include "../Headers/Guloso.h"
#include "../Headers/Vertice.h"
#include "../Headers/Aresta.h"
#include "../Headers/Grafo.h"
#include "../Headers/NoGuloso.h"

using namespace std;

Guloso::Guloso(Grafo *g)
{
  grafo = g;
  tam = grafo->getVertices()->getQuantidade();
  ultimo = -1;
  ultimoNoGuloso = -1;
  //Inicia o vetor de vertices lidos
  vetInfoVertice = new string[tam];
  //Inicia o vetor de aresta no grafo
  vetArestaIncidente = new NoGuloso[tam - 1];
  // Iniciamos o custo a ser pago em 0
  custoPagar = 0;
  for(Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    custoPagar += aux->getPeso();
}

Guloso::~Guloso()
{
  delete [] vetInfoVertice;
}

int Guloso::lido(string val)
{
  if(ultimo != -1)
    for(int i = 0; i < ultimo; i++)
      if(vetInfoVertice[i] == val)
        return i;
  
  // else
  return -1;
}

void Guloso::auxCalculaGuloso(Vertice *atual)
{
  if(atual == NULL)
    return;
  
  // else
  for(Aresta *aresta = atual->getListaAdjacencia(); aresta != NULL; aresta = aresta->getProx())
  {
    // Guarda o endereço do vertice adjacente;
    Vertice *adjacente = aresta->getAdjacente();
    
    if(aresta->getPeso() < adjacente->getPeso())
    {
      int aux = lido(adjacente->getInfo());

      if(aux == -1)
      {
        // Atualiza o custo da solução
        custoSolucao +=  aresta->getPeso();
        // Atualiza custo a pagar de penalidade
        custoPagar -=
        // Ultimo passa ser ultimo + 1
        ultimo++;
        // Atualiza o ultimo valor da lusta com a informação do vertice
        vetInfoVertice[ultimo] = adjacente->getInfo();
        
        // UltimoNoGuloso de aresta passa ser ultimoNoGuloso + 1
        ultimoNoGuloso++;
        vetArestaIncidente[ultimoNoGuloso].origem = atual;
        vetArestaIncidente[ultimoNoGuloso].destino = aresta;
        
      }
      else
      {
        if(aresta->getPeso() < vetArestaIncidente[aux].destino->getPeso())
        {
          // Atualiza o custo da solução
          custoSolucao -=  vetArestaIncidente[aux].destino->getPeso() - aresta->getPeso();
          vetArestaIncidente[aux].origem = atual;
          vetArestaIncidente[aux].destino = aresta;
        }
      }
      auxCalculaGuloso(adjacente);
    }
  }
}

// Gera o grafo a partir da AGM
Grafo* Guloso::geraGrafo()
{
  
}

/*----------------------Algoritmo Guloso--------------------------
  
  O Algoritmo Guloso funciona usando ...
  




  Também temos uma função auxiliar custoSteiner(Grafo * arvore),
  que é utilizada para encontrar o custo da arvore passada em 
  relacao ao original.

 --------------------------Pseudocódigo--------------------------

  Guloso(Vertice * p, Grafo * arvore):

    se condição de parada então
      retorne custoSteiner(resultado); //calcula e retorna o custo da arvore criada
    fim-se

    adjacentes <- p->getListaAdjacencia();
    melhor <- adjacentes;
    gasto_melhor <- melhor->getAdjacente()->getPeso() - melhor->getPeso();

    enquanto adjacentes != NULL faça

      gasto_outro <- adjacentes->getAdjacente()->getPeso() - adjacentes->getPeso();

      se gasto_melhor > gasto_outro então    
        melhor <- adjacentes;
        gasto_melhor <- gasto_outro;
      fim-se
      
      adjacentes <- adjacentes->getProx();              
    fim-enquanto

    listaVertices <- resultado->getVertices();
    melhorVertice <- melhor->getAdjacente();

    se o melhorVertice encontrado ja está na solucao então  
      //ver a melhor forma de optimizar
    fim-se
    senão
      insere o melhor vertice na arvore;
      cria aresta existente entre os vertices;
      retorne Guloso(melhorVertice, arvore);       
    fim-se
  fim

---------------------------------------------------------------------------*/

Grafo* Guloso::calculaGuloso(string verticeInicial)
{
  // Verifica se o grafo não possui vertice
  if(grafo->getVertices()->getPrimeiro() == NULL)
    return NULL;

  // Busca o vertice inicial desejado
  Vertice *inicio = grafo->getVertices()->buscaVertice(verticeInicial);

  // Verifica se o vertice inicial foi encontrado, caso não seja, o calculo da AGM começa
  // a partir do primeiro vertice
  if(inicio == NULL)
    inicio = grafo->getVertices()->getPrimeiro();

  return NULL;
}