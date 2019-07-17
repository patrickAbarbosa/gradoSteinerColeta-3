#include <iostream>
#include <fstream> // Open File
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include <queue>

#include "../Headers/Grafo.h"
//#include "../Headers/Lista.h"
#include "../Headers/GeraCsv.h"
//#include "../Headers/Fila.h"
#include "../Headers/Aresta.h"
#include "../Headers/Vertice.h"
#include "../Headers/Guloso.h"
#include "../Headers/LinhaCSV.h"

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
  //Seta o grafo como  não orientado
  ehDigrafo = false;
  //seta a saida como nula 
  out = NULL;
  //Seta o maior grau como nulo
  maiorGrau = NULL;
}

/*
 * Grafo(arquivoIn) espera o local do arquivo para 
 * leitura, assim construindo o grafo a partir desse
 */
Grafo::Grafo(string in)
{
  out = NULL;
  ehDigrafo = false;
  //Seta o maior grau como nulo
  maiorGrau = NULL;
  leArquivo(in);
}

/*
 * Grafo(arquivoIn, arquivoOut) recebe o local do 
 * arquivo para leitura para contruir o grafo a partir
 * dos dados nele e o local do arquivo de saída das
 * análiizes do processamento
 */
Grafo::Grafo(string in, GeraCsv *out)
{
  ehDigrafo = false;
  this->out = out;
  leArquivo(in);
}

/*
 * Grafo(arquivoIn, arquivoOut, ehDigrafo) recebe o local do 
 * arquivo para leitura para contruir o grafo a partir
 * dos dados nele e o local do arquivo de saída das
 * análiizes do processamento e se é o Grafo é um digrafo.
 */
Grafo::Grafo(string in, GeraCsv *out, string ehDigrafo)
{
  this->out = out;
  //Seta o maior grau como nulo
  maiorGrau = NULL;
  if (ehDigrafo == "1")
    ehDigrafo = true;
  else
    ehDigrafo = false;
  leArquivo(in);
}
/*
 * ~Grafo() analiza memória alocada dinamicamente
 * que está sendo utilizado pela classe para 
 * desalocar e liberar o espaço.
 */
Grafo::~Grafo()
{
  cout << "Destruindo Grafo" << endl;
}
//
//
// End Contrutores e Destrutores

/*
 * leArquivo() faz a leitura do arquivo
 * de entrada e coloca em variáveis 
 * para o processamento
 */
void Grafo::leArquivo(string in)
{
  // instancia as variáveis para calcular o tempo do
  clock_t inicio, fim;
  //LinhaCSV linha;
  // seta os valores da linha
  //linha.instancia = *arquivoIn;
  // //linha.classe = "Grafo.h";
  // linha.algoritmo = "leArquivo";
  // linha.interacao = 0;

  // Pega o tempo do processador no inicio da leitura
  inicio = clock();
  // Variavel para ler o arquivo do grafo 
  fstream file;
  // Tenta abrir o arquivo
  file.open(in);
  // Verifica se o aquivo foi aberto com sucesso
  if (file.is_open())
  {
    // Irá guardar se estamos lendo as arestas
    bool link = false;
    // Guarda a linha lida para uma análise futura
    string str;
    // para nao pegar a primeira linha
    getline(file, str); 
    // Enquanto a variável file não estiver no final do arquivo
    while (!file.eof())
    {
      // linha.interacao++;
      str = ' ';
      // Guarda a linha na variável str
      getline(file, str);
      // Verifica se é não é um comentário no meio da leitura
      if (str[0] >= '0' && str[0] <= '9')
      {
        // Cria uma variável que irá simular um arquivo para leitura e colocamos como entrada a str
        stringstream line(str);
        if (link)
        {
          // Variáveis que serão utilizadas para descartar valores inuteis e guardará o peso
          int lixo, peso;
          // Irá guardar as informações dos vertices A e B
          string verticeA, verticeB;
          // Remove o primeiro valor e descartamos
          line >> lixo;
          // seta as informações do verticeA, verticeB e peso.
          line >> verticeA >> verticeB >> peso;
          // Cria uma aresta com os valores pré setados
          addAresta(verticeA, verticeB, peso);
        }
        else
        {
          // Declarara o vetice
          string vertice;
          // Variável para descarte e para guardar os valores
          int lixo, peso;
          // Setamos a informação do vetice
          line >> vertice;
          // Descartamos o valor
          line >> lixo;
          // Descartamos o valor
          line >> lixo;
          // Setamos o peso do vertice
          line >> peso;
          // cria novo Vertice
          Vertice *aux = new Vertice(vertice, peso);
          //adiciona no na lista
          vertices.push_back(aux);
        }
      }
      // Verifica se iremos começar a ler arestas
      else if (str == "link")
        // Seta como verdadeiro essa leitura
        link = true;
    }
    // pega o tempo do processador do fim da leitura
    fim = clock();
    // linha.tempo_execucao = to_string((1000 * (fim - inicio))/(double)(CLOCKS_PER_SEC)) + "ms";
    // out->imprime(linha);
  }
  else
  {
    cout << "Erro ao carregar arquivo" << endl;
  }
}

/*
 * imprimeGrafoPNG() cria o arquivo * .dot, usando o programa Graphviz cria e depois 
 * exibe a imagem do grafo.
 */
void Grafo::imprimeGrafoPNG()
{
  // Declaramos o arquivo de saida
  ofstream arquivo;
  // Setamos o nome do arquivo. Caso não existir cria, caso não reescreve no arquivo GrafoPNG.dot
  arquivo.open("GrafoPNG.dot", ios::trunc | ios::in); 

  // Verifica se o arquivo foi aberte 
  if (arquivo.is_open())
  {
    // Dizemos que o grafo não terá multi-aresta
    arquivo << "Strict Graph A{" << endl;
    // Dizemos que a escrita será da esquerda pra direita
    arquivo << "    rankdir=LR;" << endl;
  	
    // Declaramos o interador para apontar para o inicio da lista de veritices até ser diferente do final
    for(vector<Vertice*>::iterator it = vertices.begin() ; it != vertices.end(); ++it)
    { 
      // Colocamos um espaço na linha
      arquivo << "    ";
      // Adicionamos a informação do vertice na linha
      arquivo << (*it)->getInfo();
      // Se o grau do vertice for maior que zero faça
      if ((*it)->getGrau() > 0)
      {
        // Colocamos "{" para dizer que seus adjacentes são esses valores
        arquivo << " -- {";
        // Iniciamos o interador apontando para o inicio das arestas desse vertice it até ser diferente do fim
        for(vector<Aresta*>::iterator aresta = (*it)->adjacentes.begin(); aresta != (*it)->adjacentes.end(); ++aresta)
          // Colocamos a informação do vertice adjacente no arquivo
          arquivo << (*aresta)->getAdjacente()->getInfo() << " ";
        
        // Adicionamos "}" no arquivo para identificar que os adjacentes ao vertice terminaram
        arquivo << "}";
      }
      // Encerramos o vertice
      arquivo << ";" << endl;
    }
    // Encerramos o arquivo
    arquivo << "}";
    // Fechamos o arquivo
    arquivo.close();
    // Chamamos a biblioteca para gerar o grafo a partir do arquivo criado
    system("dot -Tpng -O GrafoPNG.dot >> grafo.log"); // cria o png do grafo
    cout << "Arquivo Concluido!" << endl;
    // Abrimos a imagem gerada a partir do grafo
    system("display GrafoPNG.dot.png >> grafo.log"); // mostra a imagem do grafo
  }
  else
    cout << "Erro ao encontrar/criar o arquivo GrafoPNG.dot !" << endl;
}

/*
 * ExportaGrafo() Exporta os dados analizados durante a execução do
 * programa com determinada entrada para um arquivo do tipo "".csv"
 *
/
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
/*
void Grafo::menuSelecionado(char a)
{
  switch (a){

  case '1':
  {
    // Utilizadas receber as informações do vertice
    string id_a, id_b;
    // Irá receber o peso da aresta passada pelo usuário
    int peso;

    cout << "Adicionando Aresta" << endl;
    cout << "Digite o id dos vertices e em seguida o peso (ex: 23 45 0)" << endl;
    cin >> id_a >> id_b >> peso;

    Vertice *a = NULL;
    Vertice *b = NULL;
    // Busca os vertices no vetor de vertices
    for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end() && (!p || !q); ++it)
    {
      if((*it)->getInfo() == id_a)
        a = *it;
      else if((*it)->getInfo() == id_b)
        b = *it;
    }
    a->;
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
    //Algoritmo Guloso
    int inicial;
    cout<<"digite o vertice inicial: ";
    cin>>inicial;
    Guloso aux(this);
    Grafo* gr = aux.calculaGuloso(to_string(inicial));
    gr->imprimeGrafoPNG();
    break;
  }
  case '9':
  {
    //Guloso Randomizado
    float alfa;
    int numeroInteracoes;
    cout<<"digite o valor de alfa: ";
    cin>>alfa;
    cout<<"digite o numero de interacoes: ";
    cin>>numeroInteracoes;
    Guloso aux(this);
    Grafo* gr = aux.gulosoRandomizado(alfa,numeroInteracoes);
    gr->imprimeGrafoPNG();
    break;
  }
  case '0':
  {
    //Guloso Randomizado Reativo
    int numeroInteracoes;
    int tamBloco;
    int tamAlfa;
    cout<<"digite a quantidade de alfas: ";
    cin>>tamAlfa;
    int vet[tamAlfa];
    for(int i = 0; i<tamAlfa; i++){
      cout<<"digite o alfa["<<i<<"]: ";
      cin>>vet[i];
    }
    cout<<"digite o numero de interacoes: ";
    cin>>numeroInteracoes;
    cout<<"digite o tamanho do bloco: ";
    cin>>tamBloco;
    Guloso aux(this);
    Grafo* gr = aux.gulosoRandomizadoReativo();
    gr->imprimeGrafoPNG();
    imprimeGrafoPNG();
    break;
  }
  case 'p':
  {
    cout << "Imprimindo Grafo" << endl;
    imprimeGrafoPNG();
    break;
  }
  case 'i':
  {
    cout << "Informaçoes do Grafo" << endl;
    cout << "Numero de Vertices: " << vertices->getQuantidade() << endl;
    cout << "Numero de Arestas: " << numeroArestas << endl;
    cout << "Numero de Vertices de Grau 0: " << quantidadeGrausZero << endl;
    cout << "Maior Grau: " << vertices->getMaiorGrau()->getGrau() << endl;
    break;
  }
  /*----------------------Area de teste ----------------------- */
  /*
  case 'a': 
  {
    cout<<endl;
    cout << "O grafo é conexo ? " << ehConexo() << endl;
    break;
  }
  case 'b': 
  {
    string a, b;
    cout << "Digite o vertice inicial: ";
    cin >> a;
    cout << "Digite o vertice final: ";
    cin >> b;
    cout << "Resultado da busca: " << buscaPorLargura(a,b) << endl;
    break;
  }
  case 'c': 
  {
    //cout<<"custoSteiner: "<< custoSteiner(this)<<endl;
    break;
  }
  case 'd': 
  {
    float alpha[3] = {0.1,0.2,0.3};
    //Grafo * aux = gulosoRandomizadoReativo(alpha,3,5000,100);
    //cout<<"custo do guloso randomizado: "<<custoSteiner(aux)<<endl;
    break;
  }
  default:
    break;
  }
}
*/
// Menu de funcionalidades do Grafo 
/*
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
    cout << "[8] - Guloso" << endl;
    cout << "[9] - Guloso Randomizado" << endl;
    cout << "[0] - Guloso Randomizado Reativo" << endl;
    cout << "[p] - Imprimir Grafo" << endl;
    cout << "[i] - Informaçoes do Grafo" << endl;
    cout << "[q] - Para sair" << endl;
    cout << endl;
    do
    {
      cout << "Digite uma opcao do menu: ";
      cin >> menu;
    } while (((menu < '0' || menu > '9') && (menu < 'a' || menu > 'z')) && menu != 'q');

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
  // Vertice a e b para criamos uma aresta em cada uma
  Vertice *a = NULL;
  Vertice *b = NULL;

  // Apontamos o interador para o inicio do vetor de vertices até o interador ser diferente do final e a !=null e b!=null
  for(vector<Vertice *>::iterator it = vertices.begin(); it != vertices.end() &&(!a || !b); ++it)
  {
    cout << "Valor: " << (*it)->getInfo() << endl;
    // Verifica se a informação do vertice é igual ao id_a
    if((*it)->getInfo() == id_a){
      a = (*it);
      cout << "A valor encontrado" << endl;
      
    }
    // Verifica se a informação do vertice é igual ao id_b
    if((*it)->getInfo() == id_b){
      b = *it;
      cout << "B valor encontrado" << endl;
    }
  }

  cout << a->getInfo() << endl;
  cout << b->getInfo() << endl;
  auxAddAresta(a, b, peso);
  
}

/* 
 * auxAddAresta(Vertice *a, Vertice *b, int peso)
 * @Vertice *a recebe o vertice de oridem da aresta
 * @Vertice *b receve o vertice de destino da aresta
 * @int peso recebe o peso da aresta
 */
void Grafo::auxAddAresta(Vertice *a, Vertice *b, int peso)
{
  // Verifica se a e b é diferente de nulo para criar a aresta
  if (a == NULL || b == NULL)
  {
    cout << "Erro: Vertice invalido!" << endl;
    return;
  }
  else
  {
    // Criamos as arestas
    Aresta *p = new Aresta(a, b, peso);
    //Inserimos a aresta no vertice
    a->insereAresta(p);
    // Verificamos se o grafo é digrafo ou não
    if(!ehDigrafo)
    {
      Aresta *t  = new Aresta(b, a, peso);
      b->insereAresta(t);
    }
    numeroArestas++;
    cout << "Numero: " << numeroArestas << endl;
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
  // Vertice a e b para receber o endereço dos vertices
  Vertice *a = NULL;
  Vertice *b = NULL;

  // Apontamos o interador para o inicio do vetor de vertices até o interador ser diferente do final e a !=null e b!=null
  for(vector<Vertice *>::iterator it = vertices.begin(); it != vertices.end() && !a && !b; ++it)
  {
    // Verifica se a informação do vertice é igual ao id_a
    if((*it)->getInfo() == id_a)
      a = *it;
    // Verifica se a informação do vertice é igual ao id_b
    else if((*it)->getInfo() == id_b)
      b = *it;
  }
  // Verifica se o valor a ou o valor b não foi encontrado caso seja um digrafo
  if ((a == NULL || b == NULL) && !ehDigrafo)
  {
    cout << "Erro: Vertice invalido!" << endl;
    return;
  }
  // Verifica se o vertice a não foi encontrado
  else if(a == NULL)
  {
    cout << "Erro: Vertice invalido!" << endl;
    return;
  }
  else
  {
    // Recebe a aresta a ser removida
    Aresta *p = a->buscaAresta(id_b);
    // Cria t para receber uma aresta caso o grafo não seja um digrafo
    Aresta *t = NULL;
    // Verifica o grafo não é um digrafo
    if(!ehDigrafo)
      // t Recebe a aresta com a
      t = b->buscaAresta(id_a);
    // Verifica se p e t é nulo se o grafo não é orientado
    if((p == NULL || t == NULL) && !ehDigrafo)
    {
      cout << "Erro: Aresta invalida!" << endl;
      return;
    }
    // Verifica se p é nulo 
    else if(p == NULL)
    {
      cout << "Erro: Aresta invalida!" << endl;
      return;
    }
    else
    {
      a->deletaAresta(p);
      //Verifica se o grafo é um digrafo para poder deletar a aresta em b
      if(!ehDigrafo)
        b->deletaAresta(t);
    }
  }
  // Subtrai o numero de aresta
  numeroArestas--;
  //Atualiza o vertice de maior grau
  atualizaMaiorgrau();
}

/*
 * atualizaMaiorgrau() compara os graus dos vertices para achar o
 * de maior grau.
 */
void Grafo::atualizaMaiorgrau()
{
  // Zeramos o contador de graus
  quantidadeGrausZero = 0;
  // Zeramos o numero de aresta
  numeroArestas = 0;

  maiorGrau = *vertices.begin();
  for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end(); ++it)
  {
    // recebe a quantidade de arestas 
    numeroArestas += (*it)->getGrau();
    // Verifica se o vertice atual tem grau maior que o de atual maior
    if ((*it)->getGrau() > maiorGrau->getGrau())
      maiorGrau = *it;
    // Verifica se o vertice possoui grau zero 
    else if((*it)->getGrau() == 0)
      quantidadeGrausZero++;
  }
}

/*
 *  buscarVertice(int i)
 *  recebe um inteiro i para buscar com id = i do vetor
 */
Vertice * Grafo::buscaVertice(string id)
{
  // o interador recebe o inicio dos vertices até ele ser diferente do fim da lista
  for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end(); ++it)
    // Verifica se a informação do vertice é = ao id solicitado
    if((*it)->getInfo() == id)
      return *it;
  return NULL;
}

/*
 * isVector(vector<string> *vet, int value) verifica se o valor
 * está dentro do vetor.
 */
bool isVector(vector<string> *vet, string value){

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
  // Verifica se o vertice não é nulo
  if (vertice != NULL)
  {
    // imprime a informação do vertice
    cout << vertice->getInfo() << endl;
    // Enquanto o interador for diferente do fim
    for(vector<Aresta*>::iterator it = vertice->adjacentes.begin(); it != vertice->adjacentes.end(); ++it)
    {
      // Verifica se o vertice adjacente já foi lido
      if (!isVector(nosLidos, (*it)->getAdjacente()->getInfo()))
      {
        nosLidos->push_back((*it)->getAdjacente()->getInfo());
        auxBuscaPorProfundidade((*it)->getAdjacente(), nosLidos);
      }
    }
  }
}

/*
 * buscaPorProfundidade(string verticeInicial) recebe vertice inicial
 * e imprime uma arvore a partir do mesmo.
 */
void Grafo::buscaPorProfundidade(string verticeInicial)
{
  // busca o vertice de partida
  Vertice *p = buscaVertice(verticeInicial);
  //o vetor irá guardar os vertices que já foram lidos
  vector<string> nosLidos;
  // verifica se foi encontrado o verice
  if (p == NULL)
  {
    cout << "Vertice nao encontrado!" << endl;
  }
  else
    auxBuscaPorProfundidade(p, &nosLidos);

  for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end(); ++it)
    if (!isVector(&nosLidos, (*it)->getInfo()))
    {
      nosLidos.push_back((*it)->getInfo());
      auxBuscaPorProfundidade(*it, &nosLidos);
    }
}

/*
 * montaVetorVertices //comentar
 */
Vertice** Grafo::montaVetorVertices(int *cont, int tam){
  Vertice **infoVertice = new Vertice *[numeroVertices];
  
  int i = 0;
  for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end(); ++it)
  {
    infoVertice[i] = *it;
    i++;
  }

  for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end(); ++it)
  {
    i = 0;
    for(vector<Aresta*>::iterator adjacente = (*it)->adjacentes.begin();  i < numeroVertices && adjacente != (*it)->adjacentes.end(); ++adjacente)
      if(infoVertice[i]->getInfo() == (*adjacente)->getAdjacente()->getInfo())
        cont[i]++;
  }
  return infoVertice;
}

/*
 * ehConexo() verifica se o Grafico é conexo usando o algoritimo de 
 * busca em largura como base.
 */
bool Grafo::ehConexo()
{
  if(vertices.size() == 0 || numeroArestas == 0){
    cout << "Grafo vazio" << endl;
    return false;
  }
  else if (quantidadeGrausZero != 0)
    return false;

  int contp = 0;
  int contq = 0;

  for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end(); ++it)
  {
    for(vector<Vertice*>::iterator q = vertices.begin(); it != vertices.end(); ++it)
    {
      bool verif = buscaPorLargura((*it)->getInfo(),(*q)->getInfo());
      if(verif == false)
        return false;
      contq++;
    }
    contp++;
  }
  return true;
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
    //para todos os vertice do grafo no grafo complementar
    for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end(); ++it, complementar->numeroArestas++)
    {
      // copias as caracteristicas do vertice
      Vertice *aux = new Vertice((*it)->getInfo(), (*it)->getPeso());
      // Adiciona o vertice a lista de vertices
      complementar->vertices.push_back(aux);
      // atual recebe o ultimo vertice adicionado ao vetor
      Vertice *atual = (*complementar->vertices.end());

      vector<Aresta *>::iterator adjacente = (*it)->adjacentes.begin();
      //Adiciona os vertices que não são adjacentes ao vertice de forma ordenada.
      for (vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end() && adjacente != (*it)->adjacentes.end(); it++, ++adjacente)
      {
        if ((*adjacente)->getAdjacente()->getInfo() != aux->getInfo())
        {
          Aresta *novaAresta = new Aresta(atual, aux, 1);
          atual->insereAresta(novaAresta);
        }
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
  if(vertices.size() == 0)
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

bool Grafo::buscaPorLargura(string verticeInicial,string verticeFinal){
  Vertice *p = NULL;
  Vertice *q = NULL;

  for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end() && (!p || !q); ++it)
  {
    if((*it)->getInfo() == verticeInicial)
      p = *it;
    else if((*it)->getInfo() == verticeFinal)
      q = *it;
  }

  if (p == NULL || q == NULL){
    cout << "Vertice nao encontrado!" << endl;
    return false;
  }

  vector<string> nosLidos;
  queue<Vertice*> aux;
  aux.push(p);

  while (aux.size() != 0)
  {
    p = aux.front();
    aux.pop();

    if(p->getInfo() == verticeFinal){
      return true;
    }

    if(!isVector(&nosLidos,p->getInfo()))
      nosLidos.push_back(p->getInfo());
    for(vector<Aresta*>::iterator t = p->adjacentes.begin(); t != p->adjacentes.end(); ++t) 
    {
      if((*t)->getAdjacente()->getInfo() == verticeFinal)
        return true;
      if(!isVector(&nosLidos,(*t)->getAdjacente()->getInfo())){
        aux.push((*t)->getAdjacente());
      }
    }
  }
  return false;
}

/*
* algoritmoDijkstra() calcula e retorna o valor do menor caminho saindo
* do vertice de origem ate o de destino, usando busca em largura.
*/
int Grafo::algoritmoDijkstra(string origem, string destino){
  Vertice *p = NULL;
  Vertice *q = NULL;

  for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end() && (!p || !q); ++it)
  {
    if((*it)->getInfo() == origem)
      p = *it;
    else if((*it)->getInfo() == destino)
      q = *it;
  }

  if(p == NULL || q == NULL){
    cout << "Vertice nao encontrado!" << endl;
    //return exit(1);
  }

  vector<string> nosLidos;
  queue<Vertice*> aux;
  aux.push(p);
  
  while (aux.size() != 0)
  {
    p = aux.front();
    aux.pop();
    
    int caminho = p->getTamCaminho() + p->adjacentes.front()->getPeso();
    
    if(!isVector(&nosLidos,p->getInfo())){
      nosLidos.push_back(p->getInfo());
    }

    for(vector<Aresta*>::iterator t = p->adjacentes.begin(); t != p->adjacentes.end(); ++t) 
    {
      Vertice * r = (*t)->getAdjacente();
      if(!isVector(&nosLidos,r->getInfo())){
        aux.push(r);
        //adicionar tamanho do caminho ao chegar no vertice
      }
      if( caminho < r->getTamCaminho()){
        r->setTamCaminho(caminho);
      }
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
  // Cria um novo grafo
  Grafo * arvore = new Grafo ();
  
  // Guarda a origem da menor aresta do grafo
  Vertice *p = menorValor->getOrigem();
  // Guarda o destino da menor aresta do grafo
  Vertice *q = menorValor->getAdjacente();

  // verifica se p e q é diferente de nulo
  if(p == NULL && q == NULL)
    return NULL;
  // Cria o primeiro vertice do grafo
  Vertice *aux = new Vertice(p->getInfo(), p->getPeso());
  // Adiciona o vertice no grafo
  arvore->vertices.push_back(aux);
  // Cria um vertice
  aux = new Vertice(q->getInfo(), q->getPeso());
  // Adiciona o vertice no grafo
  arvore->vertices.push_back(aux);
  // Adiciona aresta entre os vertices
  arvore->addAresta(p->getInfo(), q->getInfo(), menorValor->getPeso());
  // Enquanto o numero de vertices do novo grafo for diferente do numero de aresta do grafo
  while(arvore->vertices.size() != numeroVertices)
  {  
    // Irá auxiliar as arestas
    Aresta * aux_aresta = NULL;
    // Declara um interador do tipo aresta
    vector<Aresta*>::iterator w;
    // O interador t recebe o inicio dos vertices e esquanto t for != do fim
    for(vector<Vertice*>::iterator t = vertices.begin(); t != vertices.end(); ++t) 
    {
      // Verifica se aux_aresta é diferente de nulo
      if(aux_aresta == NULL)
        // Recebe a primeira aresta adjacente do vertice
        aux_aresta = *(*t)->adjacentes.begin();
      //Parei aqui
      for(w = (*t)->adjacentes.begin(); w != (*t)->adjacentes.end() && arvore->buscaVertice((*w)->getAdjacente()->getInfo()) != NULL; ++w) 
        
      if(w == (*t)->adjacentes.end())
        aux_aresta = NULL;

      if(aux_aresta != NULL)
      {
        for(; w != (*t)->adjacentes.end(); ++w) 
          if(aux_aresta->getPeso() > (*w)->getPeso())
            if(arvore->buscaVertice((*w)->getAdjacente()->getInfo()) == NULL)
              aux_aresta = *w;
        if(w == (*t)->adjacentes.end())
          aux_aresta = NULL;
      }
    }
    if(aux_aresta != NULL){
      Vertice * vertice_auxiliar = aux_aresta->getAdjacente();
      Vertice *aux = new Vertice(vertice_auxiliar->getInfo(), vertice_auxiliar->getPeso());
      arvore->vertices.push_back(aux);
      arvore->addAresta(aux_aresta->getOrigem()->getInfo(),aux_aresta->getAdjacente()->getInfo(),aux_aresta->getPeso());
    }
  }
  return arvore; 
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

    // Recebe o primeiro adjacente do vertice
    Aresta *aresta = *p->adjacentes.begin();
    
    // Verifica essa aresta é diferente de nulo
    if(aresta){
      // busca o primeiro valor dos vertices adjacentes e coloca como menor valor da lista
      int menor = auxFloyd(aresta->getAdjacente(), destino) + aresta->getPeso();
      
      // Enquanto aresta != adjacentes.fim faça
      for(vector<Aresta*>::iterator aresta = ++p->adjacentes.begin(); aresta != p->adjacentes.end(); ++aresta)
      {
        int aux = auxFloyd((*aresta)->getAdjacente(), destino) + (*aresta)->getPeso();
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
  Vertice *inicial = NULL;
  Vertice *final = NULL;
  // Busca os vertices no vetor de vertices
  for(vector<Vertice*>::iterator it = vertices.begin(); it != vertices.end() && (!inicial || !final); ++it)
  {
    if((*it)->getInfo() == origem)
      inicial = *it;
    else if((*it)->getInfo() == destino)
      final = *it;
  }
  
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


/*
* algoritmoKruskal() ir pegando a menor aresta sem formar ciclo, até todos os vertices
* estarem na arvore.
*/
Aresta ** Grafo::ordenaArestas()
{
  Aresta ** p = new Aresta*[numeroArestas];
  int count = 0;
  p[0] = menorValor;
  count ++;
  vector<Vertice*>::iterator q = vertices.begin();

  while(count != numeroArestas){
    for(vector<Aresta*>::iterator aux = (*q)->adjacentes.begin(); aux != (*q)->adjacentes.end(); ++aux){
      if((*aux)->getAdjacente()->getInfo() > to_string(count))//if necessario para a forma que as arestas sao feitas nao ficar duplicadas
        p[count] = *aux;
    }
    count ++;
  }
  for(int i = 0;i < numeroArestas;i++){
    for(int j = 0; j<numeroArestas;j++){
      if(p[j]->getPeso() < p[j+1]->getPeso()){
        Aresta * aux = p[j];
        p[j] = p[j+1];
        p[j+1] = aux;
      }
    }
  }
  return p;
}

bool Grafo::ciclo(string p, string q){

  if(buscaVertice(p) == NULL || buscaVertice(q) == NULL)
    return false;
  if(buscaPorLargura(p,q))
    return true;
  else 
    return false;
}

Grafo * Grafo::algoritmoKruskal(){

  Grafo * arvore = new Grafo();
  Vertice * p = menorValor->getOrigem();
  Vertice * q = menorValor->getAdjacente();
  Aresta ** listaOrdena = ordenaArestas();
  
  Vertice *aux = new Vertice(p->getInfo(),p->getPeso());
  arvore->vertices.push_back(aux);
  aux = new Vertice(q->getInfo(),q->getPeso());
  arvore->vertices.push_back(aux);
  arvore->addAresta(p->getInfo(), q->getInfo(), menorValor->getPeso());

  for(int i = 1; arvore->vertices.size() != numeroVertices; i++)
  {
    p = listaOrdena[i]->getOrigem();   
    q = listaOrdena[i]->getAdjacente();

    if(buscaVertice(p->getInfo()) == NULL)
    {
      aux = new Vertice(p->getInfo(),p->getPeso());
      arvore->vertices.push_back(aux);
    }
    if(buscaVertice(q->getInfo()) == NULL)
    {
      aux = new Vertice(p->getInfo(),p->getPeso());
      arvore->vertices.push_back(aux);
    }
    if(ciclo(p->getInfo(),q->getInfo()) == false){
      arvore->addAresta(p->getInfo(), q->getInfo(), menorValor->getPeso());
    }
  }
  return arvore;
}