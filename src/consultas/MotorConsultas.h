#ifndef MOTOR_CONSULTAS_H
#define MOTOR_CONSULTAS_H

#include "../indexacao/RTree.h"
#include "../indexacao/QuadTree.h"
#include <vector>
#include <string>

class MotorConsultas {
private:
    RTree& rtree;
    QuadTree& quadtree;

    void contarQuadTreeRecursivo(const QuadTree* qt, int nivel);

public:
    MotorConsultas(RTree& rt, QuadTree& qt);

    std::vector<AreaVerde> executarBuscaPorRegiao(const Retangulo& regiao);
    void executarBuscaMaisProximo(double x, double y);
    std::vector<AreaVerde> executarBuscaPorDensidade(const std::string& densidade);
    void executarContagemQuadTree();
    void executarBuscaSobreposicao();
    std::vector<AreaVerde> executarBuscaPorRaio(double cx, double cy, double raio);
};

#endif
