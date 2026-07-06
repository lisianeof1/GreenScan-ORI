#ifndef VISUALIZADOR_SVG_H
#define VISUALIZADOR_SVG_H

#include<string>
#include<fstream>
#include "../indexacao/QuadTree.h"

class VisualizadorSVG{
    private:
    static void desenharQuadTree(ofstream& arquivo, const QuadTree* qt);

    static void desenharPonto(ofstream& arquivo, const Ponto &ponto);

    public:
    static void exportar(const string &nomeArquivo, const QuadTree &qt);
};

#endif