#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#define MAX_QUEUE_SIZE 1000

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void init_queue(QueueType*);
int is_full(QueueType*);
int is_empty(QueueType*);
void enqueue(QueueType*, element);
element dequeue(QueueType*);


TreeNode* createTree(int height) {
	if (height < 0)
		return NULL;

	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->data = 0;
	node->left = NULL;
	node->right = NULL;

	if (height > 0) {
		node->left = createTree(height - 1);
		node->right = createTree(height - 1);
	}

	return node;
}

void Inorder(TreeNode* root) {
	if (root == NULL)
		return;
	Inorder(root->left);
	int data;
	scanf("%d", &data);
	root->data = data;
	Inorder(root->right);
}

void LevelOrder(TreeNode* root) {
	QueueType q;
	init_queue(&q);

	enqueue(&q, root);
	int i = 0, d = 0;
	while (!is_empty(&q)) {
		root = dequeue(&q);
		printf("%d ", root->data);
		if (root->left)
			enqueue(&q, root->left);
		if (root->right)
			enqueue(&q, root->right);
		i++;
		if (i == pow(2, d)) {
			printf("\n");
			i = 0;
			d++;
		}

	}
}

int main() {
	int h;
	scanf("%d", &h);

	TreeNode* root;
	root = createTree(h - 1);

	Inorder(root);

	LevelOrder(root);
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