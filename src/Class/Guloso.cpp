#include <iostream>

#include "../Headers/Guloso.h"
#include "../Headers/Vertice.h"
#include "../Headers/Aresta.h"
#include "../Headers/Grafo.h"
#include "../Headers/Lista.h"

using namespace std;

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

Guloso::Guloso(Grafo *g)
{
  grafo = g;
  tam = grafo->getVertices()->getQuantidade();
  // Iniciamos o custo da solução em 0
  custoSolucao = 0;
  // Iniciamos o custo a ser pago em 0
  custoPagar = 0;
  for(Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    custoPagar += aux->getPeso();
}

Guloso::~Guloso(){}

Grafo * Guloso::algoritmoPrim(Vertice * inicial){

  Grafo * arvore = new Grafo ();
  Lista * arv_vertices = arvore->getVertices();

  arv_vertices->insereVertice(inicial->getInfo(),inicial->getPeso());

  while(custoPagar > custoSolucao){
    Vertice * t = arv_vertices->getPrimeiro();
    Aresta * aux_aresta = NULL;

    while(t != NULL){
      Vertice * w = grafo->getVertices()->buscaVertice(t->getInfo());
      if(aux_aresta == NULL)
        aux_aresta = w->getListaAdjacencia();

      while(aux_aresta != NULL && arv_vertices->buscaVertice(aux_aresta->getAdjacente()->getInfo()) != NULL)
        aux_aresta = aux_aresta->getProx(); 

      if(aux_aresta != NULL){
        for(Aresta * aux = aux_aresta->getProx(); aux!= NULL; aux = aux->getProx()){
          if(aux_aresta->getPeso() > aux->getPeso() && custoPagar > custoSolucao){
            if(arv_vertices->buscaVertice(aux->getAdjacente()->getInfo()) == NULL)
              aux_aresta = aux;
          }
        }
      }
      t = t->getProx();
    }
    if(aux_aresta != NULL){
      Vertice * vertice_auxiliar = aux_aresta->getAdjacente();
      arv_vertices->insereVertice(vertice_auxiliar->getInfo(),vertice_auxiliar->getPeso());
      //atualiza custo
      custoSolucao +=aux_aresta->getPeso();
      custoPagar -= vertice_auxiliar->getPeso();
      arvore->addAresta(aux_aresta->getOrigem()->getInfo(),aux_aresta->getAdjacente()->getInfo(),aux_aresta->getPeso());
    }
  }
  return arvore; 
}

Grafo* Guloso::calculaGuloso(string verticeInicial){

  // Verifica se o grafo não possui vertice
  if(grafo == NULL)
    return NULL;

  // Busca o vertice inicial desejado
  Vertice *inicio = grafo->getVertices()->buscaVertice(verticeInicial);
  // Verifica se o vertice inicial foi encontrado, caso não seja, o calculo da AGM começa
  // a partir do primeiro vertice
  if(inicio == NULL){
    cout<<"ERRO!!! Vertice nao encontrando, será utilizado o primerio vertice da lista"<<endl;
    inicio = grafo->getVertices()->getPrimeiro();
  }
  // Calcula Arvore Minima
  Grafo * aux = algoritmoPrim(inicio);
  aux->setCusto(custoSolucao);
  // Retorna a arvore minima do Grafo
  return aux; 
}

/*---------------------------------------------------------------------------
  O Algoritmo Guloso Randomizado funciona recevendo um parametro alfa
  que é utilizado para auxilar na randomização
---------------------------------------------------------------------------*/

Grafo * Guloso::gulosoRandomizado (float alfa){

  // Iniciamos o custo da solução em 0
  custoSolucao = 0;
  // Iniciamos o custo a ser pago em 0
  custoPagar = 0;
  for(Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    custoPagar += aux->getPeso();
  int semente = 0;
  srand(0);
  int numeroInterecoes = 1000;  //quantidade de vezes que o algoritmo sera rodado
  Grafo * melhor = calculaGuloso(grafo->getVertices()->getPrimeiro()->getInfo());
  int vertice_randomizado = int(alfa*rand())%grafo->getNumeroVertices();

  while(vertice_randomizado < 0)
    vertice_randomizado = int(alfa*rand())%grafo->getNumeroVertices();

  Vertice * p = grafo->buscaVertice(vertice_randomizado);
  for(int i = 0; i<numeroInterecoes;i++){
    Grafo * aux = calculaGuloso(p->getInfo());

    cout<<"aux: "<<aux->getCusto()<<endl;
    cout<<"melhor: "<<melhor->getCusto()<<endl;

    if(aux->getCusto() < melhor->getCusto())
      melhor = aux;

    while(vertice_randomizado < 0)
      vertice_randomizado = int(alfa*rand())%grafo->getNumeroVertices();
    p = grafo->buscaVertice(vertice_randomizado);
  }

  return melhor;
}

// https://bmcbioinformatics.biomedcentral.com/articles/10.1186/1471-2105-10-S1-S27
//// PDF: https://bmcbioinformatics.biomedcentral.com/track/pdf/10.1186/1471-2105-10-S1-S27

// GRASP Reativo
/*
Grafo *Grafo::gulosoRandomizadoReativo(float *alpha, int nAlphas, int periodos, int bloco)
{
  int nInteracoes = 0;
  int  custo = -1;
  int nVertices = 0;
  
  if(vertices == NULL)
    return NULL;
  if(vertices != NULL && numeroArestas == 0)
  {
    cout << "Alpha: 0" << endl;
    Grafo *result = new Grafo();
    Vertice *maiorGrau = vertices->getMaiorGrau(); 
    result->vertices->insereVertice(maiorGrau->getInfo(), maiorGrau->getPeso());
    return result;
  }
  float custoMax = 0;
  for(Vertice * p = vertices->getPrimeiro(); p != NULL; p = p->getProx())
    custoMax += p->getPeso();
  // Maior custo da solução
  custo = custoMax;
  // Definição de variáveis para auxiliar
  int n = 0, aleatorio = 0;
  float probabilidade[nAlphas] = { 1/ nAlphas }; //Inicia o verot com distribuição unifome
  float chances[nAlphas];
  float media[nAlphas] = {0};
  float soma[nAlphas] = {0};
  float sum;
  float sum_chances;
  
  Grafo *result = NULL;
  for(int i = 0; i < periodos; i++)
  {
    aleatorio = rand() % 101;
    sum = 0;
    n = 0;
    for(sum += probabilidade[n] * 100; n < nAlphas && sum < aleatorio; n++)
      sum += probabilidade[n] * 100;
    
    cout << "Alpha: " << alpha[n] << endl;
    cout << "Interacao: " << i + 1 << endl;
    Grafo *grafoAux = gulosoRandomizado(alpha[n]);
    int custoAux = custoSteiner(grafoAux);
    
    if(result && custo)
    {
      if(custo > custoAux)
      {
        custo = custoAux;
        delete result;
        result = grafoAux;
      }
      else 
        delete grafoAux;
    }
    else
    {
      custo = custoAux;
      result = grafoAux;
    }
    soma[i] = custo;
    if(i % bloco == 0)
    {
      sum_chances = 0;
      for(int j = 0; j < nAlphas; j++)
      {
        media[j] = soma[j] / i;
        if(media > 0)
          chances[j] = custo / media[j];
        else
          chances[j] = 0.000001;
        
        sum_chances += chances[j];
      }
    }
  }
  return NULL; 
}
*/