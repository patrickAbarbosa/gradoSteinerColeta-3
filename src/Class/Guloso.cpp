#include <iostream>

#include "../Headers/Guloso.h"
#include "../Headers/Vertice.h"
#include "../Headers/Aresta.h"
#include "../Headers/Grafo.h"
#include "../Headers/Lista.h"

using namespace std;

Guloso::Guloso(Grafo *g)
{
  grafo = g;
  tam = grafo->getVertices()->getQuantidade();
  ultimo = -1;
  ultimoNoGuloso = -1;
  //Inicia o vetor de vertices lidos
  vetInfoVertice = new Vertice*[tam];
  //Inicia o vetor de aresta no grafo
  vetArestaIncidente = new Aresta*[tam - 1];
  // Iniciamos o custo da solução em 0
  custoSolucao = 0;
  // Iniciamos o custo a ser pago em 0
  custoPagar = 0;
  for(Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    custoPagar += aux->getPeso();
}

Guloso::~Guloso()
{
  delete [] vetInfoVertice;
  delete [] vetArestaIncidente;
}

int Guloso::lido(string val)
{
  if(ultimo != -1)
    for(int i = 0; i < ultimo; i++)
      if(vetInfoVertice[i]->getInfo() == val)
        return i;
  
  // else
  return -1;
}

void Guloso::auxCalculaGuloso(Vertice *atual)
{
  if(atual == NULL)
    return;
  cout << "Atual: " << atual->getInfo() << endl;
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
        // Ultimo passa ser ultimo + 1
        ultimo++;
        // Atualiza o ultimo valor da lusta com a informação do vertice
        vetInfoVertice[ultimo] = adjacente;
        
        // UltimoNoGuloso de aresta passa ser ultimoNoGuloso + 1
        ultimoNoGuloso++;
        vetArestaIncidente[ultimoNoGuloso] = aresta;
        auxCalculaGuloso(adjacente);
      }
      else
      {
        if(adjacente->getInfo() != vetInfoVertice[0]->getInfo() && aresta->getPeso() < vetArestaIncidente[aux]->getPeso())
        {
          // Atualiza o custo da solução
          custoSolucao -=  vetArestaIncidente[aux]->getAdjacente()->getPeso() - aresta->getPeso();
          vetArestaIncidente[aux] = aresta;
        }
      }      
    }
  }
}

// Gera o grafo a partir da AGM
Grafo* Guloso::geraGrafo()
{
  Grafo *aux = new Grafo();
  // Lista de vertice
  Lista *lista = aux->getVertices();

  // adiciona todos os vertices na solução
  for(int i = 0; i < ultimo; i++)
  {
    cout << "Vertice: " << vetInfoVertice[i]->getInfo();
    cout << " Peso: " << vetInfoVertice[i]->getPeso() << endl;
    lista->insereVertice(vetInfoVertice[i]->getInfo(), vetInfoVertice[i]->getPeso());
  }
    
  
  // Adiciona as arestas na solução AGM
  for(int i = 1; i < ultimoNoGuloso; i++)
  {
    cout << "Origem: " << vetArestaIncidente[i]->getOrigem()->getInfo();
    cout << " Destino: " << vetArestaIncidente[i]->getAdjacente()->getInfo() << endl;
    aux->addAresta(vetArestaIncidente[i]->getOrigem()->getInfo(), 
    vetArestaIncidente[i]->getAdjacente()->getInfo(),
    vetArestaIncidente[i]->getPeso());
  }
    
  // Retorna Grafo gerado 
  return aux;
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
  if(grafo == NULL)
    return NULL;

  cout << "Busca o no inicial" << endl;
  // Busca o vertice inicial desejado
  Vertice *inicio = grafo->getVertices()->buscaVertice(verticeInicial);
  cout << "Oi" << endl;
  // Verifica se o vertice inicial foi encontrado, caso não seja, o calculo da AGM começa
  // a partir do primeiro vertice
  if(inicio == NULL)
    inicio = grafo->getVertices()->getPrimeiro();

  cout << "Oi1" << endl;
  // Calcula AMG
    auxCalculaGuloso(inicio);
  for(Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    auxCalculaGuloso(aux);
  cout << "Oi2" << endl;
  // Recebe o grafo gerado a partir dos calculos do Guloso
  Grafo *agm = geraGrafo();
  
  // Retorna a agm do Grafo
  return agm;
}