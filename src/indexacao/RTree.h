#ifndef RTREE_H
#define RTREE_H

#include <vector>
#include <memory>
#include <string>
#include "../indexacao/QuadTree.h" // Retangulo vem daqui

struct AreaVerde {
    int id;
    Retangulo boundingBox;
    std::string nome;
    std::string tipo;
    std::string densidade; 
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
    
    // Novas consultas espaciais
    std::vector<AreaVerde> buscarPorDensidade(const std::string& densidade);
    std::vector<std::pair<AreaVerde, AreaVerde>> buscarSobreposicoes();
    std::vector<AreaVerde> buscarPorRaio(double cx, double cy, double raio);
    AreaVerde* buscarVizinhoMaisProximo(double x, double y);

private:
    std::shared_ptr<No> raiz;

    Retangulo calcularMBR(const std::vector<Retangulo>& retangulos);
    bool intercepta(const Retangulo& r1, const Retangulo& r2);
    std::shared_ptr<No> inserirRecursivo(std::shared_ptr<No> no, const AreaVerde& area);
    void dividirNo(std::shared_ptr<No> no, std::shared_ptr<No> novoNo);
    void buscarRecursivo(std::shared_ptr<No> no, const Retangulo& regiaoBusca, std::vector<AreaVerde>& resultados);
    void coletarTodas(std::shared_ptr<No> no, std::vector<AreaVerde>& todas);
    double distanciaPontoRetangulo(double px, double py, const Retangulo& r);
};

#endif // RTREE_H
