#ifndef NODATA_H_INCLUDED
#define NODATA_H_INCLUDED

#include <iostream>

using namespace std;

class NoData
{
  public:
    NoData(){};
    ~NoData(){};

    void setDescricao(string descricao){ this->descricao = descricao; };
    string getDescricao(){ return descricao; };
    
    void setValor(string val){ this->val = val; };
    string getVal(){ return val; };

    void setProx(NoData *p){ prox = p; };
    NoData *getProx(){ return prox; };

  private:
    string descricao;
    string val;

    NoData *prox;
};

#endif // NODATA_H_INCLUDED
