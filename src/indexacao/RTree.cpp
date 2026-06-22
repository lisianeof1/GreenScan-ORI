#include "RTree.h"
#include <algorithm>
#include <limits>

// --- Funções Auxiliares de Geometria (Locais) ---
double calcularArea(const Retangulo& r) {
    return r.largura * r.altura;
}

Retangulo unirRetangulos(const Retangulo& r1, const Retangulo& r2) {
    double minX = std::min(r1.x, r2.x);
    double minY = std::min(r1.y, r2.y);
    double maxX = std::max(r1.x + r1.largura, r2.x + r2.largura);
    double maxY = std::max(r1.y + r1.altura, r2.y + r2.altura);
    return {minX, minY, maxX - minX, maxY - minY};
}
// ------------------------------------------------

RTree::RTree() {
    raiz = std::make_shared<No>(true);
}

RTree::~RTree() {}

Retangulo RTree::calcularMBR(const std::vector<Retangulo>& retangulos) {
    if (retangulos.empty()) return {0, 0, 0, 0};
    
    Retangulo mbrTotal = retangulos[0];
    for (size_t i = 1; i < retangulos.size(); ++i) {
        mbrTotal = unirRetangulos(mbrTotal, retangulos[i]);
    }
    return mbrTotal;
}

void RTree::inserir(const AreaVerde& area) {
    inserirRecursivo(raiz, area);
}

void RTree::inserirRecursivo(std::shared_ptr<No> no, const AreaVerde& area) {
    if (no->isFolha) {
        // Se é folha, simplesmente adicionamos o dado e seu MBR
        no->dados.push_back(area);
        no->mbrs.push_back(area.boundingBox);
        
        // TODO (Próxima Etapa): Checar se passou de MAX_ENTRIES e fazer o Split.
    } else {
        // Lógica "ChooseLeaf": Encontrar o melhor filho para descer
        int melhorIndice = -1;
        double menorAumentoArea = std::numeric_limits<double>::max();

        for (size_t i = 0; i < no->filhos.size(); ++i) {
            Retangulo mbrAtual = no->mbrs[i];
            Retangulo mbrExpandido = unirRetangulos(mbrAtual, area.boundingBox);
            
            double aumentoArea = calcularArea(mbrExpandido) - calcularArea(mbrAtual);
            
            if (aumentoArea < menorAumentoArea) {
                menorAumentoArea = aumentoArea;
                melhorIndice = i;
            }
        }

        // Desce recursivamente para o melhor filho encontrado
        if (melhorIndice != -1) {
            inserirRecursivo(no->filhos[melhorIndice], area);
            
            // Após a inserção no filho, precisamos atualizar o MBR deste nó pai
            no->mbrs[melhorIndice] = unirRetangulos(no->mbrs[melhorIndice], area.boundingBox);
        }
    }
}

bool RTree::intercepta(const Retangulo& r1, const Retangulo& r2) {
    bool foraX = (r1.x + r1.largura < r2.x) || (r2.x + r2.largura < r1.x);
    bool foraY = (r1.y + r1.altura < r2.y) || (r2.y + r2.altura < r1.y);
    return !(foraX || foraY);
}

std::vector<AreaVerde> RTree::buscarPorRegiao(const Retangulo& regiaoBusca) {
    std::vector<AreaVerde> resultados;
    // TODO (Etapas futuras)
    return resultados;
}
