#include <iostream>
#include "indexacao/QuadTree.h"
#include "indexacao/RTree.h"
#include "consultas/MotorConsultas.h"
#include "visualizacao/VisualizadorSVG.h"

using namespace std;

void exibirMenu() {
    cout << "\n=== GREENSCAN: Sistema de Areas Verdes ===\n";
    cout << "1. Inserir Area Verde de Teste\n";
    cout << "2. Buscar Areas por Regiao\n";
    cout << "3. Exportar Mapa (SVG)\n";
    cout << "4. Sair\n";
    cout << "Escolha uma opcao: ";
}

int main() {
    // Inicializa o mapa de 1000x1000
    Retangulo areaMapa(0, 0, 1000, 1000);
    
    // Inicializa as estruturas
    QuadTree quadtree(areaMapa, 4);
    RTree rtree;
    MotorConsultas motor(rtree, quadtree);

    int opcao = 0;
    int idCounter = 1;

    while (opcao != 4) {
        exibirMenu();
        cin >> opcao;

        switch (opcao) {
            case 1: {
                double x, y, l, a;
                cout << "Digite as coordenadas (X Y Largura Altura) separadas por espaco:\n> ";
                cin >> x >> y >> l >> a;
                
                AreaVerde novaArea = {idCounter++, {x, y, l, a}};
                rtree.inserir(novaArea);
                
                // Inserindo o centro do retangulo na QuadTree da Leticia
                Ponto centro(x + (l/2), y + (a/2));
                quadtree.inserir(centro);
                
                cout << "[!] Area Verde inserida com sucesso em ambas as arvores!\n";
                break;
            }
            case 2: {
                double x, y, l, a;
                cout << "Digite a Regiao de Busca (X Y Largura Altura) separadas por espaco:\n> ";
                cin >> x >> y >> l >> a;
                Retangulo busca(x, y, l, a);
                
                vector<AreaVerde> resultados = motor.executarBuscaPorRegiao(busca);
                
                cout << "\n--- Resultados Encontrados (" << resultados.size() << ") ---\n";
                for (const auto& area : resultados) {
                    cout << "ID: " << area.id << " | X: " << area.boundingBox.x << " Y: " << area.boundingBox.y << "\n";
                }
                break;
            }
            case 3: {
                VisualizadorSVG::exportar("mapa_greenscan.svg", quadtree);
                cout << "[!] Arquivo mapa_greenscan.svg gerado com sucesso!\n";
                break;
            }
            case 4:
                cout << "Encerrando o sistema...\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    }

    return 0;
}
