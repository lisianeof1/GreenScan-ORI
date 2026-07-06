#ifndef AREAVERDE_H
#define AREAVERDE_H

#include <string>
#include "Retangulo.h"

/**
 * Representa uma area verde: um espaco delimitado por um retangulo,
 * com identificador, nome e tipo de vegetacao predominante.
 */
class AreaVerde {
private:
    int id;
    std::string nome;
    Retangulo retangulo;
    std::string tipoVegetacao;

public:
    AreaVerde();
    AreaVerde(int id, const std::string& nome, const Retangulo& retangulo,
               const std::string& tipoVegetacao);

    // Getters
    int getId() const;
    std::string getNome() const;
    Retangulo getRetangulo() const;
    std::string getTipoVegetacao() const;

    // Setters
    void setId(int id);
    void setNome(const std::string& nome);
    void setRetangulo(const Retangulo& retangulo);
    void setTipoVegetacao(const std::string& tipoVegetacao);

    // Serializacao: converte o registro para uma linha delimitada por ';'
    // Formato: id;nome;x1;y1;x2;y2;tipoVegetacao
    std::string serializar() const;

    // Desserializacao: cria um AreaVerde a partir de uma linha delimitada por ';'
    static AreaVerde desserializar(const std::string& linha);

    // Exibe os dados da area verde no console
    void exibir() const;
};

#endif // AREAVERDE_H
