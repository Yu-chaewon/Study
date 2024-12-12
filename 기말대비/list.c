#include <stdio.h>
#include <memory.h>

//단순 연결 리스트, 원형 연결 리스트
typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

//이중 연결 리스트
typedef struct LN {
	element data;
	struct LN* llink;
	struct LN* rlink;
} LN;

//단순 연결 리스트
void insert_first(ListNode*, element);
void insert(ListNode*, ListNode*, element);
void delete_first(ListNode*);
void delete(ListNode*, ListNode*);
void print_list(ListNode*);
ListNode* search_list(ListNode*, element);
ListNode* concat_list(ListNode*, ListNode*);
ListNode* reverse(ListNode*);

//원형 연결 리스트
ListNode* C_insert_first(ListNode*, element);
ListNode* C_insert_last(ListNode*, element);

//이중 연결 리스트
void D_insert(LN*, element);
void D_delete(LN*);

int main() {
	//리스트 생성
	ListNode* head = NULL;
	head = (ListNode*)malloc(sizeof(ListNode));

	head->data = 10;
	head->link = NULL;
}

void insert_first(ListNode* head, element val) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = val;
	node->link = head;
	head = node;
}

void insert(ListNode* head, ListNode* pre, element val) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = val;
	node->link = pre->link;
	pre->link = node;
}

void delete_first(ListNode* head) {
	ListNode* delete = head;
	head = head->link;
	free(delete);
}

void delete(ListNode* head, ListNode* pre) {
	ListNode* delete = pre->link;
	pre->link = delete->link;
	free(delete);
}

void print_list(ListNode* head) {
	ListNode* node = head;
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->link;
	}
}

ListNode* search_list(ListNode* head, element target) {
	for (ListNode* p = head; p != NULL; p = p->link) {
		if (p->data == target)
			return p;
	}
	return NULL;
}

ListNode* concat_list(ListNode* head1, ListNode* head2) {
	ListNode* p;
	for (p = head1; p->link != NULL; p = p->link);
	p->link = head2;
	return head1;
}

ListNode* reverse(ListNode* head) {

}

ListNode* C_insert_first(ListNode* head, element val) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = val;
	node->link = head->link;
	head->link = node;
	return head;
}

ListNode* C_insert_last(ListNode* head, element val) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = val;
	node->link = head->link;
	head->link = node;
	head = node;
	return head;
}

void D_insert(LN* before, element val) {
	LN* node = (LN*)malloc(sizeof(LN));
	node->data = val;
	node->llink = before;
	node->rlink = before->rlink;
	before->rlink->llink = node;
	before->rlink = node;
}

void D_delete(LN* target) {
	target->llink->rlink = target->rlink;
	target->rlink->llink = target->llink;
	free(target);
}