#include "QuadTree.h"

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
    int x = limite.inferiorEsquerdo.x;
    int y = limite.inferiorEsquerdo.y;
    int metadeLargura = limite.largura() / 2;
    int metadeAltura = limite.altura() / 2;

    Retangulo areaNO(Ponto(x, y), Ponto(x + metadeLargura, y + metadeAltura));
    Retangulo areaNE(Ponto(x + metadeLargura, y), Ponto(x + limite.largura(), y + metadeAltura));
    Retangulo areaSO(Ponto(x, y + metadeAltura), Ponto(x + metadeLargura, y + limite.altura()));
    Retangulo areaSE(Ponto(x + metadeLargura, y + metadeAltura), Ponto(x + limite.largura(), y + limite.altura()));

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
