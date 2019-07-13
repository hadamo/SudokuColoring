/*
Teoria dos Grafos 2019-1 - Trabalho Pratico
Hadamo da Silva Egito
Maiana Rodrigues
*/
#include "grafo.h"
//função para criar grafo, dado numero de vertices v
Grafo* criaGrafo(int v)
{
	Grafo *g = (Grafo*) calloc(v,sizeof(Grafo));
	if (g!=NULL)
	{
		g->v  = v;
		// g->e = 0;
		g->usoCores = (int*)calloc(10,sizeof(int));
		g->adj = (Vertice*)calloc(v,sizeof(Vertice));
		for (int i = 0; i <v; ++i)
		{
			g->adj[i].prox = NULL;
		}
	}
	return g;
}
//função para criar Vertice dado valor do Vertice v e sua cor
Vertice* novoVertice(int v)
{
	Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
	if(novo == NULL)
	{
		printf("Algo de errado não está certo, Vertice não criado!\n");
	}else
	{
		novo -> val = v;
	    novo -> fixo = 0;
		novo -> prox = NULL;
	}
	return novo;
}
//função para criar aresta entre dois vertices distintos num grafo
void insereAresta(Grafo *g, int v1,int cor1, int v2, int cor2)
{
	if(v1!=v2)// impede criacao de laço no grafo
	{
		Vertice *p = g->adj[v1].prox;
		while(p!=NULL)
		{
			//verifica se os vertices ja estao ligados
			if(p->val == v2) break; 
			// procura fim da lista
			p = p->prox; 
		}
		/*se terminou de percorrer lista e não achou ocorrencia
		do novo Vertice, insere o Vertice na lista
		*/
		if(p==NULL)
		{
			//insere novo Vertice na adj de v1
			Vertice *novo = novoVertice(v2);
			novo->prox = g->adj[v1].prox;
			g->adj[v1].prox = novo;
			g->adj[v1].cor = cor1;
			if(cor1 > 0) g->adj[v1].fixo++;

			// repete o processo para v2
			novo = novoVertice(v1);
			novo->prox = g->adj[v2].prox;
			g->adj[v2].prox = novo;
			g->adj[v2].cor = cor2;
			if(cor2 > 0) g->adj[v2].fixo++;
			//incrementa quantidade de arestas
			g->e++;
			//marca cores usadas
			g->usoCores[cor1]++;
			g->usoCores[0]--;
			g->usoCores[cor2]++;
			g->usoCores[0]--;

		}
	}
}


void imprimeGrafo(Grafo *g)
{
	if(g!=NULL)
	{
		int i;
		Vertice *w;
		printf("Grafo com %d vertices e %d arestas\n",g -> v, g -> e );
		for(i=0 ; i < g->v ; ++i)
		{
			printf("v%d(%d) -> ",i,g->adj[i].cor);
			w = g -> adj[i].prox;
			while(w != NULL)
			{
				printf("[%d]-",w -> val);
				w = w -> prox;
			}
			printf("¬\n");
		}
	}
}

int buscaCorAdj(Grafo *g, int vert, int cor)
{
	Vertice *w = g->adj[vert].prox;
	while(w != NULL)
	{
		int vAdj = w->val;
		//printf("%d\t",vAdj);
		//nao da problema com 0, pois quando é chamada usa cor >0
		if(g->adj[vAdj].cor == cor)
		{
			//if(vert<3)printf("%d-%d %d|",vert,vAdj,cor);
			return 1;
		} 
		w = w->prox;
	}
	return 0;
}

int temCor(Grafo *g, int vert)
{
	return g->adj[vert].cor > 0 ? 1 : 0;
}

void setCorVertice(Grafo *g, int vert, int cor)
{
	g->adj[vert].cor = cor;
}

int ehFixo(Grafo *g, int vert)
{
	return g->adj[vert].fixo > 0 ? 1 : 0;
}