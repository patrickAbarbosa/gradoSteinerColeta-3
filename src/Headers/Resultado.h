#ifndef RESULTADO_H
#define RESULTADP_H

#include "./Grafo.h"

class Grafo;

class Resultado
{
public:
    Resultado(){
        interacao = 0;
        alpha = 0;
        custo = 0;
        grafo = NULL;
    };
    ~Resultado(){ delete grafo; };
    int interacao;
    float alpha;
    float custo;
    Grafo *grafo;
};

#endif // End Resultado