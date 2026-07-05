#ifndef RTREE_H
#define RTREE_H

#include <vector>
#include <memory>
#include "QuadTree.h" // Importando o Retangulo da Leticia!

// A struct AreaVerde continua aqui para a R-Tree usar
struct AreaVerde {
    int id;
    Retangulo boundingBox;
};

const int MAX_ENTRIES = 4;
const int MIN_ENTRIES = 2;

class RTree {
public:
    struct No {
        bool isFolha;
        std::vector<Retangulo> mbrs;
        std::vector<std::shared_ptr<No>> filhos;
        std::vector<AreaVerde> dados;

        No(bool folha) : isFolha(folha) {}
    };

    RTree();
    ~RTree();

    void inserir(const AreaVerde& area);
    std::vector<AreaVerde> buscarPorRegiao(const Retangulo& regiaoBusca);

private:
    std::shared_ptr<No> raiz;

    Retangulo calcularMBR(const std::vector<Retangulo>& retangulos);
    bool intercepta(const Retangulo& r1, const Retangulo& r2);
    std::shared_ptr<No> inserirRecursivo(std::shared_ptr<No> no, const AreaVerde& area);
    void dividirNo(std::shared_ptr<No> no, std::shared_ptr<No> novoNo);
    void buscarRecursivo(std::shared_ptr<No> no, const Retangulo& regiaoBusca, std::vector<AreaVerde>& resultados);
};

#endif // RTREE_H
