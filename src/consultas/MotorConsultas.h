#ifndef MOTOR_CONSULTAS_H
#define MOTOR_CONSULTAS_H

#include "../indexacao/RTree.h"
#include "../indexacao/QuadTree.h"
#include <vector>

class MotorConsultas {
private:
    RTree& rtree;
    QuadTree& quadtree;

public:
    // O motor guarda a referência das duas árvores ativas no sistema
    MotorConsultas(RTree& rt, QuadTree& qt);

    // Consulta 1: Busca por Região (usando a R-Tree que você implementou)
    std::vector<AreaVerde> executarBuscaPorRegiao(const Retangulo& regiao);
    
    // As outras consultas entrarão aqui nas próximas etapas!
};

#endif
