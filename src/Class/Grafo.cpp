#include <iostream>
#include <fstream> // Open File
#include <string>
#include <sstream>
#include <vector>

#include "../Headers/Grafo.h"
#include "../Headers/Lista.h"
#include "../Headers/Data.h"
#include "../Headers/Fila.h"
#include "../Headers/Vertice.h"

using namespace std;

// Construtores e destrutor da classe
//
//

/*
 * Grafo() irá construir a classe quando não precisar
 * fazer a leitura de um arquivo de entrada para um 
 * grafo, assim, necessitando que o usuário adicione
 * arestas e vertices para proceguir com  as funções.
 */
Grafo::Grafo()
{
  cout << "Construindo Grafo" << endl;

  vertices = new Lista();

  arquivoIn = NULL;
  arquivoOut = NULL;
  menorValor = NULL;
  ehDigrafo = false;
  numeroArestas = 0;
  numeroVertices = 0;
  quantidadeGrausZero = 0;
  db = new Data();
}

/*
 * Grafo(arquivoIn) espera o local do arquivo para 
 * leitura, assim construindo o grafo a partir desse
 */
Grafo::Grafo(string in)
{
  cout << "Construindo Grafo" << endl;

  vertices = new Lista();

  arquivoIn = new string;
  *arquivoIn = in;

  arquivoOut = NULL;
  ehDigrafo = false;
  numeroArestas = 0;
  numeroVertices = 0;
  quantidadeGrausZero = 0;
  db = new Data();
  leArquivo();
}

/*
 * Grafo(arquivoIn, arquivoOut) recebe o local do 
 * arquivo para leitura para contruir o grafo a partir
 * dos dados nele e o local do arquivo de saída das
 * análiizes do processamento
 */
Grafo::Grafo(string in, string out)
{
  cout << "Construindo Grafo" << endl;

  vertices = new Lista();

  arquivoIn = new string;
  *arquivoIn = in;

  arquivoOut = new string;
  *arquivoOut = out;

  ehDigrafo = false;
  numeroArestas = 0;
  numeroVertices = 0;
  quantidadeGrausZero = 0;
  db = new Data();
  leArquivo();
}

/*
 * Grafo(arquivoIn, arquivoOut, ehDigrafo) recebe o local do 
 * arquivo para leitura para contruir o grafo a partir
 * dos dados nele e o local do arquivo de saída das
 * análiizes do processamento e se é o Grafo é um digrafo.
 */
Grafo::Grafo(string in, string out, string ehDigrafo)
{
  cout << "Construindo Grafo" << endl;

  vertices = new Lista();

  arquivoIn = new string;
  *arquivoIn = in;

  arquivoOut = new string;
  *arquivoOut = out;

  if (ehDigrafo == "1")
    ehDigrafo = true;
  else
    ehDigrafo = false;
  numeroArestas = 0;
  numeroVertices = 0;
  db = new Data();
  leArquivo();
}
/*
 * ~Grafo() analiza memória alocada dinamicamente
 * que está sendo utilizado pela classe para 
 * desalocar e liberar o espaço.
 */
Grafo::~Grafo()
{
  cout << "Destruindo Grafo" << endl;
  delete db;
  delete vertices;

  if (arquivoIn)
    delete arquivoIn;
  if (arquivoOut)
    delete arquivoOut;
}
//
//
// End Contrutores e Destrutores

/*
 * leArquivo() faz a leitura do arquivo
 * de entrada e coloca em variáveis 
 * para o processamento
 */
void Grafo::leArquivo()
{
  fstream file;

  file.open(*arquivoIn);

  if (file.is_open())
  {
    bool link = false;
    while (!file.eof())
    {
      string str;
      getline(file, str);
      if (str[0] >= '0' && str[0] <= '9')
      {
        stringstream line(str);
        if (link)
        {
          int lixo, peso;
          string verticeA, verticeB;

          line >> lixo;
          line >> verticeA >> verticeB >> peso;

          addAresta(verticeA, verticeB, peso);
        }
        else
        {
          string vertice;
          int lixo, peso;

          line >> vertice;
          line >> lixo;
          line >> lixo;
          line >> peso;

          vertices->insereVertice(vertice, peso);
          numeroVertices++;
        }
      }
      else if (str == "link")
        link = true;
    }
  }
  else
  {
    cout << "Erro ao carregar arquivo" << endl;
  }
}

/*
 * imprimeGrafoPNG() cria o arquivo 
 * .dot, cria a imagem a partir dele 
 * e exibe a imagem do grafo.
 */
void Grafo::imprimeGrafoPNG()
{

  ofstream arquivo;
  arquivo.open("GrafoPNG.dot", ios::trunc | ios::in); //cria se não existir ou reescreve no arquivo GrafoPNG.dot

  if (arquivo.is_open())
  {
    arquivo << "Strict Graph A{" << endl;
    arquivo << "    rankdir=LR;" << endl;
    Vertice *p = vertices->getPrimeiro();

    while (p != NULL)
    { //p é o ponteiro que está na lista de vertices do grafo
      arquivo << "    ";
      arquivo << p->getInfo();
      cout << p->getGrau();
      if (p->getGrau() > 0)
      {

        Aresta *t = p->getListaAdjacencia();
        arquivo << " -- {";

        while (t != NULL)
        { //t é o ponteiro que está na lista de aresta do no
          arquivo << (t->getAdjacente())->getInfo() << " ";
          t = t->getProx();
        }

        arquivo << "}";
      }
      arquivo << ";" << endl;
      p = p->getProx();
    }

    arquivo << "}";
    arquivo.close();

    system("dot -Tpng -O GrafoPNG.dot"); // cria o png do grafo
    cout << "Arquivo Concluido!" << endl;
    system("display GrafoPNG.dot.png"); // mostra a imagem do grafo
  }
  else
    cout << "Erro ao encontrar/criar o arquivo GrafoPNG.dot !" << endl;
}

/*
 * ExportaGrafo() Exporta os dados 
 * analizados durante a execução do
 * programa com determinada entrada
 */
/*
void Grafo::exportaGrafo()
{
  cout << "Exportando analizes do Grafo!" << endl;

  if(0)
  {
    cout << "Exportando" << endl; // continuar com o export
  }
  else
    cout << "Erro ao exportar! Grafo não encontrado." << endl;  
}
*/
/* MenuSelecionado  recebe um caracter que identifica
 * qual opção selecionada e requisita determinado
 * parametro caso precise.
 */
void Grafo::menuSelecionado(char a)
{
  switch (a){

  case '1':
  {
    string id_a, id_b;
    int peso;

    cout << "Adicionando Aresta" << endl;
    cout << "Digite o id dos vertices e em seguida o peso (ex: 23 45 0)" << endl;
    cin >> id_a >> id_b >> peso;
    Vertice *a = vertices->buscaVertice(id_a);
    Vertice *b = vertices->buscaVertice(id_b);
    //a->insereAresta();
    break;
  }
  case '2':
  {
    string id_a, id_b;

    cout << "Removendo Aresta" << endl;
    cout << "Digite o id dos vertices (ex: 23 45)" << endl;
    cin >> id_a >> id_b;

    deletaAresta(id_a, id_b);
    break;
  }
  case '3':
  {
    string id;
    int peso;

    cout << "Adicionando vertice" << endl;
    cout << "Digite o id vertice e em seguida o seu peso (ex: 2 10): ";
    cin >> id >> peso;

    vertices->insereVertice(id, peso);
    break;
  }
  case '4':
  {
    string id;

    cout << "Removendo Veritce" << endl;
    cout << "Digite o id do vertice que deseja remover: " << endl;
    cin >> id;

    vertices->deletaVertice(id);
    break;
  }
  case '5':
  {
    string id;
    cout << "Buscar vertice" << endl;
    cout << "Digite o id do vertice que deseja procurar: " << endl;
    cin >> id;

    Vertice *aux = vertices->buscaVertice(id);

    if (aux != NULL)
      cout << "Vertice de id "
           << " encontrado!" << endl;
    else
      cout << "Vertice não encontrado!" << endl;
    break;
  }
  case '6':
  {
    string id;
    cout << "Vertices Adjacentes" << endl;
    cout << "Digite o id do vertice: " << endl;
    cin >> id;

    Vertice *aux = vertices->buscaVertice(id);

    if (aux != NULL)
    {
      Aresta *adjacentes = aux->getListaAdjacencia();

      while (adjacentes != NULL)
      {
        cout << adjacentes->getAdjacente()->getInfo() << endl;
        adjacentes = adjacentes->getProx();
      }
    }
    else
      cout << "Vertice não encontrado!" << endl;

    break;
  }
  case '7':
  {
    cout << "Limpar Grafo" << endl;
    delete vertices;
    vertices = new Lista();
    break;
  }
  case '8':
  {
    cout << "Informaçoes do Grafo" << endl;
    cout << "Numero de Vertices: " << vertices->getQuantidade() << endl;
    cout << "Numero de Arestas: " << numeroArestas << endl;
    cout << "Numero de Vertices de Grau 0: " << quantidadeGrausZero << endl;
    cout << "Maior Grau: " << vertices->getMaiorGrau()->getGrau() << endl;
    break;
  }
  case '9':
  {
    string inicio;
    cout << "Digite o vertice de inicial: ";
    cin >> inicio;
  
    Grafo * aux = guloso(inicio);
    
    if ( aux != NULL){
      cout << "O custo foi:"<< custoSteiner(aux) << endl;
      aux->imprimeGrafoPNG();
    }
    break;
  }
  case '0':
  {
    cout << "Imprimindo Grafo" << endl;
    imprimeGrafoPNG();
    break;
  }
  default:
    break;
  }
}

/* Menu de funcionalidades do Grafo */
void Grafo::menu()
{
  char menu;
  while (true)
  {
    cout << endl;
    cout << "# Menu principal #" << endl;
    cout << "[1] - Adicionar aresta" << endl;
    cout << "[2] - Deletar aresta" << endl;
    cout << "[3] - Adicionar vertice" << endl;
    cout << "[4] - Deletar vertice" << endl;
    cout << "[5] - Buscar vertice" << endl;
    cout << "[6] - Vertices adjacentes" << endl;
    cout << "[7] - Limpar Grafo" << endl;
    cout << "[8] - Informaçoes do Grafo" << endl;
    cout << "[9] - Guloso" << endl;
    cout << "[0] - Imprimir Grafo" << endl;
    cout << "[q] - Para sair" << endl;
    cout << endl;
    do
    {
      cout << "Digite uma opcao do menu: ";
      cin >> menu;
    } while ((menu < '0' || menu > '9') && menu != 'q');

    if (menu == 'q')
    {
      cout << "Saindo..." << endl;
      cout << "Bye" << endl;
      return;
    }
    menuSelecionado(menu);
  }
}

/*
 * addAresta() usa os ids dos vertices e o peso para criar a aresta que
 * será adicionada na lista de adjancencia dos vertices e incrementa 1 
 * no numero de arestas do grafo
 */
void Grafo::addAresta(string id_a, string id_b, int peso)
{

  Vertice *a = vertices->buscaVertice(id_a);
  Vertice *b = vertices->buscaVertice(id_b);

  auxAddAresta(a, b, peso);
}

void Grafo::auxAddAresta(Vertice *a, Vertice *b, int peso)
{
  if (a == NULL || b == NULL)
  {
    cout << "Erro: Vertice invalido!" << endl;
    return;
  }
  else
  {
    Aresta *p = new Aresta(a, b, peso);
    Aresta *t  = new Aresta(b, a, peso);
    a->insereAresta(p);
    b->insereAresta(t);
    numeroArestas++;

    //Aresta de menor valor
    if(menorValor == NULL){
      menorValor = p;
    }
    else if(menorValor->getPeso() > peso){
      menorValor = p;
    }
  }
  atualizaMaiorgrau();
}

/*
 * deletaAresta() usa os ids dos vertices para encontrar a aresta que
 * será apagada e diminui 1 no numero de arestas do grafo
 */
void Grafo::deletaAresta(string id_a, string id_b)
{

  Vertice *a = vertices->buscaVertice(id_a);
  Vertice *b = vertices->buscaVertice(id_b);

  if (a == NULL || b == NULL)
  {
    cout << "Erro: Vertice invalido!" << endl;
    return;
  }
  else
  {
    Aresta *p = a->buscaAresta(id_b);
    Aresta *t = b->buscaAresta(id_a);

    if (p == NULL || t == NULL)
    {
      cout << "Erro: Aresta invalida!" << endl;
      return;
    }
    else
    {
      a->deletaAresta(p);
      b->deletaAresta(t);
    }
  }
  numeroArestas--;
  atualizaMaiorgrau();
}


/*
 * atualizaMaiorgrau() compara os graus dos vertices para achar o
 * de maior grau.
 */
void Grafo::atualizaMaiorgrau(){

  Vertice * p = vertices->getPrimeiro();
  quantidadeGrausZero = 0;

  while(p != NULL){
    Vertice * maiorGrau = vertices->getMaiorGrau();
    if(maiorGrau == NULL)
      vertices->setMaiorGrau(p);
    if(p->getGrau() == 0)
      quantidadeGrausZero++;
    if(p->getGrau() > maiorGrau->getGrau()){
      vertices->setMaiorGrau(p);
    }
    p = p->getProx();
  }
}

/*
 *  buscarVertice(int i) 
 */
Vertice * Grafo::buscaVertice(int i){

  if(i<0 || i>=numeroVertices){ //fora do alcance dos vertices
    return NULL;
  }
  Vertice * p = vertices->getPrimeiro();

  for(int j = i; j > 0; j--){
    p->getProx();
  }

  return p;
}

/*
 * isVector(vector<string> *vet, int value) verifica se o valor
 * está dentro do vetor.
 */
bool isVector(vector<string> *vet, string value)
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

/*
 * auxBuscaPorProfundidade(Vertice *vertice, vector<string> *nosLidos) 
 * recebe um vertice do grafo e um vetor dos vertices lidos.
 */
void Grafo::auxBuscaPorProfundidade(Vertice *vertice, vector<string> *nosLidos)
{
  if (vertice != NULL)
  {
    cout << vertice->getInfo() << endl;

    Aresta *p = vertice->getListaAdjacencia();
    while (p != NULL)
    {
      Vertice *aux = p->getAdjacente();
      if (!isVector(nosLidos, aux->getInfo()))
      {
        nosLidos->push_back(vertice->getInfo());
        auxBuscaPorProfundidade(aux, nosLidos);
      }
      p = p->getProx();
    }
  }
}

/*
 * buscaPorProfundidade(string verticeInicial) recebe vertice inicial
 * e imprime uma arvore a partir do mesmo.
 */
void Grafo::buscaPorProfundidade(string verticeInicial)
{
  Vertice *p = vertices->buscaVertice(verticeInicial);
  vector<string> nosLidos;

  if (p == NULL)
  {
    cout << "Vertice nao encontrado!" << endl;
  }
  else
    auxBuscaPorProfundidade(p, &nosLidos);

  for (Vertice *aux = vertices->getPrimeiro(); aux != NULL; aux = aux->getProx())
    if (!isVector(&nosLidos, aux->getInfo()))
    {
      nosLidos.push_back(aux->getInfo());
      auxBuscaPorProfundidade(aux, &nosLidos);
    }
}

Vertice** Grafo::montaVetorVertices(int *cont, int tam){
  Vertice **infoVertice = new Vertice *[numeroVertices];
  
  int i = 0;
  for(Vertice *aux = vertices->getPrimeiro(); aux != NULL; aux = aux->getProx()) // i++ ?
    infoVertice[i] = aux;

  for(Vertice *aux = vertices->getPrimeiro(); aux != NULL; aux = aux->getProx())
  {
    i = 0;
    for(Aresta *adjacente = aux->getListaAdjacencia(); i < numeroVertices && adjacente != NULL; i++) //adjacente = adjacente->getProx()?
      if(infoVertice[i]->getInfo() == adjacente->getAdjacente()->getInfo())
        cont[i]++;
  }
  return infoVertice;
}

/*
 * ehConexo() verifica se o Grafico é conexo.
 */
bool Grafo::ehConexo()
{
  if (vertices == NULL|| numeroVertices == 0)
  {
    cout << "Grafo vazio" << endl;
    return false;
  }
  if(quantidadeGrausZero == 0)
    return true;
  else
    return false;
}

/*
 * Complementar retorna o grafo complementar do grafo alocado na memória. 
 * As arestas do Grafo coplementar recebem peso igual a um.
 */
Grafo *Grafo::complementar()
{
  Grafo *complementar = new Grafo();

  if (numeroVertices == 0)
    return complementar;
  else
  {
    //obtem o primeiro vertice da lista
    Vertice *p = vertices->getPrimeiro();

    //para todos os vertice do grafo no grafo complementar
    for (; p != NULL; p = p->getProx(), complementar->numeroVertices++)
    {
      complementar->vertices->insereVertice(p->getInfo(), p->getPeso());
      Vertice *atual = complementar->vertices->buscaVertice(p->getInfo());

      Aresta *adjacente = p->getListaAdjacencia();

      //Adiciona os vertices que não são adjacentes ao vertice de forma ordenada.
      for (Vertice *aux = vertices->getPrimeiro(); aux != NULL && adjacente != NULL; aux = aux->getProx())
      {
        if (adjacente->getAdjacente()->getInfo() != aux->getInfo())
        {
          Aresta *novaAresta = new Aresta(atual, aux, 1);
          atual->insereAresta(novaAresta);
        }
        adjacente = adjacente->getProx();
      }
    }
  }
  return complementar;
}

/* 
 * AuxOrdenacao auxilia a ordenacao topoligica buscando
 * o menor valor do vetor >= 0 e retorna seu indice
 */
int Grafo::auxOrdenacaoTopologica(int vet[], int tam)
{
  if(tam = 0)
    return -1;

  int menor = 0;
  
  for(int i = 0; i<tam; i++)
    if(vet[i] != -1 && vet[i] < vet[menor])
      menor = i;

  vet[menor] = -1;
  return menor;
}

/*
 * OrdenacaoTopologica
 */
Vertice** Grafo::ordenacaoTopologica()
{
  if(vertices->getPrimeiro() == NULL)
    return NULL;

  int cont[numeroVertices];
  Vertice **infoVertice = montaVetorVertices(cont, numeroVertices);
  
  Vertice **ordenado = new Vertice *[numeroVertices];
  for(int i = 0; i<numeroVertices; i++)
    ordenado[i] = infoVertice[auxOrdenacaoTopologica(cont, numeroVertices)];
  
  return ordenado; 
}

/*
 * buscaPorLargura() usa uma fila parar ir buscando sempre
 * os adjacentes do vertice utilizando a ordem da lista de adjacencia
 * */
///melhorar esse comenntário

void Grafo::buscaPorLargura(string verticeInicial)
{
  Vertice *p = vertices->buscaVertice(verticeInicial);

  if (p == NULL)
  {
    cout << "Vertice nao encontrado!" << endl;
  }
  p = vertices->getPrimeiro();
  vector<string> nosLidos;
  Fila aux;
  aux.insere(p);

  while (!aux.vazia())
  {
    p = aux.retira();
    Aresta *t = p->getListaAdjacencia();

    if(!isVector(&nosLidos,p->getInfo())){
        nosLidos.push_back(p->getInfo());
    }    

    while(t != NULL){
      
      if(!isVector(&nosLidos,t->getAdjacente()->getInfo())){
        aux.insere(t->getAdjacente());
      }
      t = t->getProx();
      
    }
  }
}

/*
* algoritmoDijkstra() calcula e retorna o valor do menor caminho saindo
* do vertice de origem ate o de destino, usando busca em largura.
*/

int Grafo::algoritmoDijkstra(string origem, string destino){

  Vertice * p = vertices->buscaVertice(origem);
  Vertice * q = vertices->buscaVertice(destino);

  if(p == NULL || q == NULL){
    cout << "Vertice nao encontrado!" << endl;
    //return exit(1);
  }

  vector <string> nosLidos;
  Fila aux;
  aux.insere(p);

  while (!aux.vazia())
  {
    p = aux.retira();
    Aresta * t = p->getListaAdjacencia();
    int caminho = p->getTamCaminho() + t->getPeso();
    
    if(!isVector(&nosLidos,p->getInfo())){
      nosLidos.push_back(p->getInfo());
    }

    while(t != NULL){
      Vertice * r = t->getAdjacente();
      if(!isVector(&nosLidos,r->getInfo())){
        aux.insere(r);
        //adicionar tamanho do caminho ao chegar no vertice
      }
      if( caminho < r->getTamCaminho()){
        r->setTamCaminho(caminho);
      }
      t = t->getProx();
    }
  }
  return q->getTamCaminho();
}

/*
* algoritmoPrim() calcula a arvore geradora minima de um grafo,
* procura sempre a aresta de menor peso que conecte um vértice
* da árvore a outro que ainda não esteja na árvore. 
*/

Grafo * Grafo::algoritmoPrim(){

  Grafo * arvore = new Grafo ();
  Lista * arv_vertices = arvore->getVertices();
  Vertice * p = menorValor->getOrigem();
  Vertice * q = menorValor->getAdjacente();

  arv_vertices->insereVertice(p->getInfo(),p->getPeso());
  arv_vertices->insereVertice(q->getInfo(),q->getPeso());
  arvore->addAresta(p->getInfo(), q->getInfo(), menorValor->getPeso());

  while(arv_vertices->getQuantidade() != numeroVertices){

    Vertice * t = arv_vertices->getPrimeiro();
    Aresta * aux_aresta;

    while(t!=NULL){

      Aresta * aux = vertices->buscaVertice(t->getInfo())->getListaAdjacencia();

      for(; aux!= NULL; aux = aux->getProx()){
        if(aux_aresta->getPeso() > aux->getPeso()){
          if(arv_vertices->buscaVertice(aux->getAdjacente()->getInfo()) == NULL)
            aux_aresta = aux;
        }
      }
      t = t->getProx();
    }
    Vertice * vertice_auxiliar = aux_aresta->getAdjacente();
    arv_vertices->insereVertice(vertice_auxiliar->getInfo(),vertice_auxiliar->getPeso());
    arvore->addAresta(aux_aresta->getOrigem()->getInfo(),aux_aresta->getAdjacente()->getInfo(),aux_aresta->getPeso());
  }
  return arvore; 
}

/*
* algoritmoKruskal() 
*
*/

Grafo * Grafo::algoritmoKruskal(){

  Grafo * arvore = new Grafo ();
  Lista * arv_vertices = arvore->getVertices();
  Vertice * p = menorValor->getOrigem();
  Vertice * q = menorValor->getAdjacente();

  arv_vertices->insereVertice(p->getInfo(),p->getPeso());
  arv_vertices->insereVertice(q->getInfo(),q->getPeso());
  arvore->addAresta(p->getInfo(), q->getInfo(), menorValor->getPeso());

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

int Grafo::custoSteiner (Grafo * arvore){
  
  int custo_arestas = 0;
  int custo_nos = 0;
  Vertice * p = (arvore->getVertices())->getPrimeiro();
  
  while(p != NULL){
    
    Aresta * t = p->getListaAdjacencia();

    for(int i = p->getGrau(); i>0;i++){
      custo_arestas+= t->getPeso();
      t = t->getProx();
    }
    p = p->getProx();
  }
  custo_arestas= custo_arestas/2;
  
  p = vertices->getPrimeiro();

  while(p != NULL){
    if(arvore->getVertices()->buscaVertice(p->getInfo()) != NULL)
      custo_nos+= p->getPeso();  
    p->getProx();
  }
    
  return custo_arestas + custo_nos;
}

int Grafo::auxGuloso(Vertice * p, Grafo * resultado,int count){

  cout << "count: " << count << endl;
  if(count == 420)  //condição de parada da recursão
    return custoSteiner(resultado); //calcula e retorna o custo da arvore criada

  Aresta * adjacentes = p->getListaAdjacencia();
  Lista * verticesR = resultado->getVertices();

  //if(verticesR->buscaVertice(adjacentes->getAdjacente()->getInfo()) != NULL)// para evitar que pegue um nó que ja está na solução
  //  adjacentes = adjacentes->getProx();

  Aresta * melhor = adjacentes;
  int gasto_melhor = melhor->getAdjacente()->getPeso() - melhor->getPeso();

  while(adjacentes != NULL){   //procura o melhor vertice na arvore

    int gasto_outro = adjacentes->getAdjacente()->getPeso() - adjacentes->getPeso(); //preenche com o "lucro" de ir para um vertice

    if(gasto_melhor > gasto_outro){
      melhor = adjacentes;
      gasto_melhor = gasto_outro;
    }
    cout<<"flag depois do if" << endl;
    
    adjacentes = adjacentes->getProx();

    if(verticesR->buscaVertice(adjacentes->getAdjacente()->getInfo()) != NULL) // para evitar que pegue um nó que ja está na solução
      adjacentes = adjacentes->getProx();              
  }

  Vertice * melhorVertice = melhor->getAdjacente();
  Vertice * verifica = verticesR->buscaVertice(melhorVertice->getInfo());

/*if(verifica != NULL){ //verifica se o vertice ja está na solucao    
    //ver a melhor forma de optimizar
  }
  else{}
*/
  cout<<"Estou no else"<<endl;
  verticesR->insereVertice(melhorVertice->getInfo(),melhorVertice->getPeso());  //coloca o vertice na arvore
  resultado->addAresta(p->getInfo(),melhorVertice->getInfo(),melhor->getPeso());  //cria aresta existente entre os vertices
  return auxGuloso(melhorVertice,resultado,count+1);       
}

Grafo * Grafo::guloso(string vertice_inicial){

  Vertice * vertice_aux = vertices->buscaVertice(vertice_inicial);

  if(vertice_aux == NULL){
    cout<<"Erro: vertice não encontrado!"<<endl;
    return NULL;
  }
  if(ehConexo() == false){
    cout<<"Erro: o Grafo não é conexo!"<<endl;
    return NULL;
  }

  Grafo * resultado = new Grafo();
  int count = 0;
  auxGuloso(vertice_aux,resultado,count);

  cout << "flag final"<<endl;
  return resultado;
}

/*---------------------------------------------------------------------------
  O Algoritmo Guloso Randomizado funciona recevendo um parametro alfa
  que é utilizado para auxilar na randomização




---------------------------------------------------------------------------*/

Grafo * Grafo::gulosoRandomizado (float alfa){

  srand(time(NULL));
  int numeroInterecoes = 1000;  //quantidade de vezes que o algoritmo sera rodado
  Grafo * melhor = guloso(vertices->getPrimeiro()->getInfo());
  int vertice_randomizado = (rand()%numeroVertices)*alfa; 
  Vertice * p = buscaVertice(vertice_randomizado);

  for(int i = 0; i<numeroInterecoes;i++){
    
    Grafo * aux = guloso(p->getInfo());

    if(custoSteiner(aux) < custoSteiner(melhor))
      melhor = aux;

    vertice_randomizado = (rand()%numeroVertices) * alfa;
    p = buscaVertice(vertice_randomizado);
  }

  return melhor;
}

/*
 * Auxilia recursivamente o algoritmo de Floyd para encontrar menor 
 * caminho entre dois vertices, sendo 2000000000 como não tendo aresta
 */
int Grafo::auxFloyd(Vertice *p, Vertice *destino)
{
  if(p)
  { 
    //Verifica se chegou no vestice de destino
    if(p == destino)
      return 0;

    Aresta *aresta = p->getListaAdjacencia();
    if(aresta){
      // busca o primeiro valor dos vertices adjacentes e coloca como menor valor da lista
      int menor = auxFloyd(aresta->getAdjacente(), destino) + aresta->getPeso();
      
      for(aresta = aresta->getProx(); aresta != NULL; aresta = aresta->getProx())
      {
        int aux = auxFloyd(aresta->getAdjacente(), destino) + aresta ->getPeso();
        if(aux < menor)
          menor = aux;
      }
      return menor;
    }
  }
  return 1500000000;
}

/*
 * Algoritmo de Floyd encontra o menor caminho entre dois vertices.
 */
int Grafo::algoritmoFloyd(string origem, string destino){
  // busca os vertices inicial e final
	Vertice *inicial = vertices->buscaVertice(origem);
  Vertice *final = vertices->buscaVertice(destino);

  // verifica se os vertices estão na lista
  if(inicial && final)
  {
    return auxFloyd(inicial, final);
  }
  else if(inicial)
    cout << "Verice de destino inexistente no grafo" << endl;
  else
    cout << "Verice inicial inexistente no grafo" << endl;
  return 2147483547;
}
