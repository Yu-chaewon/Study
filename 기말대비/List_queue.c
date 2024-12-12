#include <stdio.h>
#include <memory.h>

//연결 리스트로 구현한 큐
typedef int element;
typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;
typedef struct {
	QueueNode* front, * rear;
} LinkedQueueType;

void enqueue(LinkedQueueType*, element);
element dequeue(LinkedQueueType*);

int main() {
	LinkedQueueType* q = (LinkedQueueType*)malloc(sizeof(LinkedQueueType));
	q->front = NULL;
	q->rear = NULL;
}

void enqueue(LinkedQueueType* q, element val) {
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	node->data = val;
	node->link = NULL;
	q->rear->link = node;
	q->rear = node;
}

element dequeue(LinkedQueueType* q) {
	QueueNode* del = q->front;
	element result = del->data;
	q->front = q->front->link;
	free(del);
	return result;
}