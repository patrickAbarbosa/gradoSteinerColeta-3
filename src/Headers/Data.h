#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <iostream>
#include "./NoData.h"

using namespace std;

class Data
{
  public:
    Data();
    ~Data();

    void add(string descricao, string val);
    void deleta(int k);
    NoData *getK(int k);
    
  private:
    NoData *primeiro;
    NoData *ultimo;
    
    int n;
};

#endif // NODATA_H_INCLUDED