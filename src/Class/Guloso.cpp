#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#include "../Headers/Guloso.h"
#include "../Headers/Vertice.h"
#include "../Headers/Aresta.h"
#include "../Headers/Grafo.h"
#include "../Headers/Lista.h"
#include "../Headers/Fila.h"

#include "../Headers/Fila2.h"

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
  for (Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    custoPagar += aux->getPeso();
}

Guloso::~Guloso() {}

bool estaNoVetor(vector<string> *vet, string value)
{
  if (!vet)
  {
    cout << "Vetor nao alocado!" << endl;
    exit(1);
  }

  for (vector<string>::iterator it = vet->begin(); it != vet->end(); ++it)
    if (*it == value)
      return true;
  return false;
}

Grafo * Guloso::algoritmoPrim(Vertice *inicial){

  vector<Aresta *> vetor_arestas;
  vector<Vertice *> vetor_vertices;

  vetor_vertices.push_back(inicial);
  
  while(custoPagar > custoSolucao){

    Vertice * t = vetor_vertices.front();
    Aresta * aux_aresta = NULL;
    vector<Vertice *>::iterator  it = vetor_vertices.begin();

    while(it != vetor_vertices.end()){

      Vertice * w = grafo->getVertices()->buscaVertice(t->getInfo());

      if(aux_aresta == NULL)
        aux_aresta = w->getListaAdjacencia();

      while(aux_aresta != NULL && isVector(vetor_vertices,aux_aresta->getAdjacente()) == true)
        aux_aresta = aux_aresta->getProx(); 

      if(aux_aresta != NULL){
        for(Aresta * aux = aux_aresta->getProx(); aux!= NULL; aux = aux->getProx()){

          int somaA = aux_aresta->getPeso() + custoSolucao + custoPagar - aux_aresta->getAdjacente()->getPeso();
          int somaB = aux->getPeso() + custoSolucao + custoPagar - aux->getAdjacente()->getPeso();
          
          if(somaA > somaB){
            if(isVector(vetor_vertices,aux_aresta->getAdjacente()) == false)
              aux_aresta = aux;
          }
        }
      }
      ++it;
    }
    if(aux_aresta != NULL){
      Vertice * vertice_auxiliar = aux_aresta->getAdjacente();
      //atualiza custo
      custoSolucao +=aux_aresta->getPeso();
      custoPagar -= vertice_auxiliar->getPeso();
      //adiciona a aresta no vector
      vetor_arestas.push_back(aux_aresta);
    }
  }
  Grafo * resultado = montaGrafo(vetor_arestas,custoPagar+custoSolucao);
  return resultado;
}

bool Guloso::isVector(vector<Vertice*> vet, Vertice * aux){
  if (vet.empty())
  {
    cout << "Vetor nao alocado!" << endl;
    exit(1);
  }

  for (vector<Vertice*>::iterator it = vet.begin(); it != vet.end(); ++it)
    if (*it == aux)
      return true;
  return false;
}

Grafo * Guloso::montaGrafo(vector<Aresta *> arestas,int custo){

  if(arestas.empty()){
    cout<<"Erro: vetor de arestas vazio!"<<endl;
    return NULL;
  }

  Grafo * resultado = new Grafo();
  Lista * vertices = resultado->getVertices();

  //Apagar esse teste
  for(vector<Aresta *>::iterator it = arestas.begin(); it != arestas.end(); ++it){ 
    Aresta * a = *it;
    cout<< a->getPeso()<<" "<< a->getOrigem()->getInfo()<<endl;
  }


  for(vector<Aresta *>::iterator it = arestas.begin(); it != arestas.end(); ++it){ 
    //separando as informações da aresta
    Aresta * aux = *it;
    Vertice * origem = aux->getOrigem();
    Vertice * adj = aux->getAdjacente();

    //adiciona os vertices
    if(vertices->buscaVertice(origem->getInfo()) == NULL)
      vertices->insereVertice(origem->getInfo(),origem->getPeso());
    if(vertices->buscaVertice(adj->getInfo()) == NULL)
      vertices->insereVertice(adj->getInfo(),adj->getPeso()); 

    //adiciona a aresta
    origem = vertices->buscaVertice(origem->getInfo());
    adj = vertices->buscaVertice(adj->getInfo());
    
    Aresta * aresta = new Aresta(origem,adj,aux->getPeso());

    origem->insereAresta(aresta);
  }
  resultado->setCusto(custo);

  return resultado;
}

Grafo *Guloso::calculaGuloso(Vertice *inicial){

  // Verifica se o grafo não possui vertice
  if (grafo == NULL)
    return NULL;
    
  if (inicial == NULL)
  {
    cout << "ERRO!!! Vertice nao encontrando, será utilizado o primerio vertice da lista" << endl;
    inicial = grafo->getVertices()->getPrimeiro();
    exit(1);
  }

  //Arruma o custo incial
  custoSolucao = 0;
  custoPagar = 0;
  for (Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    custoPagar += aux->getPeso();

  // Calcula Arvore Minima
  return algoritmoPrim(inicial);
}

/*---------------------------------------------------------------------------
  O Algoritmo Guloso Randomizado funciona recevendo um parametro alfa
  que é utilizado para auxilar na randomização
---------------------------------------------------------------------------*/

Grafo *Guloso::gulosoRandomizado(float alfa, int numeroInteracoes)
{
  int semente = 0; //semente utilizada
  srand(semente);

  int nVertices = grafo->getVertices()->getQuantidade();
  Grafo *melhor = calculaGuloso(grafo->getVertices()->getPrimeiro());

  for (int i = 0; i < numeroInteracoes; i++)
  {
    int vertice_randomizado = (int)(alfa * (rand() % nVertices));
    if (vertice_randomizado <= 0)
      vertice_randomizado = (vertice_randomizado * (-1)) + 1;
    Vertice *p = grafo->getVertices()->buscaVertice(to_string(vertice_randomizado));
    if(p != NULL)
      cout << "oi 3->" << p->getInfo() << endl;
    Grafo *aux = calculaGuloso(p);
    cout<<"oi 3"<<endl;

    if (aux->getCusto() < melhor->getCusto())
    {
      Grafo *lixo = melhor;
      melhor = aux;
      delete lixo;
      cout << "deletou lizo" << endl;
    }
    cout << "oi 3.1" << endl;
  }
  cout << "3.2" << endl;
  cout<<"custo melhor"<<melhor->getCusto()<<endl;
  return melhor;
}

// https://bmcbioinformatics.biomedcentral.com/articles/10.1186/1471-2105-10-S1-S27
//// PDF: https://bmcbioinformatics.biomedcentral.com/track/pdf/10.1186/1471-2105-10-S1-S27

// GRASP Reativo

Grafo *Guloso::gulosoRandomizadoReativo(float *alpha, int nAlphas, int periodos, int bloco){

  int nInteracoes = 0;
  int custo = -1;
  int nVertices = 0;
  Lista *aux = grafo->getVertices();

  if (grafo->getVertices() == NULL)
    return NULL;
  float custoMax = 0;
  for (Vertice *p = aux->getPrimeiro(); p != NULL; p = p->getProx())
    custoMax += p->getPeso();
  // Maior custo da solução
  custo = custoMax;
  // Definição de variáveis para auxiliar
  int n = 0, aleatorio = 0;
  double probabilidade[nAlphas]; //Inicia o verot com distribuição unifome
  for (int i = 0; i < nAlphas; i++)
    probabilidade[i] = 1 / nAlphas;
  cout<<"aqui 0"<<endl;
  float chances[nAlphas];
  float media[nAlphas] = {0};
  float soma[nAlphas] = {0};
  float sum;
  float sum_chances;

  Grafo *result = NULL;
  for (int i = 0; i < periodos; i++){

    aleatorio = rand() % 101;
    sum = 0;
    n = 0;
    for (sum += probabilidade[n] * 100; n < nAlphas && sum < aleatorio; n++)
      sum += probabilidade[n] * 100;

    cout << "Alpha: " << alpha[n] << endl;
    cout << "Interacao: " << i + 1 << endl;
    Grafo *grafoAux = gulosoRandomizado(alpha[n], 100); //numero de interações do randomizado
    cout<<"saiu aqui"<<endl;
    int custoAux = grafoAux->getCusto();

    if (result && custo)
    {
      if (custo > custoAux)
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
    if (i % bloco == 0)
    {
      sum_chances = 0;
      for (int j = 0; j < nAlphas; j++)
      {
        cout<<"aqui 5"<<endl;
        media[j] = soma[j] / i;
        if (media > 0)
          chances[j] = custo / media[j];
        else
          chances[j] = 0.000001;

        sum_chances += chances[j];
      }
    }
  }
  return NULL;
}