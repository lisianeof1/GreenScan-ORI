#include <iostream>
#include <string>
#include "indexacao/QuadTree.h"
#include "indexacao/RTree.h"
#include "consultas/MotorConsultas.h"
#include "visualizacao/VisualizadorSVG.h"

using namespace std;

void exibirMenu() {
    cout << "\n=== GREENSCAN: Menu de Consultas ===\n";
    cout << "1. Inserir Area Verde Manual\n";
    cout << "2. Consulta: Areas dentro de uma Regiao (R-Tree)\n";
    cout << "3. Consulta: Vizinho Mais Proximo (R-Tree)\n";
    cout << "4. Consulta: Areas por Densidade (R-Tree)\n";
    cout << "5. Consulta: Quantidade por Regiao (QuadTree)\n";
    cout << "6. Consulta: Sobreposicao de Areas (R-Tree)\n";
    cout << "7. Consulta: Areas dentro de um Raio (R-Tree)\n";
    cout << "8. Exportar Mapa para SVG\n";
    cout << "9. Sair\n";
    cout << "Escolha uma opcao: ";
}

void exemplo_resultado_QuadTree(){
    Retangulo area(0, 0, 500, 500);
    QuadTree qt(area, 4);

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

    VisualizadorSVG::exportar("resultados/quadtree.svg", qt); 
}

int main() {
    Retangulo areaMapa(0, 0, 1000, 1000);
    QuadTree quadtree(areaMapa, 4);
    RTree rtree;
    MotorConsultas motor(rtree, quadtree);

    int opcao = 0;
    int idCounter = 1;

    while (opcao != 9) {
        exibirMenu();
        cin >> opcao;

        switch (opcao) {
            case 1: {
                double x, y, l, a;
                string nome, tipo, densidade;
                cout << "Coordenadas (X Y Larg Alt) separadas por espaco: ";
                cin >> x >> y >> l >> a;
                cout << "Nome da Area: "; cin >> ws; getline(cin, nome);
                cout << "Tipo (Parque, Praca, etc): "; getline(cin, tipo);
                cout << "Densidade (Alta, Media, Baixa): "; getline(cin, densidade);
                
                AreaVerde novaArea = {idCounter++, {x, y, l, a}, nome, tipo, densidade};
                rtree.inserir(novaArea);
                
                Ponto centro(x + (l/2), y + (a/2));
                quadtree.inserir(centro);
                cout << "[!] Sucesso.\n";
                break;
            }
            case 2: {
                double x, y, l, a;
                cout << "Regiao de Busca (X Y Larg Alt): ";
                cin >> x >> y >> l >> a;
                vector<AreaVerde> res = motor.executarBuscaPorRegiao({x, y, l, a});
                for (const auto& area : res) cout << "ID: " << area.id << " | " << area.nome << "\n";
                break;
            }
            case 3: {
                double x, y;
                cout << "Ponto de Origem (X Y): "; cin >> x >> y;
                motor.executarBuscaMaisProximo(x, y);
                break;
            }
            case 4: {
                string densidade;
                cout << "Densidade desejada: "; cin >> ws; getline(cin, densidade);
                vector<AreaVerde> res = motor.executarBuscaPorDensidade(densidade);
                for (const auto& area : res) cout << "ID: " << area.id << " | " << area.nome << "\n";
                break;
            }
            case 5: {
                motor.executarContagemQuadTree();
                break;
            }
            case 6: {
                motor.executarBuscaSobreposicao();
                break;
            }
            case 7: {
                double x, y, raio;
                cout << "Centro do Raio (X Y Raio): "; cin >> x >> y >> raio;
                vector<AreaVerde> res = motor.executarBuscaPorRaio(x, y, raio);
                for (const auto& area : res) cout << "ID: " << area.id << " | " << area.nome << "\n";
                break;
            }
            case 8: {
                VisualizadorSVG::exportar("resultados/mapa_greenscan.svg", quadtree);
                cout << "[!] SVG gerado.\n";
                break;
            }
            case 9:
                break;
            default:
                cout << "Opcao invalida.\n";
        }
    }

    //exemplo para simplificar
    exemplo_resultado_QuadTree();
    
    return 0;
}
