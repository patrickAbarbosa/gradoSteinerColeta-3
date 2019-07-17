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
#include "../Headers/LinhaCSV.h";
#include "../Headers/Fila2.h"

using namespace std;

// Construtor do guloso
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

/*----------------------Algoritmo Guloso--------------------------
  
  O Algoritmo Guloso funciona usando o algoritmo de Prim como
  base e vai calculando o custo enquanto procura a arvore minima 
  de steiner, após finalizado usa uma função auxiliar para montar
  o Grafo a partir do vetor de vertices recebido.
  
  Obs: O algoritmo de prim para ao conseguir um equilibrio entre
  o custo de solucao e o custo a pagar.

------------------------------------------------------------------*/
int Guloso::algoritmoPrim(Vertice *inicial, vector<Aresta*> *vetor_arestas){
  // Guarda os id's já lidos
  vector<string> vetor_vertices;
  // Adiciona ao vetor o vertice inicial
  vetor_vertices.push_back(inicial->getInfo());
  
  // Enquanto o custo a pagar for > que o custo da solução
  while(custoPagar > custoSolucao){
    // Irá auxiliar na escolha da aresta com seu adjacente
    Aresta * aux_aresta = NULL;
    // Recebe o interador do primeiro vertice da lista
    vector<string>::iterator  it = vetor_vertices.begin();
    //
    for(;it != vetor_vertices.end();++it){
      Vertice * w = grafo->getVertices()->buscaVertice(*it);

      if(aux_aresta == NULL)
        aux_aresta = w->getListaAdjacencia();

      while(aux_aresta != NULL && isVector(&vetor_vertices,aux_aresta->getAdjacente()->getInfo()) == true)
        aux_aresta = aux_aresta->getProx(); 

      if(aux_aresta != NULL){
        for(Aresta * aux = aux_aresta->getProx(); aux!= NULL; aux = aux->getProx()){
          int somaA = aux_aresta->getPeso() + custoSolucao + custoPagar - aux_aresta->getAdjacente()->getPeso();
          int somaB = aux->getPeso() + custoSolucao + custoPagar - aux->getAdjacente()->getPeso();

          if(somaA > somaB){
            if(isVector(&vetor_vertices,aux->getAdjacente()->getInfo()) == false)
              aux_aresta = aux;
          }
        }
      }
    }
    if(aux_aresta != NULL){

      Vertice * vertice_auxiliar = aux_aresta->getAdjacente();
      //atualiza custo
      custoSolucao +=aux_aresta->getPeso();
      custoPagar -= vertice_auxiliar->getPeso();
      //adiciona a aresta no vector
      vetor_vertices.push_back(vertice_auxiliar->getInfo());
      vetor_arestas->push_back(aux_aresta);
    }
  }
  return custoPagar+custoSolucao;
}
/*
  isVector() verifica se o valor está contido no vetor
 */
bool Guloso::isVector(vector<string> *vet, string aux){

  if (vet->empty()){
    cout << "Vetor nao alocado!" << endl;
    exit(1);
  }

  for (vector<string>::iterator it = vet->begin(); it != vet->end(); ++it){
    if (*it == aux){
      return true;
    }
  }
  return false;
}

/* ---------------------------------------------------------------------------
  montaGrafo() pega o vetor de arestas recebido e adiciona os vertices,
  arestas, seta o custo e retorna o grafo.
 ---------------------------------------------------------------------------*/
Grafo * Guloso::montaGrafo(vector<Aresta *> * arestas,int custo){

  if(arestas->empty()){
    cout<<"Erro: vetor de arestas vazio!"<<endl;
    return NULL;
  }

  Grafo * resultado = new Grafo();
  Lista * vertices = resultado->getVertices();

  for(vector<Aresta *>::iterator it = arestas->begin(); it != arestas->end(); ++it){ 
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

int Guloso::auxCalculaGuloso(Vertice *inicial, vector<Aresta *> * vetor_arestas){

  // Verifica se o grafo não possui vertice
  if (grafo == NULL)
    return 0;
    
  if (inicial == NULL){
    cout << "ERRO!!! Vertice nao encontrando, será utilizado o primerio vertice da lista" << endl;
    exit(1);
  }

  //Arruma o custo incial
  custoSolucao = 0;
  custoPagar = 0;
  for (Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    custoPagar += aux->getPeso();

  // Calcula Arvore Minima
  return algoritmoPrim(inicial,vetor_arestas);
}

Grafo * Guloso::calculaGuloso(string inicial){

  Vertice *i = grafo->getVertices()->buscaVertice(inicial);
  vector<Aresta *> vetor_arestas;
  int custo = auxCalculaGuloso(i,&vetor_arestas);
  return montaGrafo(&vetor_arestas,custo);
}

/*---------------------------------------------------------------------------
  O Algoritmo Guloso Randomizado funciona recevendo um parametro alfa
  que é utilizado para auxilar na randomização
---------------------------------------------------------------------------*/

int Guloso::auxGulosoRandomizado(float alfa, int numeroInteracoes, vector<Aresta *> *vetor_arestas_melhor){
  clock_t inicio, fim;
  LinhaCSV linha;
  // seta os valores da linha
  linha.instancia = *grafo->arquivoIn;
  linha.classe = "Guloso";
  linha.algoritmo = "gulosoRandomizado";
  linha.numero_vertces = grafo->getNumeroVertices();
  linha.numero_aresta = grafo->getNumeroArestas();
  inicio = clock();
  int semente = 355; //semente utilizada
  srand(semente);

  int nVertices = grafo->getVertices()->getQuantidade();
  int melhor = auxCalculaGuloso(grafo->getVertices()->getPrimeiro(),vetor_arestas_melhor);

  for (int i = 0; i < numeroInteracoes; i++){

    int vertice_randomizado = (int)(alfa * (rand() % nVertices));
    if (vertice_randomizado <= 0)
      vertice_randomizado = (vertice_randomizado * (-1)) + 1;

    Vertice *p = grafo->getVertices()->buscaVertice(to_string(vertice_randomizado));
    vector<Aresta *> vetor_arestas_aux;

    int aux = auxCalculaGuloso(p,&vetor_arestas_aux);

    if (aux < melhor){
      melhor = aux;
      *vetor_arestas_melhor = vetor_arestas_aux;
    }
    fim = clock();
    linha.interacao = i;
    linha.melhor_solucao = to_string(melhor);
    linha.parametro = to_string(alfa);
    linha.tempo_execucao = to_string((1000 * (fim - inicio))/(double)(CLOCKS_PER_SEC));
    grafo->out->imprime(linha);
  }
  return melhor;
}

Grafo * Guloso::gulosoRandomizado(float alfa, int numeroInteracoes)
{
  vector<Aresta *> vetor_arestas;
  int custo = auxGulosoRandomizado(alfa,numeroInteracoes,&vetor_arestas);
  return montaGrafo(&vetor_arestas,custo);
}

// GRASP Reativo

Grafo *Guloso::gulosoRandomizadoReativo(float *alpha, int nAlphas, int periodos, int bloco){
  clock_t inicio, fim;
  LinhaCSV linha;
  // seta os valores da linha
  linha.instancia = *grafo->arquivoIn;
  linha.classe = "Guloso";
  linha.algoritmo = "gulosoRandomizadoReativo";
  inicio = clock();
  if (grafo->getVertices()== NULL)
    return NULL;

  int nInteracoes = 0;
  int custo = -1;
  int nVertices = 0;

  //calcula o custo maximo
  for(Vertice *p = grafo->getVertices()->getPrimeiro(); p != NULL; p = p->getProx())
    custo += p->getPeso();

  // Definição de variáveis para auxiliar
  int n = 0, aleatorio = 0;
  double probabilidade[nAlphas]; //Inicia o verot com distribuição unifome
  for (int i = 0; i < nAlphas; i++)
    probabilidade[i] = 1 / nAlphas;

  float chances[nAlphas];
  float media[nAlphas] = {0};
  float soma[nAlphas] = {0};
  float sum;
  float sum_chances;

  vector<Aresta*> vetor_arestas_melhor; //vetor que fica com o mennor custo()
  vector<Aresta*> vetor_arestas_aux; //vetor auxiliar

  for (int i = 0; i < periodos; i++){

    aleatorio = rand() % 101;
    sum = 0;
    n = 0;
    for (sum += probabilidade[n] * 100; n < nAlphas && sum < aleatorio; n++)
      sum += probabilidade[n] * 100;

    //limpa o vetor auxiliar
    vetor_arestas_aux.clear();

    int custoGrafoAux = auxGulosoRandomizado(alpha[n],100,&vetor_arestas_aux);
    if (custo > custoGrafoAux){
      custo = custoGrafoAux;
      vetor_arestas_melhor = vetor_arestas_aux;
    }
    soma[i] = custo;
    if (i % bloco == 0)
    {
      sum_chances = 0;
      for (int j = 0; j < nAlphas; j++)
      {
        media[j] = soma[j] / i;
        if (media > 0)
          chances[j] = custo / media[j];
        else
          chances[j] = 0.000001;

        sum_chances += chances[j];
      }
    }
    fim = clock();
    linha.interacao = nInteracoes;
    linha.parametro = to_string(alpha[n]);
    linha.tempo_execucao = to_string((1000 * (fim - inicio))/(double)(CLOCKS_PER_SEC));
    grafo->out->imprime(linha);
  }
  return montaGrafo(&vetor_arestas_melhor,custo);
}