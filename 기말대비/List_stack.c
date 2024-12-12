#include <stdio.h>
#include <memory.h>

//연결 리스트로 구현한 스택
typedef int element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;
typedef struct {
	StackNode* top;
} LinkedStackType;

void push(LinkedStackType*, element);
element pop(LinkedStackType*);

int main() {
	LinkedStackType* s = (LinkedStackType*)malloc(sizeof(LinkedStackType));
	push(s, 10);
	printf("%d", pop(s));
}

void push(LinkedStackType* stack, element val) {
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->data = val;
	node->link = stack->top;
	stack->top = node;
}

element pop(LinkedStackType* stack) {
	StackNode* del = stack->top;
	element result = del->data;
	stack->top = del->link;
	free(del);
	return result;
}