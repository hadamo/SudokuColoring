/*
Teoria dos Grafos 2019-1 - Trabalho Pratico
Hadamo da Silva Egito
Maiana Rodrigues Gonçalves
*/
#include "grafo.h"
#include <string.h>
//estrutura que guarda elementos do
//sudoku dado como entrada
typedef struct tab
{
	int pos, val;
}Tabela;
//funcao que inicia grafo com o sudoku de entrada
Grafo* iniciaGrafo(char *entrada,int grafoSize);
//funcao que imprime o sudoku na tela
void desenhaSudoku(Grafo *g);
//funcao que colora os grafos
int coloreGrafo(Grafo *g,int i);
//funcao que verifica se a coloracao esta correta
int verificaResposta(Grafo *g);
//funcao que verifica se entrada eh aceitavel
int verificaEntrada(Grafo *g);


int main(int *argc, char *argv[])
{
	//trata arquivo de entrada
    char entrada[25];
    strcpy(entrada , argv[1]);
    //inicia grafo
	Grafo *grafo;
	grafo= iniciaGrafo(entrada,81);
	//desenhaSudoku(grafo);
	if(!verificaEntrada(grafo)) return 0;
	//realiza colaração, verificação e visualização de resultados
	 imprimeGrafo(grafo);
	coloreGrafo(grafo,0);
	//desenhaSudoku(grafo);
	//int x = verificaResposta(grafo);

}

int verificaEntrada(Grafo *g)
{
	for(int i = 0; i < g->v ; i++)
	{
		int cor = g->adj[i].cor; 
		if( cor < 0 || cor > 9 )
		{
			printf("Valor Nao Aceitavel em %d!\n",i);
			return 0;
		} 
		Vertice *w = g->adj[i].prox;
		while(w != NULL )
		{
			int adjcor = g->adj[w->val].cor;
			if(cor == adjcor && cor > 0)
			{
				printf("%d tem adj %d com mesma cor %d, Entrada Invalida!!\n",i,w->val,adjcor);
				return 0;			
			}
			w = w->prox;
		} 
	}
	printf("Entrada Aceitavel!\n");
	return 1;
}
//verifica se algum vertice ficou sem coloracao
//ou algum adjacente possui cor igual
int verificaResposta(Grafo *g)
{
	for(int i = 0; i < g->v ; i++)
	{
		if( !temCor(g,i) )
		{
			printf("Vertice %d sem cor, Resposta Errada!\n",i);
			return 0;
		} 
		Vertice *w = g->adj[i].prox;
		int cor = g->adj[i].cor; 
		while(w != NULL )
		{
			int adjcor = g->adj[w->val].cor;
			if(cor == adjcor)
			{
				printf("%d tem adj %d com mesma cor %d, Resposta Errada!!\n",i,w->val,adjcor);
				return 0;			
			}
			w = w->prox;
		} 
	}
	printf("Correto!\n");
	return 1;
}

int coloreGrafo(Grafo *g, int i)
{
	//se ainda nao verificou todos os vertices
	if(i < g -> v) 
	{
		//se for vertice iniciado na entrada, i.e, fixo, passa pro proximo
		if( ehFixo(g,i) )
		{
			if(coloreGrafo(g,i+1)) return 1;
			//se o proximo nao puder ser colorido volta pro anterior
			//do atual pois ele eh fixo
			return 0;
		}
		//se nao tiver cor procura a cor disponivel
		for(int cor = 1 ; cor <= 9; cor++)
		{
			//se nenhum adjacente tiver a cor 
			//usa a cor
			if(!buscaCorAdj(g,i,cor))
			{
				setCorVertice(g,i,cor);
				//busca o proximo vertice
				//retorna 1 quando a busca chegar ao ultimo vertice
				//para que a coloração termine.
				if(coloreGrafo(g,i+1)) return 1;
				//caso nao consiga solucaoo com as cores atuais
				//descolore o vertice novamente e verifica proxima cor
				//eh preciso descolorir para nao dar problema na busca nos adjacentes
				//ja que esta refazendo escolha de cor
				setCorVertice(g,i,0);
			}
		}
		//caso atual nao tenha cor, e nao conseguir colorir-lo
		//deve-se alterar a cor do vertice anterior
		return 0;
	}
	//se ja chegou no ultimo vertice, retorna 1 para indicar 
	//que acabou a busca e que deve voltar na arvore de busca
	return 1;
}

Grafo* iniciaGrafo(char *entrada, int grafoSize)
{
	FILE *sudoku = fopen(entrada, "r");
	Tabela M[9][9];
	int i , j , k , x=0, scan;
	Grafo *grafo = criaGrafo(grafoSize);
	for(i=0; i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			scan = fscanf(sudoku, "%d", &M[i][j].val);

			M[i][j].pos = x++;
			//printf(" %d (%d)",M[i][j].pos, M[i][j].val);
		}
	}
	fclose(sudoku);
	//cria adjascencias para coluna inteira e linha inteira
	for(i = 0; i < 9; i++ )
		for (j = 0; j < 9; j++)
		{
			//insere todos os elementos depois do atual na linha e coluna como adjacentes
			//não eh preciso repetir o anterior pois ja possui adjacencia com ele
			for( k = i+1; k < 9 ; k++)
				insereAresta(grafo , M[ i ][ j ].pos, M[ i ][ j ].val , M[ k ][ j ].pos , M[ k ][ j ].val );
			for( k = j+1; k < 9 ; k++)
				insereAresta(grafo , M[ i ][ j ].pos, M[ i ][ j ].val , M[ i ][ k ].pos , M[ i ][ k ].val );
			//printf("\n");
		}

	//cria adjascencias restantes para cada vertice em um
	//mesmo quadrante para cada um dos 9 quadrantes
	for(i =0 ; i < 7; i += 3)
		for( j = 0 ; j < 7 ; j += 3)
		{
			//celula superior esquerda
			insereAresta(grafo , M[ i ][ j ].pos , M[ i ][ j ].val ,  M[ i+1 ][ j+1 ].pos , M[ i+1 ][ j+1 ].val );
			insereAresta(grafo , M[ i ][ j ].pos , M[ i ][ j ].val , M[i+1 ][ j+2 ].pos , M[i+1 ][ j+2 ].val );
			insereAresta(grafo , M[ i ][ j ].pos , M[ i ][ j ].val , M[ i+2 ][ j+1 ].pos , M[ i+2 ][ j+1 ].val );
			insereAresta(grafo , M[ i ][ j ].pos , M[ i ][ j ].val , M[ i+2 ][ j+2 ].pos , M[ i+2 ][ j+2 ].val );
			
			//celula superior
			insereAresta(grafo , M[ i ][ j+1 ].pos , M[ i ][ j+1 ].val , M[ i+1][ j ].pos , M[ i+1][ j ].val );
			insereAresta(grafo , M[ i ][ j+1 ].pos , M[ i ][ j+1 ].val , M[i+1 ][ j+2 ].pos , M[i+1 ][ j+2 ].val);
			insereAresta(grafo , M[ i ][ j+1 ].pos , M[ i ][ j+1 ].val , M[ i+2][ j ].pos , M[ i+2][ j ].val );
			insereAresta(grafo , M[ i ][ j+1 ].pos , M[ i ][ j+1 ].val , M[ i+2 ][ j+2 ].pos , M[ i+2 ][ j+2 ].val );

			//celula superior direita
			insereAresta(grafo , M[ i ][ j+2 ].pos , M[ i ][ j+2 ].val , M[ i+1][ j ].pos , M[ i+1][ j ].val );
			insereAresta(grafo , M[ i ][ j+2 ].pos , M[ i ][ j+2 ].val , M[ i+1 ][ j+1 ].pos , M[ i+1 ][ j+1 ].val );
			insereAresta(grafo , M[ i ][ j+2 ].pos , M[ i ][ j+2 ].val , M[ i+2][ j ].pos , M[ i+2][ j ].val );
			insereAresta(grafo , M[ i ][ j+2 ].pos , M[ i ][ j+2 ].val , M[ i+2 ][ j+1 ].pos , M[ i+2 ][ j+1 ].val );

			//celula esquerda
			insereAresta(grafo , M[ i+1][ j ].pos , M[ i+1][ j ].val , M[ i+2 ][ j+1 ].pos , M[ i+2 ][ j+1 ].val );
			insereAresta(grafo , M[ i+1][ j ].pos , M[ i+1][ j ].val , M[ i+2 ][ j+2 ].pos ,  M[ i+2 ][ j+2 ].val );

			//celula central
			insereAresta(grafo , M[ i+1 ][ j+1 ].pos , M[ i+1 ][ j+1 ].val , M[ i+2][ j ].pos , M[ i+2][ j ].val );
			insereAresta(grafo , M[ i+1 ][ j+1 ].pos , M[ i+1 ][ j+1 ].val , M[ i+2 ][ j+2 ].pos ,M[ i+2 ][ j+2 ].val );

			//celula direita
			insereAresta(grafo , M[i+1 ][ j+2 ].pos , M[i+1 ][ j+2 ].val , M[ i+2][ j ].pos , M[ i+2][ j ].val );
			insereAresta(grafo , M[i+1 ][ j+2 ].pos , M[i+1 ][ j+2 ].val , M[ i+2 ][ j+1 ].pos , M[ i+2 ][ j+1 ].val );
		}
	return grafo;
}

void desenhaSudoku(Grafo *g)
{
	int i,j,k,m,x;
	j=8;
	k=0;
	m=0;
	printf("   ");
	for ( i = 0; i < 9; ++i)
	{
		printf( "   %d",i);
		m++;
		if(m%3==0)
		{
			printf(" ");
		}
	}
	m=0;
	printf("\n %d ||",k++);
	for(i=0 ; i < g->v ; ++i)
	{
		x = g->adj[i].cor;
		printf(" ");
		printf("%d",g->adj[i].cor);
		m++;
		printf(" |");
		if(m % 3 == 0)
		{
			printf("|");
		}
		if(i==j)
		{
			printf("\n");
			if(k<9) printf(" %d ||",k++ );
			j+=9;
		}
	}
}
