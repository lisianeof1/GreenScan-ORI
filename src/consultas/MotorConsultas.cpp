#include "MotorConsultas.h"

MotorConsultas::MotorConsultas(RTree& rt, QuadTree& qt) : rtree(rt), quadtree(qt) {}

std::vector<AreaVerde> MotorConsultas::executarBuscaPorRegiao(const Retangulo& regiao) {
    // Repassa a responsabilidade para a busca otimizada da sua R-Tree
    return rtree.buscarPorRegiao(regiao);
}
