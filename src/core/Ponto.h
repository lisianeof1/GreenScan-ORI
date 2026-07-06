#ifndef PONTO_H
#define PONTO_H

/**
 * Representa um ponto em um plano cartesiano de coordenadas inteiras.
 * Header-only: nao possui .cpp associado.
 */
struct Ponto {
    int x;
    int y;

    Ponto(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Ponto& outro) const {
        return x == outro.x && y == outro.y;
    }
};

#endif // PONTO_H
