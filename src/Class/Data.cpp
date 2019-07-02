#include <iostream>

#include "../Headers/Data.h"
#include "../Headers/NoData.h"

Data::Data(){
  n = 0;
  primeiro = NULL;
  ultimo = NULL;
}

Data::~Data(){
  while(primeiro != NULL)
  {
    ultimo = primeiro->getProx();
    delete primeiro;
    primeiro = ultimo;
  }
}

void Data::add(string descricao, string val)
{
  NoData *p = new NoData();

  p->setDescricao(descricao);
  p->setValor(val);
  p->setProx(NULL);
  if(primeiro == NULL)
  {
    primeiro = p;
    ultimo = p;
  }
  else
  {
      NoData *aux = primeiro;
      while(aux->getProx() != NULL)
        aux = aux->getProx();
      
      aux->setProx(p);
  }
}

NoData* Data::getK(int k)
{
  NoData *p = primeiro;
  NoData *ant = NULL;
  if(p)
  {
    for(int i = 0; i != k && p != NULL; i++)
    {
      ultimo = p;
      p = p->getProx();
    }

    if(primeiro == ultimo && primeiro == p)
      primeiro = ultimo = NULL;
    
    else if(primeiro == p)
      primeiro = p->getProx();
    
    else if(ultimo == p)
    {
      ultimo = ant;
      ultimo->setProx(NULL);
    }
    
    delete p;
  }
  else
    cout << "Nenhum dado armazenado."<< endl;
  return NULL;
}