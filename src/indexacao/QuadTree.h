#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "../core/Ponto.h"
#include "../core/Retangulo.h"

using namespace std;

class QuadTree{
    private:
    Retangulo limite;
    int capacidade;
    vector<Ponto> pontos;

    bool dividida;

    QuadTree* nordeste;
    QuadTree* noroeste;
    QuadTree* sudeste;
    QuadTree* sudoeste;

    void subdividir();

    public:
    QuadTree(const Retangulo &limite, int capacidade);
    ~QuadTree();

    bool inserir(const Ponto &ponto);

    const Retangulo& getLimite() const;
    const vector<Ponto>& getPontos() const;

    bool estaDividida() const;

    QuadTree* getNordeste() const;
    QuadTree* getNoroeste() const;
    QuadTree* getSudeste() const;
    QuadTree* getSudoeste() const;
};

#endif
