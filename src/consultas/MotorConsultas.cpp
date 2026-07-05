#include "MotorConsultas.h"
#include <iostream>

using namespace std;

MotorConsultas::MotorConsultas(RTree& rt, QuadTree& qt) : rtree(rt), quadtree(qt) {}

std::vector<AreaVerde> MotorConsultas::executarBuscaPorRegiao(const Retangulo& regiao) {
    return rtree.buscarPorRegiao(regiao);
}

void MotorConsultas::executarBuscaMaisProximo(double x, double y) {
    AreaVerde* area = rtree.buscarVizinhoMaisProximo(x, y);
    if (area != nullptr) {
        cout << "Vizinho mais proximo: ID " << area->id << " (" << area->nome << ")\n";
        delete area;
    } else {
        cout << "Nenhuma area verde cadastrada.\n";
    }
}

std::vector<AreaVerde> MotorConsultas::executarBuscaPorDensidade(const std::string& densidade) {
    return rtree.buscarPorDensidade(densidade);
}

void MotorConsultas::contarQuadTreeRecursivo(const QuadTree* qt, int nivel) {
    if (!qt) return;
    const Retangulo& r = qt->getLimite();
    cout << "Nivel " << nivel << " [Regiao X:" << r.x << " Y:" << r.y << "]: " 
         << qt->getPontos().size() << " areas verdes.\n";
         
    if (qt->estaDividida()) {
        contarQuadTreeRecursivo(qt->getNordeste(), nivel + 1);
        contarQuadTreeRecursivo(qt->getNoroeste(), nivel + 1);
        contarQuadTreeRecursivo(qt->getSudeste(), nivel + 1);
        contarQuadTreeRecursivo(qt->getSudoeste(), nivel + 1);
    }
}

void MotorConsultas::executarContagemQuadTree() {
    cout << "--- Contagem de Areas por Regiao da QuadTree ---\n";
    contarQuadTreeRecursivo(&quadtree, 0);
}

void MotorConsultas::executarBuscaSobreposicao() {
    auto sobreposicoes = rtree.buscarSobreposicoes();
    if (sobreposicoes.empty()) {
        cout << "Nenhuma area verde se sobrepoe.\n";
    } else {
        for (const auto& par : sobreposicoes) {
            cout << "Conflito Espacial: ID " << par.first.id << " cruza com ID " << par.second.id << "\n";
        }
    }
}

std::vector<AreaVerde> MotorConsultas::executarBuscaPorRaio(double cx, double cy, double raio) {
    return rtree.buscarPorRaio(cx, cy, raio);
}
