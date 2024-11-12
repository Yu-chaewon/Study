#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 5

typedef struct {
	int id;
	int arrival_time;
	int service_time;
	int isVip; //VIP ���θ� ����. VIP�� 1, �ƴϸ� 0
} element;

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void init_queue(QueueType*);
int is_empty(QueueType*);
int is_full(QueueType*);
void enqueue(QueueType*, element);
element dequeue(QueueType*);

int main(void) {
	int minutes = 50000;

	int total_wait = 0;
	int comm_wait = 0;
	int vip_wait = 0;

	int total_customers = 0;
	int comm_customers = 0;
	int vip_customers = 0;

	int service_time = 0;
	int service_customer;
	int waitTime; //1���� ���ð� ��Ͽ�

	QueueType queue;
	init_queue(&queue);
	srand(time(NULL));

	for (int clock = 0; clock < minutes; clock++) {
		printf("����ð� = %d\n", clock);
		int randomNum = rand() % 10;
		//���⼭����
		if (randomNum < 2) { //�Ϲ� �� �߻� Ȯ�� 20%
			element customer;
			customer.id = total_customers++;
			comm_customers++; //�Ϲ� �� �湮 �� ī��Ʈ
			customer.arrival_time = clock;
			customer.service_time = (rand() % 3) + 1;
			customer.isVip = 0; //VIP�� �ƴ��� ǥ��
			enqueue(&queue, customer);
			printf("�� %d�� %d�п� ���ɴϴ�. ����ó���ð� = %d��\n", customer.id, customer.arrival_time, customer.service_time);
		}
		else if (randomNum < 3) { //vip �� �߻� Ȯ�� 10%
			element customer;
			customer.id = total_customers++;
			vip_customers++; //VIP �� �湮 �� ī��Ʈ
			customer.arrival_time = clock;
			customer.service_time = (rand() % 3) + 1;
			customer.isVip = 1; //VIP���� ǥ��
			enqueue(&queue, customer);
			printf("vip �� %d�� %d�п� ���ɴϴ�. ����ó���ð� = %d��\n", customer.id, customer.arrival_time, customer.service_time);
		}

		if (service_time > 0) {
			printf("�� %d ����ó�����Դϴ�.\n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("�� %d�� %d�п� ���� ����, ���ð��� %d��.\n", customer.id, clock, clock - customer.arrival_time);
				waitTime = clock - customer.arrival_time; //����ó���� ������ ���� ��� �ð�
				total_wait += waitTime; //��ü ��� �ð��� ���ǹ��� Ÿ�� ����
				if (!(customer.isVip))
					comm_wait += waitTime; //VIP�� �ƴϸ� �Ϲ� �� ���ð��� �ջ�
				else
					vip_wait += waitTime; //VIP�� VIP �� ���ð��� �ջ�
			}
		}
	}
	printf("=================================\n");
	printf("VIP ��ü ��� �ð� = %d��\n", vip_wait);
	printf("VIP �湮 �� = %d\n", vip_customers);
	printf("VIP ��� ��� �ð� = %d��\n", vip_wait / vip_customers);
	printf("�Ϲ� �� ��ü ��� �ð� = %d��\n", comm_wait);
	printf("�Ϲ� �� �湮 �� = %d\n", comm_customers);
	printf("�Ϲ� �� ��� ��� �ð� = %d��\n", comm_wait / comm_customers);
	printf("��ü �� �湮 �� = %d\n", total_customers);
	printf("��ü ��� �ð� = %d��\n", total_wait);
	printf("��ü ��� ��� �ð� = %d��\n", total_wait / total_customers);
}


void init_queue(QueueType* q) {
	q->front = 0;
	q->rear = 0;
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
}

element dequeue(QueueType* q) {
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}