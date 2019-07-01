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
  ultimo = 0;
  ultimaAresta = 0;
  //Inicia o vetor de vertices lidos
  vetInfoVertice = new Vertice*[tam-1];

  vetArestaIncidente = new Aresta*[grafo->getNumeroArestas()-1];
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
  if(ultimo != -1){
    for(int i = 0; i < ultimo; i++){
      if(vetInfoVertice[i]->getInfo() == val){
        return i;
      }
    }
  }
  // else
  return -1;
}

bool Guloso::arestaLida(Aresta * a){

  if(ultimaAresta !=-1){
    for(int i = 0; i < ultimaAresta; i++){
      Aresta * b = new Aresta(a->getAdjacente(),a->getOrigem(),a->getPeso());
      if(a == vetArestaIncidente[i] || b == vetArestaIncidente[i]){
        return true;
      }
    }
  }

  return false;

}

void Guloso::auxCalculaGuloso(Vertice *atual){
  if(atual == NULL)
    return;
  cout << "Atual: " << atual->getInfo() << endl;
  // else
  for(Aresta * aresta = atual->getListaAdjacencia(); aresta != NULL; aresta = aresta->getProx()){
    
    while(arestaLida(aresta) && aresta !=NULL)
      aresta = aresta->getProx();
    if(aresta == NULL){
      auxCalculaGuloso(atual->getProx());
    }
    // Guarda o endereço do vertice adjacente;
    Vertice *adjacente = aresta->getAdjacente();
    cout<<"adjacente: "<<adjacente->getInfo()<<endl;
    if(aresta->getPeso() < adjacente->getPeso()){

      int aux = lido(adjacente->getInfo());

      if(aux == -1){

        cout << "ADD: " << adjacente->getInfo() << endl;
        // Atualiza o custo da solução
        custoSolucao +=  aresta->getPeso();
        custoPagar -= adjacente->getPeso();
        // Ultimo passa ser ultimo + 1
        // Atualiza o ultimo valor da lusta com a informação do vertice
        vetInfoVertice[ultimo] = adjacente;
        ultimo++;

        // UltimoNoGuloso de aresta passa ser ultimoNoGuloso + 1
        vetArestaIncidente[ultimaAresta] = aresta;

        cout<<"aresta: "<< vetArestaIncidente[ultimaAresta]->getOrigem()->getInfo()<<" "
                        << vetArestaIncidente[ultimaAresta]->getAdjacente()->getInfo()<<" "
                        << vetArestaIncidente[ultimaAresta]->getPeso()<<endl;
        cout<<"ultima Aresta: "<<ultimaAresta<< endl;

        ultimaAresta++;
        
        Grafo * isso = geraGrafo();
        isso->imprimeGrafoPNG();
        if(custoSolucao < custoPagar)
          auxCalculaGuloso(adjacente);
      }
      else{
        if(aresta->getPeso() < vetArestaIncidente[ultimaAresta]->getPeso()){
          cout << "Troca Aresta: " << adjacente->getInfo() << endl;
          // Atualiza o custo da solução
          custoSolucao -= vetArestaIncidente[aux]->getAdjacente()->getPeso() - aresta->getPeso();

          int m = lido(atual->getInfo());
          int count = 0;
          int arestas [2] = {0,0};
          
          for(int i = 0, j = 0; i < ultimaAresta;i++){
            if(atual == vetArestaIncidente[i]->getOrigem() || atual == vetArestaIncidente[i]->getAdjacente()){
              count++;
              arestas [j] = i;
              j++;
            }
          }
          if( count == 2){
            ultimo--;
            for(int i = m; i<ultimo; i++){ //retira o vertice do vetor
              vetInfoVertice[i] = vetInfoVertice[i+1];
            }
          }
          ultimaAresta = ultimaAresta-2;
          for(int i = arestas[0]; i < ultimaAresta; i++){
              vetArestaIncidente[i] = vetArestaIncidente[i+1];
          }

          vetArestaIncidente[ultimaAresta] = aresta;
          ultimaAresta++;
          Grafo * isso = geraGrafo();
          isso->imprimeGrafoPNG();
          if(custoSolucao < custoPagar)
            auxCalculaGuloso(aresta->getAdjacente());
        }
      }      
    }
  }
}

// Gera o grafo a partir da AGM
Grafo* Guloso::geraGrafo(){

  Grafo *aux = new Grafo();
  // Lista de vertice
  Lista *lista = aux->getVertices();

  // adiciona todos os vertices na solução
  for(int i = 0; i < ultimo; i++)
    lista->insereVertice(vetInfoVertice[i]->getInfo(),vetInfoVertice[i]->getPeso());

  // Adiciona as arestas na solução Arvore Minima
  for(int i = 0; i < ultimaAresta; i++){
    aux->addAresta(vetArestaIncidente[i]->getOrigem()->getInfo(), 
    vetArestaIncidente[i]->getAdjacente()->getInfo(),
    vetArestaIncidente[i]->getPeso());
  }

  return aux;
}

Grafo* Guloso::calculaGuloso(string verticeInicial)
{

  // Verifica se o grafo não possui vertice
  if(grafo == NULL)
    return NULL;

  cout << "Busca o no inicial" << endl;
  // Busca o vertice inicial desejado
  Vertice *inicio = grafo->getVertices()->buscaVertice(verticeInicial);
  // Verifica se o vertice inicial foi encontrado, caso não seja, o calculo da AGM começa
  // a partir do primeiro vertice
  if(inicio == NULL)
    inicio = grafo->getVertices()->getPrimeiro();

  vetInfoVertice[ultimo] = inicio;
  ultimo ++;
  // Calcula Arvore Minima
  auxCalculaGuloso(inicio);
  for(Vertice *aux = grafo->getVertices()->getPrimeiro(); aux != NULL; aux = aux->getProx())
    auxCalculaGuloso(aux);
  // Recebe o grafo gerado a partir dos calculos do Guloso
  Grafo *am = geraGrafo();
  
  // Retorna a arvore minima do Grafo
  am->setCusto(custoSolucao);
  return am; 
}

/*---------------------------------------------------------------------------
  O Algoritmo Guloso Randomizado funciona recevendo um parametro alfa
  que é utilizado para auxilar na randomização
---------------------------------------------------------------------------*/

Grafo * Guloso::gulosoRandomizado (float alfa){

  srand(time(NULL));
  int numeroInterecoes = 1000;  //quantidade de vezes que o algoritmo sera rodado
  Grafo * melhor = calculaGuloso(grafo->getVertices()->getPrimeiro()->getInfo());
  int vertice_randomizado = (rand()%grafo->getNumeroVertices())*alfa; 
  Vertice * p = grafo->buscaVertice(vertice_randomizado);

  for(int i = 0; i<numeroInterecoes;i++){
    
    Grafo * aux = calculaGuloso(p->getInfo());

    if(aux->getCusto() < melhor->getCusto())
      melhor = aux;

    vertice_randomizado = (rand()%grafo->getNumeroVertices()) * alfa;
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