#ifndef RTREE_H
#define RTREE_H

#include <vector>
#include <memory>

// =========================================================================
// MOCKS (Simulações temporárias do Módulo Core da Kamila para podermos testar)
// Quando ela terminar, apagaremos isso e faremos o #include dos arquivos dela.
struct Retangulo {
    double x, y, largura, altura;
};

struct AreaVerde {
    int id;
    Retangulo boundingBox;
};
// =========================================================================

// Constantes da R-Tree
const int MAX_ENTRIES = 4; // Capacidade máxima de um nó (M)
const int MIN_ENTRIES = 2; // Capacidade mínima de um nó (m)

class RTree {
public:
    // Estrutura interna do Nó da R-Tree
    struct No {
        bool isFolha;
        std::vector<Retangulo> mbrs; // Minimum Bounding Rectangles das entradas
        std::vector<std::shared_ptr<No>> filhos; // Ponteiros para os filhos (se não for folha)
        std::vector<AreaVerde> dados; // Dados reais (apenas se for folha)

        No(bool folha) : isFolha(folha) {}
    };

    RTree();
    ~RTree();

    // Métodos principais que você usará no Motor de Consultas
    void inserir(const AreaVerde& area);
    std::vector<AreaVerde> buscarPorRegiao(const Retangulo& regiaoBusca);

private:
    std::shared_ptr<No> raiz;

    // Métodos auxiliares internos
    Retangulo calcularMBR(const std::vector<Retangulo>& retangulos);
    bool intercepta(const Retangulo& r1, const Retangulo& r2);
    
    // ATUALIZAÇÃO: Agora retorna um ponteiro para um novo nó caso ocorra um Split
    std::shared_ptr<No> inserirRecursivo(std::shared_ptr<No> no, const AreaVerde& area);
    
    // NOVO: Método para lidar com a divisão do array
    void dividirNo(std::shared_ptr<No> no, std::shared_ptr<No> novoNo);
};

#endif // RTREE_H
