#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_VERTICES 1000
#define MAX_QUEUE_SIZE 1000

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

typedef int element;
typedef struct QueueType {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void init(GraphType*);
void insert_vertex(GraphType*, int);
void insert_edge(GraphType*, int, int);

void init_queue(QueueType*);
int is_full(QueueType*);
int is_empty(QueueType*);
void enqueue(QueueType*, element);
element dequeue(QueueType*);

void dfs(GraphType*, int);
void bfs(GraphType*, int);

bool* visited;
int* result;
int cnt = 0;

int main() {

	int N, M, R; //정점의 수 N, 간선의 수 M, 탐색 시작점 V
	scanf("%d %d %d", &N, &M, &R);

	visited = (bool*)malloc(sizeof(bool) * N);
	memset(visited, false, sizeof(bool) * N);
	result = (int*)malloc(sizeof(int) * (N + 1));
	memset(result, 0, sizeof(int) * (N + 1));

	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	for (int i = 0; i < N; i++)
		insert_vertex(g, i);

	int u, v;
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		insert_edge(g, u-1, v-1);
	}

	dfs(g, R-1);

	for (int i = 0; i < cnt; i++)
		printf("%d ", result[i]);
	printf("\n");

	memset(visited, false, sizeof(bool) * N); //visited 초기화

	bfs(g, R-1);

	for (int i = 0; i < cnt; i++)
		printf("%d ", result[i]);

}

void dfs(GraphType* g, int a) {
	visited[a] = true;
	result[cnt] = a+1;
	cnt++;

	for (int i = 0; i < g->n; i++) {
		if(g->adj_mat[a][i] && !visited[i])
			dfs(g, i);
	}
}

void bfs(GraphType* g, int R) {
	QueueType q;
	init_queue(&q);
	cnt = 0;

	result[cnt] = R+1;
	cnt++;
	visited[R] = true;
	enqueue(&q, R);

	while (!is_empty(&q)) {
		int a = dequeue(&q);
		for (int i = 0; i < g->n; i++) {
			if (g->adj_mat[a][i] && !visited[i]) {
				visited[i] = true;
				enqueue(&q, i);
				result[cnt] = i+1;
				cnt++;
			}
		}
	}
}

void init(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
	}
}

void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES)
		return;
	g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n)
		return;
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}


void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		return;
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	return;
}

element dequeue(QueueType* q) {
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}