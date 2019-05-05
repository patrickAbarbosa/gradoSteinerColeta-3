#include <iostream>
#include <fstream> // Open File
#include <string>
#include <sstream>
#include <vector>

#include "../Headers/Grafo.h"
#include "../Headers/Lista.h"
#include "../Headers/Fila.h"

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
  ehDigrafo = false;
  numeroArestas = 0;
  numeroVertices = 0;
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
  leArquivo();
}

Grafo::Grafo(string in, string out, string ehDigrafo)
{
  cout << "Construindo Grafo" << endl;

  vertices = new Lista();

  arquivoIn = new string;
  *arquivoIn = in;

  arquivoOut = new string;
  *arquivoOut = out;

  if(ehDigrafo == "1" )
    ehDigrafo = true;
  else
    ehDigrafo = false;
  numeroArestas = 0;
  numeroVertices = 0;
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
 * */

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
  switch(a)
  {
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
      cout << "Vertice de id " << " encontrado!" << endl;
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
    cout << "Numero de Arestas: " <<  numeroArestas <<endl;
    cout << "Maior Grau: " << vertices->getMaiorGrau()->getGrau() << endl;
    break;
  }
  case '9':
  {
    string inicio;
    cout << "Digite o vertice de partida: ";
    cin >> inicio;
    buscaPorProfundidade(inicio);
    break;
  }
  case '0':
  {
    cout << "Imprimir Grafo" << endl;
    imprimeGrafoPNG();
    break;
  }
  default:
    break;
  }
}

/* Mennu de funcionalidades do Grafo */
void Grafo::menu()
{
  char menu;
  while (true)
  {
    cout << "# Menu principal #" << endl;
    cout << "[1] - Adicionar aresta" << endl;
    cout << "[2] - Deletar aresta" << endl;
    cout << "[3] - Adicionar vertice" << endl;
    cout << "[4] - Deletar vertice" << endl;
    cout << "[5] - Buscar vertice" << endl;
    cout << "[6] - Vertices adjacentes" << endl;
    cout << "[7] - Limpar Grafo" << endl;
    cout << "[8] - Informaçoes do Grafo" << endl;
    cout << "[9] - Busca por profundidade" << endl;
    cout << "[0] - Imprimir Grafo" << endl;
    cout << "[q] - Para sair" << endl;
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
 * */

void Grafo::addAresta(string id_a, string id_b, int peso)
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
    Aresta *p = new Aresta(a, peso);
    Aresta *t = new Aresta(b, peso);
    a->insereAresta(t);
    b->insereAresta(p);
  }
  numeroArestas++;
}

/*
 * deletaAresta() usa os ids dos vertices para encontrar a aresta que
 * será apagada e diminui 1 no numero de arestas do grafo
 * */

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
}

bool isVector(vector <string> *vet, string value)
{
  if(!vet){
    cout << "Vetor nao alocado!" << endl;    
    exit(1);
  }

  for(vector<string>::iterator it = vet->begin(); it != vet->end(); ++it)
    if(*it == value)
      return true;
  return false;
}

void Grafo::auxBuscaPorProfundidade(Vertice *vertice, vector <string> *nosLidos)
{
  if (vertice != NULL)
  {
    cout << vertice->getInfo() << endl;

    Aresta *p = vertice->getListaAdjacencia();
    while (p != NULL)
    {
      Vertice *aux = p->getAdjacente();
      if(!isVector(nosLidos, aux->getInfo()))
      {
        nosLidos->push_back(vertice->getInfo());
        auxBuscaPorProfundidade(aux, nosLidos);      
      }
      p  = p->getProx();
    }
  }
}

void Grafo::buscaPorProfundidade(string verticeInicial)
{
  Vertice *p = vertices->buscaVertice(verticeInicial);
  vector <string> nosLidos;
  
  if (p == NULL)
  {
    cout << "Vertice nao encontrado!" << endl;
  }
  
  auxBuscaPorProfundidade(p, &nosLidos);
  
  for(Vertice *aux = vertices->getPrimeiro(); aux != NULL; aux = aux->getProx())
    if(!isVector(&nosLidos, aux->getInfo()))
    {
      nosLidos.push_back(aux->getInfo());
      auxBuscaPorProfundidade(aux, &nosLidos);
    } 
}

/*
 * buscaPorLargura() usa uma fila parar ir buscando sempre
 * os adjacentes do vertice utilizando a ordem da lista de adjacencia
 * */

///melhorar esse comenntário

void Grafo::buscaPorLargura(string verticeInicial){

  Vertice * p = vertices->buscaVertice(verticeInicial);

  if(p == NULL){
    cout << "Vertice nao encontrado!" << endl;
  }
  
  vector <string> nosLidos;
  Fila aux;
  aux.insere(p);

  while(!aux.vazia()){

    p = aux.retira();
    Aresta * t = p->getListaAdjacencia(); 

    if(!isVector(&nosLidos,p->getInfo(){
        nosLidos->push_back(p->getInfo());
    }    

    while(t != NULL){
      if(!isVector(&nosLidos,t->getAdjacente()->getInfo()){
        aux.insere(t->getAdjacente());
      }
      t = t->getProx();
    }
  }
}

void Grafo::algoritimoDijkstra(){

  Vertice * p = vertices->getPrimeiro();
  //adicionar caminho no vertice
  int tamCaminho = 0;
  
  vector <string> nosLidos;
  Fila aux;
  aux.insere(p);

  while(!aux.vazia()){

    p = aux.retira();
    Aresta * t = p->getListaAdjacencia(); 

    if(!isVector(&nosLidos,p->getInfo(){
        nosLidos->push_back(p->getInfo());
    }    

    while(t != NULL){
      if(!isVector(&nosLidos,t->getAdjacente()->getInfo()){
        aux.insere(t->getAdjacente());
        //adicionar tamanho do caminho ao chegar no vertice
      }
      t = t->getProx();
    }
    tamCaminho ++;
  }
}

void Grafo::auxPrim(){

    //cria arvore
}

void Grafo::algoritmoPrim(){

  //gera arvore de custo minimo

}