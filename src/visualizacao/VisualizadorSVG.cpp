#include "VisualizadorSVG.h"
#include <iostream>

using namespace std;

void VisualizadorSVG::desenharQuadTree(ofstream &arquivo, const QuadTree *qt)
{
    if (qt == nullptr) return;
    const Retangulo &r = qt->getLimite();

    arquivo << "<rect x=\"" << r.inferiorEsquerdo.x << "\" y=\"" << r.inferiorEsquerdo.y
            << "\" width=\"" << r.largura()
            << "\" height=\"" << r.altura()
            << "\" fill=\"none\" stroke=\"olive\" stroke-width=\"1\" />\n";

    for (const Ponto &p : qt->getPontos()) {
        desenharPonto(arquivo, p);
    }

    if (qt->estaDividida()) {
        desenharQuadTree(arquivo, qt->getNordeste());
        desenharQuadTree(arquivo, qt->getNoroeste());
        desenharQuadTree(arquivo, qt->getSudeste());
        desenharQuadTree(arquivo, qt->getSudoeste());
    }
}

void VisualizadorSVG::desenharPonto(ofstream &arquivo, const Ponto &ponto)
{
    arquivo << "<circle cx=\"" << ponto.x
            << "\" cy=\"" << ponto.y
            << "\" r=\"3\" fill=\"darkgreen\" />\n";
}

void VisualizadorSVG::exportar(const string &nomeArquivo, const QuadTree &qt)
{
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "[-] ERRO: Nao foi possivel salvar em '" << nomeArquivo << "'. A pasta 'resultados' existe neste diretorio?\n";
        return;
    }
    const Retangulo &limite = qt.getLimite();

    arquivo << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
            << "width=\"" << limite.largura() << "\" "
            << "height=\"" << limite.altura() << "\" "
            << "viewBox=\"" << limite.inferiorEsquerdo.x << " " << limite.inferiorEsquerdo.y << " "
            << limite.largura() << " " << limite.altura() << "\">\n";

    arquivo << "<rect x=\"" << limite.inferiorEsquerdo.x << "\" y=\"" << limite.inferiorEsquerdo.y
            << "\" width=\"" << limite.largura()
            << "\" height=\"" << limite.altura()
            << "\" fill=\"lightgreen\" stroke=\"black\" stroke-width=\"2\" />\n";

    desenharQuadTree(arquivo, &qt);

    arquivo << "</svg>\n";
    arquivo.close();
}

    arquivo.close();
}
