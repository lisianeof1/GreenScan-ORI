#include "GerenciadorArquivos.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace {
    const std::string TIPOS_VEGETACAO[] = {
        "Grama", "Arvores nativas", "Jardim floral", "Bosque",
        "Mata ciliar", "Area de reflorestamento", "Horta comunitaria"
    };
    const int QTD_TIPOS = 7;
}

std::string GerenciadorArquivos::gerarTipoVegetacaoAleatorio() {
    int indice = std::rand() % QTD_TIPOS;
    return TIPOS_VEGETACAO[indice];
}

std::string GerenciadorArquivos::gerarNomeAleatorio(int indice) {
    return "AreaVerde_" + std::to_string(indice);
}

void GerenciadorArquivos::gerarAreasAleatorias(const std::string& nomeArquivo,
                                                int quantidade,
                                                int larguraMaxima,
                                                int alturaMaxima) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Sobrescreve o arquivo para comecar a "base de dados" do zero.
    std::ofstream arquivo(nomeArquivo, std::ios::out | std::ios::trunc);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao criar/abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    for (int i = 1; i <= quantidade; ++i) {
        int x1 = std::rand() % larguraMaxima;
        int y1 = std::rand() % alturaMaxima;
        int largura = 1 + std::rand() % (larguraMaxima / 10 + 1);
        int altura = 1 + std::rand() % (alturaMaxima / 10 + 1);

        int x2 = x1 + largura;
        int y2 = y1 + altura;

        Retangulo retangulo(Ponto(x1, y1), Ponto(x2, y2));
        AreaVerde area(i, gerarNomeAleatorio(i), retangulo, gerarTipoVegetacaoAleatorio());

        arquivo << area.serializar() << '\n';
    }

    arquivo.close();
    std::cout << quantidade << " areas verdes geradas e gravadas em '"
              << nomeArquivo << "'." << std::endl;
}

bool GerenciadorArquivos::gravarArea(const std::string& nomeArquivo,
                                      const AreaVerde& area,
                                      bool anexar) {
    std::ios_base::openmode modo = std::ios::out;
    modo |= anexar ? std::ios::app : std::ios::trunc;

    std::ofstream arquivo(nomeArquivo, modo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para gravacao: " << nomeArquivo << std::endl;
        return false;
    }

    arquivo << area.serializar() << '\n';
    arquivo.close();
    return true;
}

std::vector<AreaVerde> GerenciadorArquivos::lerTodas(const std::string& nomeArquivo) {
    std::vector<AreaVerde> areas;
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para leitura: " << nomeArquivo << std::endl;
        return areas;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;
        try {
            areas.push_back(AreaVerde::desserializar(linha));
        } catch (const std::exception& e) {
            std::cerr << "Registro invalido ignorado: " << e.what() << std::endl;
        }
    }

    arquivo.close();
    return areas;
}

bool GerenciadorArquivos::leitorSequencial(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para leitura sequencial: "
                  << nomeArquivo << std::endl;
        return false;
    }

    std::cout << "--- Leitura sequencial de '" << nomeArquivo << "' ---" << std::endl;

    std::string linha;
    int contador = 0;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;
        try {
            AreaVerde area = AreaVerde::desserializar(linha);
            area.exibir();
            ++contador;
        } catch (const std::exception& e) {
            std::cerr << "Registro invalido ignorado: " << e.what() << std::endl;
        }
    }

    arquivo.close();
    std::cout << "--- Fim da leitura. " << contador << " registro(s) lido(s). ---"
              << std::endl;
    return true;
}

bool GerenciadorArquivos::arquivoExiste(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    return arquivo.good();
}
