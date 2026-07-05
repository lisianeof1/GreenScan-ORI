#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>

using namespace std;


struct Ponto{
    double x;
    double y;

    Ponto(double x = 0, double y = 0);
};

struct Retangulo{
    double x;
    double y;
    double largura;
    double altura;

    Retangulo(double x = 0, double y = 0, double largura = 0, double altura = 0);

    bool tem_ponto(const Ponto &p) const;
};

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