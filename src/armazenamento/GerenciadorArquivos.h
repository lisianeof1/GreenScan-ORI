#ifndef GERENCIADORARQUIVOS_H
#define GERENCIADORARQUIVOS_H

#include <string>
#include <vector>
#include "AreaVerde.h"

/**
 * Responsavel por simular o "banco de dados em arquivo":
 * gera areas verdes aleatoriamente, grava-as em arquivo texto
 * delimitado por ';' e le os registros de forma sequencial.
 */
class GerenciadorArquivos {
public:
    // Gera 'quantidade' areas verdes aleatorias e grava no arquivo
    // (sobrescreve o arquivo, criando a base do zero).
    static void gerarAreasAleatorias(const std::string& nomeArquivo,
                                      int quantidade,
                                      int larguraMaxima = 1000,
                                      int alturaMaxima = 1000);

    // Grava uma unica AreaVerde no arquivo. Se anexar = true, adiciona
    // ao final do arquivo; caso contrario, sobrescreve o conteudo.
    static bool gravarArea(const std::string& nomeArquivo,
                            const AreaVerde& area,
                            bool anexar = true);

    // Le todos os registros do arquivo de uma so vez e retorna em um vetor.
    static std::vector<AreaVerde> lerTodas(const std::string& nomeArquivo);

    // Leitor sequencial: percorre o arquivo registro a registro (linha a
    // linha), exibindo cada AreaVerde encontrada. Simula o acesso
    // sequencial tradicional a um arquivo de dados.
    static bool leitorSequencial(const std::string& nomeArquivo);

    // Verifica se o arquivo existe e pode ser aberto para leitura.
    static bool arquivoExiste(const std::string& nomeArquivo);

private:
    static std::string gerarTipoVegetacaoAleatorio();
    static std::string gerarNomeAleatorio(int indice);
};

#endif // GERENCIADORARQUIVOS_H
