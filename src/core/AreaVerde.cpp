#include "AreaVerde.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

AreaVerde::AreaVerde()
    : id(0), nome(""), retangulo(), tipoVegetacao("") {}

AreaVerde::AreaVerde(int id, const std::string& nome, const Retangulo& retangulo,
                       const std::string& tipoVegetacao)
    : id(id), nome(nome), retangulo(retangulo), tipoVegetacao(tipoVegetacao) {}

int AreaVerde::getId() const { return id; }
std::string AreaVerde::getNome() const { return nome; }
Retangulo AreaVerde::getRetangulo() const { return retangulo; }
std::string AreaVerde::getTipoVegetacao() const { return tipoVegetacao; }

void AreaVerde::setId(int id) { this->id = id; }
void AreaVerde::setNome(const std::string& nome) { this->nome = nome; }
void AreaVerde::setRetangulo(const Retangulo& retangulo) { this->retangulo = retangulo; }
void AreaVerde::setTipoVegetacao(const std::string& tipoVegetacao) {
    this->tipoVegetacao = tipoVegetacao;
}

std::string AreaVerde::serializar() const {
    std::ostringstream oss;
    oss << id << ';'
        << nome << ';'
        << retangulo.inferiorEsquerdo.x << ';'
        << retangulo.inferiorEsquerdo.y << ';'
        << retangulo.superiorDireito.x << ';'
        << retangulo.superiorDireito.y << ';'
        << tipoVegetacao;
    return oss.str();
}

AreaVerde AreaVerde::desserializar(const std::string& linha) {
    std::stringstream ss(linha);
    std::string campo;
    std::string campos[7];
    int i = 0;

    while (std::getline(ss, campo, ';')) {
        if (i >= 7) {
            throw std::runtime_error("Linha com formato invalido: " + linha);
        }
        campos[i++] = campo;
    }

    if (i != 7) {
        throw std::runtime_error("Linha com numero de campos invalido: " + linha);
    }

    int id = std::stoi(campos[0]);
    std::string nome = campos[1];
    int x1 = std::stoi(campos[2]);
    int y1 = std::stoi(campos[3]);
    int x2 = std::stoi(campos[4]);
    int y2 = std::stoi(campos[5]);
    std::string tipoVegetacao = campos[6];

    Retangulo retangulo(Ponto(x1, y1), Ponto(x2, y2));
    return AreaVerde(id, nome, retangulo, tipoVegetacao);
}

void AreaVerde::exibir() const {
    std::cout << "ID: " << id
              << " | Nome: " << nome
              << " | Retangulo: (" << retangulo.inferiorEsquerdo.x << ", "
              << retangulo.inferiorEsquerdo.y << ") -> ("
              << retangulo.superiorDireito.x << ", "
              << retangulo.superiorDireito.y << ")"
              << " | Area: " << retangulo.area()
              << " | Vegetacao: " << tipoVegetacao
              << std::endl;
}

