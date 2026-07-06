#include "RTree.h"
#include <algorithm>
#include <limits>
#include <cmath>

double calcularArea(const Retangulo& r) { 
    return r.area();
}

Retangulo unirRetangulos(const Retangulo& r1, const Retangulo& r2) {
    int minX = std::min(r1.inferiorEsquerdo.x, r2.inferiorEsquerdo.x);
    int minY = std::min(r1.inferiorEsquerdo.y, r2.inferiorEsquerdo.y);
    int maxX = std::max(r1.superiorDireito.x, r2.superiorDireito.x);
    int maxY = std::max(r1.superiorDireito.y, r2.superiorDireito.y);
    
    return Retangulo(Ponto(minX, minY), Ponto(maxX, maxY));
}

RTree::RTree() { raiz = std::make_shared<No>(true); }
RTree::~RTree() {}

Retangulo RTree::calcularMBR(const std::vector<Retangulo>& retangulos) {
    if (retangulos.empty()) return Retangulo();
    Retangulo mbrTotal = retangulos[0];
    for (size_t i = 1; i < retangulos.size(); ++i) {
        mbrTotal = unirRetangulos(mbrTotal, retangulos[i]);
    }
    return mbrTotal;
}

void RTree::inserir(const AreaVerde& area) {
    std::shared_ptr<No> novoNo = inserirRecursivo(raiz, area);
    if (novoNo != nullptr) {
        std::shared_ptr<No> novaRaiz = std::make_shared<No>(false);
        novaRaiz->filhos.push_back(raiz);
        novaRaiz->mbrs.push_back(calcularMBR(raiz->mbrs));
        novaRaiz->filhos.push_back(novoNo);
        novaRaiz->mbrs.push_back(calcularMBR(novoNo->mbrs));
        raiz = novaRaiz;
    }
}

std::shared_ptr<RTree::No> RTree::inserirRecursivo(std::shared_ptr<No> no, const AreaVerde& area) {
    if (no->isFolha) {
        no->dados.push_back(area);
        no->mbrs.push_back(area.getRetangulo());
        if (no->dados.size() > MAX_ENTRIES) {
            std::shared_ptr<No> novoNo = std::make_shared<No>(true);
            dividirNo(no, novoNo);
            return novoNo; 
        }
        return nullptr; 
    } else {
        int melhorIndice = -1;
        double menorAumentoArea = std::numeric_limits<double>::max();
        for (size_t i = 0; i < no->filhos.size(); ++i) {
            Retangulo mbrExpandido = unirRetangulos(no->mbrs[i], area.getRetangulo());
            double aumentoArea = calcularArea(mbrExpandido) - calcularArea(no->mbrs[i]);
            if (aumentoArea < menorAumentoArea) {
                menorAumentoArea = aumentoArea;
                melhorIndice = i;
            }
        }
        std::shared_ptr<No> novoFilho = inserirRecursivo(no->filhos[melhorIndice], area);
        no->mbrs[melhorIndice] = unirRetangulos(no->mbrs[melhorIndice], area.getRetangulo());
        if (novoFilho != nullptr) {
            no->filhos.push_back(novoFilho);
            no->mbrs.push_back(calcularMBR(novoFilho->mbrs));
            if (no->filhos.size() > MAX_ENTRIES) {
                std::shared_ptr<No> novoNoPai = std::make_shared<No>(false);
                dividirNo(no, novoNoPai);
                return novoNoPai; 
            }
        }
        return nullptr;
    }
}

void RTree::dividirNo(std::shared_ptr<No> no, std::shared_ptr<No> novoNo) {
    size_t meio = no->mbrs.size() / 2;
    novoNo->mbrs.assign(no->mbrs.begin() + meio, no->mbrs.end());
    no->mbrs.erase(no->mbrs.begin() + meio, no->mbrs.end());
    if (no->isFolha) {
        novoNo->dados.assign(no->dados.begin() + meio, no->dados.end());
        no->dados.erase(no->dados.begin() + meio, no->dados.end());
    } else {
        novoNo->filhos.assign(no->filhos.begin() + meio, no->filhos.end());
        no->filhos.erase(no->filhos.begin() + meio, no->filhos.end());
    }
}

bool RTree::intercepta(const Retangulo& r1, const Retangulo& r2) {
    bool foraX = (r1.superiorDireito.x < r2.inferiorEsquerdo.x) || (r2.superiorDireito.x < r1.inferiorEsquerdo.x);
    bool foraY = (r1.superiorDireito.y < r2.inferiorEsquerdo.y) || (r2.superiorDireito.y < r1.inferiorEsquerdo.y);
    return !(foraX || foraY);
}

void RTree::buscarRecursivo(std::shared_ptr<No> no, const Retangulo& regiaoBusca, std::vector<AreaVerde>& resultados) {
    if (no->isFolha) {
        for (size_t i = 0; i < no->dados.size(); ++i) {
            if (intercepta(no->mbrs[i], regiaoBusca)) {
                resultados.push_back(no->dados[i]);
            }
        }
    } else {
        for (size_t i = 0; i < no->filhos.size(); ++i) {
            if (intercepta(no->mbrs[i], regiaoBusca)) {
                buscarRecursivo(no->filhos[i], regiaoBusca, resultados);
            }
        }
    }
}

std::vector<AreaVerde> RTree::buscarPorRegiao(const Retangulo& regiaoBusca) {
    std::vector<AreaVerde> resultados;
    buscarRecursivo(raiz, regiaoBusca, resultados);
    return resultados;
}

// --- CONSULTAS OBRIGATÓRIAS ---

void RTree::coletarTodas(std::shared_ptr<No> no, std::vector<AreaVerde>& todas) {
    if (no->isFolha) {
        for (const auto& area : no->dados) todas.push_back(area);
    } else {
        for (auto filho : no->filhos) coletarTodas(filho, todas);
    }
}

std::vector<AreaVerde> RTree::buscarPorDensidade(const std::string& densidade) {
    std::vector<AreaVerde> todas, filtradas;
    coletarTodas(raiz, todas);
    for(const auto& a : todas) {
        if(a.getTipoVegetacao() == densidade) filtradas.push_back(a);
    }
    return filtradas;
}

std::vector<std::pair<AreaVerde, AreaVerde>> RTree::buscarSobreposicoes() {
    std::vector<AreaVerde> todas;
    std::vector<std::pair<AreaVerde, AreaVerde>> sobreposicoes;
    coletarTodas(raiz, todas);
    
    for (size_t i = 0; i < todas.size(); ++i) {
        for (size_t j = i + 1; j < todas.size(); ++j) {
            if (intercepta(todas[i].getRetangulo(), todas[j].getRetangulo())) {
                sobreposicoes.push_back({todas[i], todas[j]});
            }
        }
    }
    return sobreposicoes;
}

double RTree::distanciaPontoRetangulo(double px, double py, const Retangulo& r) {
    double dx = std::max({0.0, static_cast<double>(r.inferiorEsquerdo.x) - px, px - static_cast<double>(r.superiorDireito.x)});
    double dy = std::max({0.0, static_cast<double>(r.inferiorEsquerdo.y) - py, py - static_cast<double>(r.superiorDireito.y)});
    return std::sqrt(dx*dx + dy*dy);
}

std::vector<AreaVerde> RTree::buscarPorRaio(double cx, double cy, double raio) {
    std::vector<AreaVerde> todas, noRaio;
    coletarTodas(raiz, todas);
    for(const auto& a : todas) {
        if (distanciaPontoRetangulo(cx, cy, a.getRetangulo()) <= raio) {
            noRaio.push_back(a);
        }
    }
    return noRaio;
}

AreaVerde* RTree::buscarVizinhoMaisProximo(double x, double y) {
    std::vector<AreaVerde> todas;
    coletarTodas(raiz, todas);
    if(todas.empty()) return nullptr;

    AreaVerde* maisProximo = nullptr;
    double menorDistancia = std::numeric_limits<double>::max();

    for(auto& a : todas) {
        double dist = distanciaPontoRetangulo(x, y, a.getRetangulo());
        if (dist < menorDistancia) {
            menorDistancia = dist;
            maisProximo = new AreaVerde(a.getId(), a.getNome(), a.getRetangulo(), a.getTipoVegetacao());
        }
    }
    return maisProximo;
}
