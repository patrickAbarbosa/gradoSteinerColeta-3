#include "../Headers/FilaPrioridade.h"
#include "../Headers/Aresta.h"
#include "../Hearders/Vertice.h"

// Construtor da classe
FilaPrioridade::FilaPrioridade()
{
	primeiro = NULL;
	ultimo = NULL;
}

// Destrutor da classe
FilaPrioridade::~FilaPrioridade()
{
	while(retira() != NULL); 
}

// Verifica se a fila está vazia
bool FilaPrioridade::vazia()
{
	if(primeiro == NULL)
		return true;
	else
		return false;
}

//entra no final da FilaPrioridade
void FilaPrioridade::insere(Aresta * p){ 
	if(primeiro == NULL) {
    primeiro = p;
    ultimo = p;
  }
  else
  {

  }
}

// Retira o primeiro da Fila
Aresta * FilaPrioridade::retira(){

	if(primeiro == NULL) //FilaPrioridade vazia
		return NULL;
	else
	{
		Aresta * p = primeiro;
		primeiro = p->getProx();
		if(!primeiro)
			ultimo = NULL;
		return p;
	}
}