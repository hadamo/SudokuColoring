# SudokuColoring
 
- Solução de puzzle Sudoku 9x9 com cores 1,2,..,9 utilizando algoritmo para coloração minima de grafos com backtracking e indice cromático 9.
- Sudoku: Matriz 9x9 com 81 células, cada uma enumerada de 1 a 9 sendo que nenhuma célula na mesma linha, coluna e quadrante podem ter números iguais.
- Modelagem: Cada uma das 81 células do sudoku é um vértice, cada célula é adjacente a todas as celulas na mesma linha, na mesma coluna e no mesmo quadrante, totalizando 81 vértices e 810 arestas.
- Coloração: A coloração de vértices é um problema em que dado grafo G=(V,E) vértices recebem uma cor tal que quais quer vértices v e w contidos em V, não podem receber a mesma cor caso sejam adjacentes. 
- Solução: Algoritmo backtracking que verifica todos os vertices sequencialmente, colorindo com a primeira cor disponível para aquele vértice considerando as invariantes do problema, caso não seja possível colorir um vértice com nenhuma cor, o algoritmo volta para o vértice anterior e colore com a próxima cor disponível e repetindo este processo até que o grafo esteja completamente colorido, assim solucionando o Sudoku. O algoritmo ainda aceita sudokus de entrada com valores previamente fixos, neste caso alguns vértices começam já coloridos e esta cor não pode ser alterada.
