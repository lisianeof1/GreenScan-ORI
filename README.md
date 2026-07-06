# GreenScan - Sistema de Consulta Espacial de Áreas Verdes

O GreenScan é um sistema de indexação e consulta espacial desenvolvido para o gerenciamento de áreas verdes. Este projeto foi construído para a disciplina ministrada pelo professor Roberto Ferrari na Universidade Federal de São Carlos (UFSCar). 

O sistema implementa estruturas de dados espaciais avançadas (**R-Tree** e **QuadTree**) para garantir extrema eficiência em buscas bidimensionais, além de persistência de dados em disco e exportação visual do particionamento espacial.

---

## Equipe de Desenvolvimento
* **Lisiane:** Motor de Consultas e Integração, Implementação da R-Tree, Lógica de Consultas Espaciais e Menu Principal.
* **Letícia:** Implementação da QuadTree, Lógica de Particionamento e Visualizador/Exportador de mapas SVG.
* **Kamila:** Estruturas Base (Core) e Módulo de Armazenamento/Serialização (Persistência em arquivo `.txt`).

---

## Funcionalidades (Motor de Consultas)

O coração do sistema atende a **6 consultas espaciais obrigatórias**:

1. **Busca por Região (R-Tree):** Retorna todas as áreas verdes contidas dentro de uma janela (bounding box) de busca.
2. **Vizinho Mais Próximo (R-Tree):** Calcula a distância euclidiana e encontra a área verde mais próxima de um ponto `(X, Y)` fornecido.
3. **Filtro por Tipo de Vegetação (R-Tree):** Varredura indexada para retornar áreas verdes filtradas por características (ex: Grama, Bosque).
4. **Contagem por Quadrante (QuadTree):** Navegação recursiva na QuadTree para exibir a quantidade de áreas agrupadas por região do mapa.
5. **Análise de Sobreposição (R-Tree):** Identificação de conflitos espaciais onde duas ou mais áreas verdes se cruzam.
6. **Busca Radial (R-Tree):** Retorna as áreas que estão dentro de um raio de distância específico a partir de um ponto central.

**Recursos Extras:**
* **Armazenamento Persistente:** Os dados inseridos em memória são gravados e lidos automaticamente do arquivo `areas_verdes.txt`, utilizando serialização separada por ponto e vírgula (`;`).
* **Exportação Visual:** Geração automática do arquivo `mapa_greenscan.svg`, permitindo a visualização gráfica da QuadTree e dos pontos no navegador de internet.

---

## Estrutura do Projeto

O código-fonte segue uma arquitetura modular dividida por responsabilidades:

```text
GreenScan/
├── areas_verdes.txt            # Arquivo de banco de dados (gerado automaticamente)
├── resultados/                 # Pasta destino para os arquivos exportados
│   └── mapa_greenscan.svg      # Exportação visual do mapa
└── src/
    ├── armazenamento/          # Leitura, gravação e persistência de dados
    │   └── GerenciadorArquivos.h / .cpp
    ├── consultas/              # Centralização e regras de negócio das 6 queries
    │   └── MotorConsultas.h / .cpp
    ├── core/                   # Estruturas de dados primitivas do domínio
    │   ├── AreaVerde.h / .cpp
    │   ├── Ponto.h
    │   └── Retangulo.h
    ├── indexacao/              # Estruturas de dados avançadas
    │   ├── QuadTree.h / .cpp
    │   └── RTree.h / .cpp
    ├── visualizacao/           # Módulo de exportação gráfica
    │   └── VisualizadorSVG.h / .cpp
    └── main.cpp                # Ponto de entrada e Menu CLI
