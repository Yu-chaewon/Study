#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100001
#define INF 1000001

int parent[MAX];
void set_init(int);
int set_find(int);
void set_union(int, int);

struct Edge {
	int start, end, weight;
};

typedef struct GraphType {
	int n;
	struct Edge edges[MAX];
} GraphType;

void graph_init(GraphType*);
void insert_edge(GraphType*, int, int, int);

int kruskal(GraphType*, int, int);

int main() {
	int V, E; //정점의 개수 V, 간선의 개수 E
	scanf("%d %d", &V, &E);

	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	int A, B, C;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &A, &B, &C);
		insert_edge(g, A - 1, B - 1, C);
	}

	printf("%d", kruskal(g, V, E));
}

void set_init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int curr) {
	if (parent[curr] == -1)
		return curr;
	else
		return parent[curr] = set_find(parent[curr]);
}

void set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);
	if(root1 != root2)
		parent[root1] = root2;
}

void graph_init(GraphType* g) {
	g->n = 0;
	g->edges[0].start = 0;
	g->edges[0].end = 0;
	g->edges[0].weight = INF;
}

void insert_edge(GraphType* g, int start, int end, int w) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

int compare(const void* a, const void* b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return(x->weight - y->weight);
}

int kruskal(GraphType* g, int V, int E) {
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;
	int MST_Weight = 0;

	set_init(g->n);
	qsort(g->edges, g->n, sizeof(struct Edge), compare);
	
	if (E <= 1) {
		e = g->edges[0];
		return e.weight;
	}

	int i = 0;
	while (edge_accepted < V - 1) {
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			edge_accepted++;
			set_union(uset, vset);
			MST_Weight += e.weight;
		}
		i++;
	}
	return MST_Weight;
}