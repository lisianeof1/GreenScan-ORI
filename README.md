# GreenScan 🌱

**Disciplina:** Organização e Recuperação da Informação (ORI)
**Equipe:** 
* Kamila de Freitas Alves
* Letícia Viggiani Moura
* Lisiane de Oliveira Ferreira

---

## 📌 Sobre o Projeto
O **GreenScan** é um protótipo desenvolvido em C++ focado na organização, armazenamento e recuperação eficiente de dados espaciais. O sistema trabalha sobre um mapa cartesiano 2D simulado (1000x1000 unidades) que representa áreas verdes de São Carlos.

O objetivo central é implementar do zero e comparar o uso de duas estruturas de dados avançadas para memória secundária:
1. **QuadTree:** Para particionamento hierárquico do espaço do mapa.
2. **R-Tree:** Para indexação e agrupamento dos polígonos (Minimum Bounding Rectangles - MBR) das áreas verdes.

---

## ⚙️ Funcionalidades e Consultas
O sistema realiza a leitura de arquivos de texto simulando armazenamento externo e responde às seguintes consultas espaciais:
1. Busca por região (quais áreas estão dentro de um retângulo).
2. Busca pelo vizinho mais próximo a um ponto (Nearest Neighbor).
3. Busca por densidade (alta/média/baixa).
4. Contagem de áreas por quadrante.
5. Detecção de sobreposição entre áreas.
6. Busca por raio circular a partir de um ponto.

A visualização do particionamento espacial será exportada para o formato vetorial SVG.

---

## 👩‍💻 Divisão de Tarefas

O projeto foi arquitetado em módulos para facilitar o desenvolvimento paralelo:

**1. Kamila (Módulo Core e Armazenamento)**
* **Responsabilidade:** Criar a estrutura básica e a simulação do banco de dados em arquivo.
* **Arquivos principais:** `Ponto.h`, `Retangulo.h`, `AreaVerde.h/cpp` e `GerenciadorArquivos.h/cpp`.
* **Foco:** Gerar aleatoriamente as áreas verdes, gravá-las no arquivo delimitado (`;`) e implementar o leitor sequencial.

**2. Letícia (Módulo QuadTree e Visualização)**
* **Responsabilidade:** Particionamento do espaço e saída gráfica.
* **Arquivos principais:** `QuadTree.h/cpp` e `VisualizadorSVG.h/cpp`.
* **Foco:** Implementar a lógica de divisão em 4 quadrantes da QuadTree e exportar o resultado final e os *bounding boxes* para um arquivo `.svg`.

**3. Lisiane (Módulo R-Tree, Motor de Consultas e Main)**
* **Responsabilidade:** Indexação de objetos, regras de busca e integração.
* **Arquivos principais:** `RTree.h/cpp`, `MotorConsultas.h/cpp` e `main.cpp`.
* **Foco:** Implementar a R-Tree para os polígonos, amarrar as 6 consultas obrigatórias no Motor e criar o menu interativo via terminal executando os módulos da equipe.

---

## 🚀 Como Contribuir (Fluxo Git)
Para manter o repositório organizado e evitar conflitos de código, seguiremos este fluxo:

1. **Atualize seu repositório local:**
   Antes de começar a programar no dia, baixe as alterações mais recentes:
   `git pull origin main`

2. **Programe nos seus arquivos:**
   Trabalhe apenas nos `.cpp` e `.h` que estão sob a sua responsabilidade listada acima.

3. **Salve e suba suas alterações:**
   `git add .`
   `git commit -m "Descricao clara do que voce fez"`
   `git push origin main`

*Atenção: A integração final será feita pela Lisiane no arquivo `main.cpp`. Se precisarem alterar um arquivo que não seja o seu, comuniquem a equipe primeiro!*

###Anotações: o que preciso fazer (Lisi)
- apagar main.cpp da leticia, antes colocar o conteudo na main ja existente
- colocar todos os codigos da leticia no lugar certo se ela n colocar
- acrescentar tudo na main original
- consultas
