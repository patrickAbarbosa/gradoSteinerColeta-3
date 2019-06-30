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
  ultimo = 0;
  ultimoNoGuloso = 0;
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
  if(ultimo != 0)
    for(int i = 0; i < ultimo; i++)
      if(vetInfoVertice[i]->getInfo() == val)
        return i;
  
  // else
  return -1;
}

void Guloso::auxCalculaGuloso(Vertice *atual, int *n)
{
  if(atual == NULL)
    return;
  cout << "Atual: " << atual->getInfo() << endl;
  // else
  for(Aresta *aresta = atual->getListaAdjacencia(); aresta != NULL; aresta = aresta->getProx())
  {
    (*n)++;
    // Guarda o endereço do vertice adjacente;
    Vertice *adjacente = aresta->getAdjacente();
    if(adjacente == NULL)
      cout << "Adjacente = NULL" << endl;
      cout << "Peso da aresta: " << aresta->getPeso() << endl;
    if(aresta->getPeso() < adjacente->getPeso() || custoSolucao < custoPagar)
    {
      cout << "# if: "<< adjacente->getInfo() << endl;
      int aux = lido(adjacente->getInfo());
      cout << "Está no vetor ? aux: " << aux;
      if(aux >= 0)
        cout << ", info: " << vetInfoVertice[aux]->getInfo();
      cout << endl;
      if(aux == -1)
      {
        cout << "ADD: " << adjacente->getInfo() << endl;
        
        // Atualiza o custo da solução
        custoSolucao +=  aresta->getPeso();
        custoPagar -= adjacente->getPeso();
        // Ultimo passa ser ultimo + 1
        // Atualiza o ultimo valor da lusta com a informação do vertice
        vetInfoVertice[ultimo] = adjacente;
        ultimo++;
        
        // UltimoNoGuloso de aresta passa ser ultimoNoGuloso + 1
        vetArestaIncidente[ultimoNoGuloso] = aresta;
        ultimoNoGuloso++;
        auxCalculaGuloso(adjacente, n);
      }
      else if(aux > 0)
      {
        cout << "Está no vetor" << endl;
        cout << "Informações da aresta: {" << endl;
        cout << "\torigem: " << aresta->getOrigem() << ", info: " << aresta->getOrigem()->getInfo() << "," << endl;
        cout << "\tdestino: " << aresta->getAdjacente() << ", info: " << aresta->getAdjacente()->getInfo() << "," << endl;
        cout << "\tpeso: " << aresta->getPeso() << endl;
        cout << "}" << endl;
        cout << "Vetor de aresta: {" << endl;
        cout << "\tendereco: " << vetArestaIncidente[aux]<< endl;
        cout << "\tdestino: " << vetArestaIncidente[aux]->getAdjacente() << endl;
        cout << "\tdestino: " << vetArestaIncidente[aux]->getAdjacente() << ", info: " << vetArestaIncidente[aux]->getAdjacente()->getInfo() << "," << endl;
        cout << "\tpeso: " << vetArestaIncidente[aux]->getPeso() << endl;
        cout << "}" << endl;
        if(aresta->getPeso() < vetArestaIncidente[aux]->getPeso())
        {
          cout << "Troca Aresta: " << adjacente->getInfo() << endl;
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
    lista->insereVertice(vetInfoVertice[i]->getInfo(), vetInfoVertice[i]->getPeso());
  
  // Adiciona as arestas na solução AGM
  for(int i = 1; i < ultimoNoGuloso; i++)
    aux->addAresta(vetArestaIncidente[i]->getOrigem()->getInfo(), 
                   vetArestaIncidente[i]->getAdjacente()->getInfo(),
                   vetArestaIncidente[i]->getPeso());

  // Retorna Grafo gerado 
  return aux;
}


Grafo* Guloso::calculaGuloso(string verticeInicial)
{

  // Verifica se o grafo não possui vertice
  if(grafo == NULL)
    return NULL;

  // Busca o vertice inicial desejado
  Vertice *inicio = grafo->getVertices()->buscaVertice(verticeInicial);

  // Verifica se o vertice inicial foi encontrado, caso não seja, o calculo da AGM começa
  // a partir do primeiro vertice
  if(inicio == NULL)
    inicio = grafo->getVertices()->getPrimeiro();

  // adiciona o inicio da AGM
  vetInfoVertice[0] = inicio;
  ultimo = 1;
  ultimoNoGuloso = 1;
  // Calcula AMG
  int n = 0;
  auxCalculaGuloso(inicio, &n);
  cout << "# 139" <<endl;
  //for(Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    //auxCalculaGuloso(aux);
  // Recebe o grafo gerado a partir dos calculos do Guloso
  Grafo *agm = geraGrafo();
  
  // Retorna a agm do Grafo
  return agm;
}