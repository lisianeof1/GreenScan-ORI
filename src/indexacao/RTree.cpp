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
    // Agora capturamos se a recursão gerou um novo nó a partir da raiz
    std::shared_ptr<No> novoNo = inserirRecursivo(raiz, area);
    
    if (novoNo != nullptr) {
        // A raiz estourou a capacidade! Precisamos criar uma nova raiz acima dela.
        std::shared_ptr<No> novaRaiz = std::make_shared<No>(false);
        
        // Adiciona a raiz antiga como primeiro filho
        novaRaiz->filhos.push_back(raiz);
        novaRaiz->mbrs.push_back(calcularMBR(raiz->mbrs));
        
        // Adiciona o novo nó gerado pelo split como segundo filho
        novaRaiz->filhos.push_back(novoNo);
        novaRaiz->mbrs.push_back(calcularMBR(novoNo->mbrs));
        
        raiz = novaRaiz;
    }
}
}
std::shared_ptr<RTree::No> RTree::inserirRecursivo(std::shared_ptr<No> no, const AreaVerde& area) {
    if (no->isFolha) {
        no->dados.push_back(area);
        no->mbrs.push_back(area.boundingBox);
        
        // Verifica se estourou a capacidade máxima
        if (no->dados.size() > MAX_ENTRIES) {
            std::shared_ptr<No> novoNo = std::make_shared<No>(true);
            dividirNo(no, novoNo);
            return novoNo; // Retorna o novo nó para o pai lidar com ele
        }
        return nullptr; // Nenhum split necessário
    } else {
        // Lógica "ChooseLeaf" (já implementada na etapa anterior)
        int melhorIndice = -1;
        double menorAumentoArea = std::numeric_limits<double>::max();

        for (size_t i = 0; i < no->filhos.size(); ++i) {
            Retangulo mbrExpandido = unirRetangulos(no->mbrs[i], area.boundingBox);
            double aumentoArea = calcularArea(mbrExpandido) - calcularArea(no->mbrs[i]);
            
            if (aumentoArea < menorAumentoArea) {
                menorAumentoArea = aumentoArea;
                melhorIndice = i;
            }
        }

        // Descida recursiva
        std::shared_ptr<No> novoFilho = inserirRecursivo(no->filhos[melhorIndice], area);
        
        // Atualiza o MBR do filho escolhido
        no->mbrs[melhorIndice] = unirRetangulos(no->mbrs[melhorIndice], area.boundingBox);
        
        // Se a descida gerou um novo filho (o filho splitou), precisamos acomodá-lo neste nó
        if (novoFilho != nullptr) {
            no->filhos.push_back(novoFilho);
            no->mbrs.push_back(calcularMBR(novoFilho->mbrs));
            
            // Verifica se este nó pai também estourou a capacidade
            if (no->filhos.size() > MAX_ENTRIES) {
                std::shared_ptr<No> novoNoPai = std::make_shared<No>(false);
                dividirNo(no, novoNoPai);
                return novoNoPai; // Propaga o split para cima
            }
        }
        return nullptr;
    }
}

void RTree::dividirNo(std::shared_ptr<No> no, std::shared_ptr<No> novoNo) {
    // Calcula o ponto de corte (metade simples)
    size_t meio = no->mbrs.size() / 2;
    
    // Transfere a segunda metade dos MBRs para o novo nó
    novoNo->mbrs.assign(no->mbrs.begin() + meio, no->mbrs.end());
    no->mbrs.erase(no->mbrs.begin() + meio, no->mbrs.end());
    
    if (no->isFolha) {
        // Se for folha, divide também os dados (Áreas Verdes)
        novoNo->dados.assign(no->dados.begin() + meio, no->dados.end());
        no->dados.erase(no->dados.begin() + meio, no->dados.end());
    } else {
        // Se for nó interno, divide os ponteiros dos filhos
        novoNo->filhos.assign(no->filhos.begin() + meio, no->filhos.end());
        no->filhos.erase(no->filhos.begin() + meio, no->filhos.end());
    }
}
