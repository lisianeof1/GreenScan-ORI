#ifndef RETANGULO_H
#define RETANGULO_H

#include "Ponto.h"

/**
 * Representa um retangulo definido por dois pontos:
 * o canto inferior esquerdo e o canto superior direito.
 * Header-only: nao possui .cpp associado.
 */
struct Retangulo {
    Ponto inferiorEsquerdo;
    Ponto superiorDireito;

    Retangulo(Ponto ie = Ponto(), Ponto sd = Ponto())
        : inferiorEsquerdo(ie), superiorDireito(sd) {}

    int largura() const {
        return superiorDireito.x - inferiorEsquerdo.x;
    }

    int altura() const {
        return superiorDireito.y - inferiorEsquerdo.y;
    }

    long area() const {
        return static_cast<long>(largura()) * static_cast<long>(altura());
    }

    // ADICIONE ESTE BLOCO AQUI EMBAIXO:
    bool tem_ponto(const Ponto& p) const {
        return p.x >= inferiorEsquerdo.x &&
               p.x <= superiorDireito.x &&
               p.y >= inferiorEsquerdo.y &&
               p.y <= superiorDireito.y;
    }
};

#endif // RETANGULO_H
