#include "RTree.h"
#include <algorithm>

RTree::RTree() {
    // A árvore inicializa com uma raiz vazia que é folha
    raiz = std::make_shared<No>(true);
}

RTree::~RTree() {
    // O uso de std::shared_ptr limpa a memória automaticamente
}

void RTree::inserir(const AreaVerde& area) {
    // Ponto de entrada da inserção. 
    // Por enquanto, chamamos a função recursiva básica.
    inserirRecursivo(raiz, area);
}

void RTree::inserirRecursivo(std::shared_ptr<No> no, const AreaVerde& area) {
    // TODO (Próxima Etapa): Implementar a lógica de descida na árvore,
    // escolha da melhor sub-árvore, adição do dado e lógica de Split 
    // caso o nó ultrapasse MAX_ENTRIES.
}

bool RTree::intercepta(const Retangulo& r1, const Retangulo& r2) {
    // Verifica se dois retângulos se sobrepõem (usado nas consultas)
    bool foraX = (r1.x + r1.largura < r2.x) || (r2.x + r2.largura < r1.x);
    bool foraY = (r1.y + r1.altura < r2.y) || (r2.y + r2.altura < r1.y);
    return !(foraX || foraY);
}

std::vector<AreaVerde> RTree::buscarPorRegiao(const Retangulo& regiaoBusca) {
    std::vector<AreaVerde> resultados;
    // TODO (Etapas futuras): Implementar a travessia da árvore verificando 
    // a interseção entre o MBR do nó e a regiaoBusca.
    return resultados;
}
