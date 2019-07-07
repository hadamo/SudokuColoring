#include <stdlib.h>
#include <stdio.h>
/*
Teoria dos Grafos 2019-1 - Trabalho Pratico
Hadamo da Silva Egito
Maiana Rodrigues Gonçalves
*/
#ifndef GRAFO_H
#define GRAFO_H

/*
	Autor: Hadamo Egito
*/
//estrutura de no para vertices
typedef struct vertice
{
	//val = numero da celula do sudoku representada pelo vertice
	//cor = cor alocada ao vertice, de 0 a 9, sendo 0 = incolor
	int val,
		cor,
		fixo;
	struct vertice *prox;
}Vertice;
//estrutura do grafo com num de vertices e arestas,lista de adj
//e vetor que contabiliza o uso de cada cor de 0 a 9, sendo 0 = incolor
typedef struct grafo
{
	int v,e;
	int *usoCores;
	Vertice *adj;
}Grafo;

//funcao que cria grafo com x vertices
Grafo* criaGrafo(int);
//funcao que cria instancia de estrutura vertice
Vertice* novoVertice(int v);
//funcao que insere aresta simples nao valorada em grafo dados vertices
//das extremidades
void insereAresta(Grafo*, int, int, int, int);
//funcao que imprime o grafo
void imprimeGrafo(Grafo*);
//busca por cor em adjacencias, se existe vertice adjacente
//com a cor retorna num do adj caso contrario retorna 0;
int buscaCorAdj(Grafo *g, int vert, int cor);
//verifica se vertice selecionado ja possui cor
//se true : 1  false : 0
int temCor(Grafo *g, int vert);
//seta cor do vertice
void setCorVertice(Grafo *g, int vert, int cor);
// funcao que verifica se o vertice eh fixo
//ou seja eh vertice ja colorido na entrada
//1 true 0 false
int ehFixo(Grafo *g, int vert);
#endif