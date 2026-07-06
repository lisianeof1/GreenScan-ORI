#include "QuadTree.h"

Ponto::Ponto(double x, double y){
    this->x = x;
    this->y = y;
}

Retangulo::Retangulo(double x, double y, double largura, double altura){
    this->x = x;
    this->y = y;
    this->largura = largura;
    this->altura = altura;
}

bool Retangulo::tem_ponto(const Ponto &p) const{
    return p.x >= x &&
           p.x <= x + largura &&
           p.y >= y &&
           p.y <= y + altura;
}

QuadTree::QuadTree(const Retangulo &limite, int capacidade){
    this->limite = limite;
    this->capacidade = capacidade;

    dividida = false;

    nordeste = nullptr;
    noroeste = nullptr;
    sudeste = nullptr;
    sudoeste = nullptr;
};

QuadTree::~QuadTree(){
    delete nordeste;
    delete noroeste;
    delete sudeste;
    delete sudoeste;
};

void QuadTree::subdividir(){
    double x = limite.x;
    double y = limite.y;
    double metadeLargura = limite.largura / 2.0;
    double metadeAltura = limite.altura / 2.0;

    Retangulo areaNO(x, y, metadeLargura, metadeAltura);
    Retangulo areaNE(x + metadeLargura, y, metadeLargura, metadeAltura);
    Retangulo areaSO(x, y + metadeAltura, metadeLargura, metadeAltura);
    Retangulo areaSE(x + metadeLargura, y + metadeAltura, metadeLargura, metadeAltura);

    nordeste = new QuadTree(areaNE, capacidade);
    noroeste = new QuadTree(areaNO, capacidade);
    sudeste = new QuadTree(areaSE, capacidade);
    sudoeste = new QuadTree(areaSO, capacidade);
    
    dividida = true;
};

bool QuadTree::inserir(const Ponto &ponto){
    if(!limite.tem_ponto(ponto)) return false;

    if(pontos.size() < capacidade && !dividida){
        pontos.push_back(ponto);
        return true;
    }

    if(!dividida){
        subdividir();

        for(const Ponto &p : pontos){
            nordeste->inserir(p);
            noroeste->inserir(p);
            sudeste->inserir(p);
            sudoeste->inserir(p);
        }

        pontos.clear();
    }

    if(nordeste->inserir(ponto)) return true;
    if(noroeste->inserir(ponto)) return true;
    if(sudeste->inserir(ponto)) return true;
    if(sudoeste->inserir(ponto)) return true;

    return false;
};

const Retangulo& QuadTree::getLimite() const{
    return limite;
};

const vector<Ponto>& QuadTree::getPontos() const{
    return pontos;
};

bool QuadTree::estaDividida() const{
    return dividida;
};

QuadTree* QuadTree::getNordeste() const{
    return nordeste;
};

QuadTree* QuadTree::getNoroeste() const{
    return noroeste;
};

QuadTree* QuadTree::getSudeste() const{
    return sudeste;
};

QuadTree* QuadTree::getSudoeste() const{
    return sudoeste;
};