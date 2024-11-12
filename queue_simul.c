#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 5

typedef struct {
	int id;
	int arrival_time;
	int service_time;
	int isVip; //VIP 여부를 따짐. VIP면 1, 아니면 0
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
	int waitTime; //1명의 대기시간 기록용

	QueueType queue;
	init_queue(&queue);
	srand(time(NULL));

	for (int clock = 0; clock < minutes; clock++) {
		printf("현재시각 = %d\n", clock);
		int randomNum = rand() % 10;
		//여기서부터
		if (randomNum < 2) { //일반 고객 발생 확률 20%
			element customer;
			customer.id = total_customers++;
			comm_customers++; //일반 고객 방문 수 카운트
			customer.arrival_time = clock;
			customer.service_time = (rand() % 3) + 1;
			customer.isVip = 0; //VIP가 아님을 표시
			enqueue(&queue, customer);
			printf("고객 %d이 %d분에 들어옵니다. 업무처리시간 = %d분\n", customer.id, customer.arrival_time, customer.service_time);
		}
		else if (randomNum < 3) { //vip 고객 발생 확률 10%
			element customer;
			customer.id = total_customers++;
			vip_customers++; //VIP 고객 방문 수 카운트
			customer.arrival_time = clock;
			customer.service_time = (rand() % 3) + 1;
			customer.isVip = 1; //VIP임을 표시
			enqueue(&queue, customer);
			printf("vip 고객 %d이 %d분에 들어옵니다. 업무처리시간 = %d분\n", customer.id, customer.arrival_time, customer.service_time);
		}

		if (service_time > 0) {
			printf("고객 %d 업무처리중입니다.\n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("고객 %d이 %d분에 업무 시작, 대기시간은 %d분.\n", customer.id, clock, clock - customer.arrival_time);
				waitTime = clock - customer.arrival_time; //업무처리를 시작한 고객의 대기 시간
				total_wait += waitTime; //전체 대기 시간은 조건문을 타지 않음
				if (!(customer.isVip))
					comm_wait += waitTime; //VIP가 아니면 일반 고객 대기시간에 합산
				else
					vip_wait += waitTime; //VIP면 VIP 고객 대기시간에 합산
			}
		}
	}
	printf("=================================\n");
	printf("VIP 전체 대기 시간 = %d분\n", vip_wait);
	printf("VIP 방문 수 = %d\n", vip_customers);
	printf("VIP 평균 대기 시간 = %d분\n", vip_wait / vip_customers);
	printf("일반 고객 전체 대기 시간 = %d분\n", comm_wait);
	printf("일반 고객 방문 수 = %d\n", comm_customers);
	printf("일반 고객 평균 대기 시간 = %d분\n", comm_wait / comm_customers);
	printf("전체 고객 방문 수 = %d\n", total_customers);
	printf("전체 대기 시간 = %d분\n", total_wait);
	printf("전체 평균 대기 시간 = %d분\n", total_wait / total_customers);
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