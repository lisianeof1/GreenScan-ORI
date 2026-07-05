#include "QuadTree.h"
#include "VisualizadorSVG.h"

int main(void){
    Retangulo areaMapa(0, 0, 500, 500);

    QuadTree qt(areaMapa, 4);

    qt.inserir(Ponto(100, 100));
    qt.inserir(Ponto(120, 130));
    qt.inserir(Ponto(140, 110));
    qt.inserir(Ponto(160, 150));
    qt.inserir(Ponto(300, 300));
    qt.inserir(Ponto(210, 200));
    qt.inserir(Ponto(350, 320));
    qt.inserir(Ponto(400, 400));
    qt.inserir(Ponto(460, 470));
    qt.inserir(Ponto(310, 220));
    qt.inserir(Ponto(440, 410));
    qt.inserir(Ponto(50, 450));
    qt.inserir(Ponto(110, 110));
    qt.inserir(Ponto(130, 120));
    qt.inserir(Ponto(150, 140));
    qt.inserir(Ponto(250, 450));
    qt.inserir(Ponto(430, 440));
    qt.inserir(Ponto(320, 460));
    qt.inserir(Ponto(250, 220));
    qt.inserir(Ponto(260, 230));
    qt.inserir(Ponto(170, 50));
    qt.inserir(Ponto(320, 60));
    qt.inserir(Ponto(200, 70));
    qt.inserir(Ponto(440, 270));
    qt.inserir(Ponto(440, 480));
    qt.inserir(Ponto(460, 470));
    qt.inserir(Ponto(290, 270));
    qt.inserir(Ponto(220, 240));
    qt.inserir(Ponto(60, 60));
    qt.inserir(Ponto(30, 40));
    qt.inserir(Ponto(50, 20));
    qt.inserir(Ponto(60, 90));
    qt.inserir(Ponto(40, 20));
    qt.inserir(Ponto(30, 20));
    qt.inserir(Ponto(40, 30));
    qt.inserir(Ponto(70, 20));
    qt.inserir(Ponto(80, 90));
    qt.inserir(Ponto(60, 100));
    qt.inserir(Ponto(110, 130));
    qt.inserir(Ponto(80, 140));
    qt.inserir(Ponto(240, 160));
    qt.inserir(Ponto(80, 70));

    VisualizadorSVG::exportar("quadtree.svg", qt);

    return 0;
}