#include "../Headers/Lista.h"


//construtor inicializa os ponteiros com NULL e a variavel com 0

Lista::Lista () {

	primeiro = NULL;
	maiorGrau = NULL;
	quantidade = 0;
}

Lista::~Lista()
{
	
	while(primeiro!=NULL)
	{
		Vertice *p = primeiro->getProx();
		delete primeiro;
		primeiro = p;
	}
	if(maiorGrau!=NULL)
		delete maiorGrau;
}

//insere um novo vertice a lista caso nao exista outro vertice com essa info

void Lista::insereVertice (string info, int peso) {
	cout << "aaa" << endl;
	if (primeiro == NULL) {
		cout << "ssss" << endl;
		cout << info << peso << endl;
		primeiro = new Vertice();
		cout << "llll" << endl;
		primeiro->setInfo(info);
		primeiro->setPeso(peso);
		cout << "criando" << endl;
		maiorGrau = primeiro;
		quantidade ++;
	}
	else if(buscaVertice(info) == NULL){
		cout << "xxxx" << endl;
		Vertice *p = primeiro;
		
		while (p->getProx() != NULL)
		    p = p->getProx();
		
		Vertice *novo = new Vertice (info, peso);
		p->setProx(novo);
		quantidade ++;
	}
	else{
		cout<<"Vertice: "<<info<<" ja existe!"<< endl;
	}
}

void Lista::insereVertice (Vertice * p){

	if (primeiro == NULL) {
		primeiro = p;
		maiorGrau = primeiro;
		quantidade ++;
		return;
	}
	if(buscaVertice(p->getInfo()) == NULL){
		Vertice *q = primeiro;
		
		while (q->getProx() != NULL)
		    q = q->getProx();
			
		q->setProx(p);
		quantidade ++;
	}
	else{
		cout<<"Vertice: "<<p->getInfo()<<" ja existe!"<< endl;
	}


}

// Busca o vertice usando a informacao na lista e caso nao exista retorna NULL

Vertice* Lista::buscaVertice(string info) {
	 
	Vertice * p = primeiro;
	
	while(p != NULL) {
		
		if(p->getInfo() == info)
			return p;
		p = p->getProx();
	}
	cout << "Nulo" << endl;
	return NULL;
}

//Deleta um vertice dado a info

void Lista::deletaVertice (string info) {
	
	Vertice * p = buscaVertice(info);
	Vertice * aux = primeiro;
	
	if( p == NULL){
		cout<<"ERRO: o Vertice "<<info<<" nao existe !";
		return;
	}

	if(p == maiorGrau){
		maiorGrau = NULL;
	}
	
	if(p == primeiro)
		primeiro = primeiro->getProx();
		
	else {
		
		while(aux->getProx() != p)
			aux = aux->getProx();

		aux->setProx(p->getProx());
		delete p; 
	}
	quantidade--;
}
