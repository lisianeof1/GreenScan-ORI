#include <iostream>
#include <string>
#include <vector>

// Inclusões dos Módulos Core e Armazenamento (Kamila)
#include "core/Ponto.h"
#include "core/Retangulo.h"
#include "core/AreaVerde.h"
#include "armazenamento/GerenciadorArquivos.h"

// Inclusões de Indexação, Consultas e Visualização (Lisiane e Letícia)
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
    cout << "4. Consulta: Areas por Tipo de Vegetacao (R-Tree)\n";
    cout << "5. Consulta: Quantidade por Regiao (QuadTree)\n";
    cout << "6. Consulta: Sobreposicao de Areas (R-Tree)\n";
    cout << "7. Consulta: Areas dentro de um Raio (R-Tree)\n";
    cout << "8. Exportar Mapa para SVG\n";
    cout << "9. Sair\n";
    cout << "Escolha uma opcao: ";
}

void exemplo_resultado_QuadTree(){
    Retangulo area(Ponto(0, 0), Ponto(500, 500));
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

    VisualizadorSVG::exportar("resultados/quadtree_exemplo.svg", qt);
}

int main() {
    Retangulo areaMapa(Ponto(0, 0), Ponto(1000, 1000));
    QuadTree quadtree(areaMapa, 4);
    RTree rtree;
    MotorConsultas motor(rtree, quadtree);

    int opcao = 0;
    int idCounter = 1;
    string arquivoDados = "areas_verdes.txt";

    cout << "Inicializando GreenScan...\n";
    // Integração: Carregando dados do disco no início do programa
    if (GerenciadorArquivos::arquivoExiste(arquivoDados)) {
        vector<AreaVerde> dados_iniciais = GerenciadorArquivos::lerTodas(arquivoDados);
        for (const auto& area : dados_iniciais) {
            rtree.inserir(area);
            
            Retangulo r = area.getRetangulo();
            int cx = r.inferiorEsquerdo.x + (r.largura() / 2);
            int cy = r.inferiorEsquerdo.y + (r.altura() / 2);
            quadtree.inserir(Ponto(cx, cy));
            
            if (area.getId() >= idCounter) {
                idCounter = area.getId() + 1;
            }
        }
        cout << "[+] " << dados_iniciais.size() << " areas carregadas do disco com sucesso!\n";
    } else {
        cout << "[-] Nenhum arquivo de dados encontrado. Iniciando base zerada.\n";
    }

    while (opcao != 9) {
        exibirMenu();
        cin >> opcao;

        switch (opcao) {
            case 1: {
                int x, y, l, a;
                string nome, tipo;
                cout << "Coordenadas (X Y Larg Alt) separadas por espaco: ";
                cin >> x >> y >> l >> a;
                cout << "Nome da Area: "; cin >> ws; getline(cin, nome);
                cout << "Tipo de Vegetacao (Grama, Bosque, etc): "; getline(cin, tipo);
                
                Retangulo ret(Ponto(x, y), Ponto(x + l, y + a));
                AreaVerde novaArea(idCounter++, nome, ret, tipo);
                
                rtree.inserir(novaArea);
                
                quadtree.inserir(Ponto(x + (l/2), y + (a/2)));
                
                // Salvando permanentemente no arquivo
                GerenciadorArquivos::gravarArea(arquivoDados, novaArea, true);
                
                cout << "[!] Sucesso! Area salva em memoria e no disco.\n";
                break;
            }
            case 2: {
                int x, y, l, a;
                cout << "Regiao de Busca (X Y Larg Alt): ";
                cin >> x >> y >> l >> a;
                
                Retangulo busca(Ponto(x, y), Ponto(x + l, y + a));
                vector<AreaVerde> res = motor.executarBuscaPorRegiao(busca);
                
                for (const auto& area : res) {
                    cout << "ID: " << area.getId() << " | " << area.getNome() << "\n";
                }
                break;
            }
            case 3: {
                double x, y;
                cout << "Ponto de Origem (X Y): "; cin >> x >> y;
                motor.executarBuscaMaisProximo(x, y);
                break;
            }
            case 4: {
                string tipo;
                cout << "Tipo de vegetacao desejada: "; cin >> ws; getline(cin, tipo);
                vector<AreaVerde> res = motor.executarBuscaPorDensidade(tipo);
                for (const auto& area : res) {
                    cout << "ID: " << area.getId() << " | " << area.getNome() << "\n";
                }
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
                for (const auto& area : res) {
                    cout << "ID: " << area.getId() << " | " << area.getNome() << "\n";
                }
                break;
            }
            case 8: {
                VisualizadorSVG::exportar("resultados/mapa_greenscan.svg", quadtree);
                cout << "[!] SVG gerado na pasta resultados/.\n";
                break;
            }
            case 9:
                cout << "Encerrando o sistema. Ate logo!\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    }

    exemplo_resultado_QuadTree();
    
    return 0;
}