#include <stdio.h>
#include <stdlib.h>

int bestset[5] = { 0,0,0,0,0 }; //item ���԰��� ǥ�� �迭(�ְ�����)
int include[5] = { 0,0,0,0,0 };// item ���԰��� �ľ�
int W = 9;
int p[5] = { 20,30,35,12,3 };
int w[5] = { 2,5,7,3,1 };
int maxprofit = 0;
int Bread_First_W = 9;
int Bread_First_p[5] = { 20,30,35,12,3 };
int Bread_First_w[5] = { 2,5,7,3,1 };
int Bread_First_maxprofit = 0;

int Best_maxprofit = 0;

typedef struct heapnode {//Best-First ��� ����
	
	int level;
	int profit;
	int weight;
	int bound;
}heapnode;

typedef struct PriorityQueue { // �켱���� ť ����ü
	heapnode* heap[10];
	int count;
}PriorityQueue;


typedef struct node {//Breadth-First ��� ����
	struct node* next;
	int level;
	int profit;
	int weight;
}node;

typedef struct Queue { // ť ����ü
	node* front;
	node* rear;
	int size;
}Queue;



void knapsack(int index, int profit, int weight); // Depth-First 
int promising(int index, int profit, int weight);

void knapsack2();// Breath-First
int bound(node* u);

void initialize(Queue* Q);
int isEmpty(Queue* Q);
void enqueue(Queue* Q, node* v);
node* dequeue(Queue* Q);

void knapsack3();//Best-First
int pbound(heapnode* u);

int isEmptyPQ(PriorityQueue* PQ);
heapnode* depqueue(PriorityQueue* PQ);
void initializePQ(PriorityQueue* PQ);
void enpqueue(PriorityQueue* PQ, heapnode* v);
void heapify(PriorityQueue* PQ, int k);

int main()
{
	printf(" Depth-First\n");
	knapsack(-1, 0, 0);
	printf(" Best Node : \n");
	for (int i = 0; i < 5; i++) {
		if (bestset[i] == 1) {
			printf(" %d��° item ���� \n", i + 1);
		}

	}
	printf(" maxprofit : %d\n", maxprofit);
	knapsack2();
	knapsack3();
}

void knapsack(int index, int profit, int weight) {// Depth-First �� �����ذ� �Լ�
	if ((weight <= W) && (profit > maxprofit)) {
		maxprofit = profit;
		for (int i = 0; i < 5; i++)
			bestset[i] = include[i]; // �ִ� ���� ��� ����
	}
	if (promising(index,profit,weight)) {//������ �Ǵ�
		include[index + 1] = 1;
		knapsack(index + 1, profit + p[index + 1], weight + w[index + 1]); //���ʺ��� (�׼��� ������ �����Ѵ°��)
		include[index + 1] = 0;
		knapsack(index + 1, profit, weight );//����������  (�׼��� ������ �������� �ʴ� ���)

	}
}

int promising(int index, int profit, int weight) // ����� ������ �Ǵ��Լ� 
{
	int j, k;
	int totweight;
	int bound;
	if (index > 5)
		return 0;
	if (weight >= W) return 0;
	else {
		j = index + 1;
		bound = profit;
		totweight = weight;
		while ((j <= 5) && (totweight+w[j] <= W)) { //���԰� ���� �������� �ִ´�
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		}
		k = j;
		if (k <= 5) { // �״��� �������� �ɰ��� �Ѱ���� �ִ´�
			bound = bound + (W - totweight) * (p[k] / w[k]);
			
		}
		if (bound > maxprofit) {// �ִ������� bound ���� �۾ƾ� ����.
			printf(" %d %d %d\n", profit, weight, bound);
			return 1;
		}
		else
			return 0;
	}
}
void knapsack2() { // Breath-First �� �����ذ� �Լ�
	Queue Q;
	node* v, * u;
	initialize(&Q);
	v = (node*)malloc(sizeof(node)); // ���� ��� ǥ��
	u = (node*)malloc(sizeof(node));// �ڽ� ��� ǥ��
	int level = 0;
	v->level = -1; v->profit = 0; v->weight = 0; v->next == NULL; Bread_First_maxprofit = 0;
	printf("Breath-First\n");
	printf("-------------------- Level %d --------------------\n", level);
	enqueue(&Q, v); // root ����
	while (!isEmpty(&Q)) { // ť�� �������� �ݺ�
		v = dequeue(&Q);// ť���� ��带 ������ 
		if (v->level + 1 > level) {
			printf("-------------------- Level %d --------------------\n", level+1);
			level++;
		}
		printf(" Weight : %d profit : %d  bound : %d\n", v->weight, v->profit, bound(v));
		//���� ���(item �����ϴ� ���)
		u->level = v->level + 1;
		u->profit = v->profit + Bread_First_p[v->level + 1];
		u->weight = v->weight + Bread_First_w[v->level + 1];

		if ((u->weight <= Bread_First_W) && (u->profit > Bread_First_maxprofit)) // �ִ����� ����
		{ 
			if (u->weight == 9) {
				printf(" Max Node\n");
				printf(" Weight : %d profit : %d  bound : %d\n", u->weight, u->profit, bound(u));
			}
			Bread_First_maxprofit = u->profit;
		}
		if (bound(u) > Bread_First_maxprofit) { // ������ �˻��� �����ϴٸ� ����
			enqueue(&Q, u);
		}
		//������ ���(item �������� �ʴ� ���)
		u->weight = v->weight;
		u->profit = v->profit;
		if (bound(u) > Bread_First_maxprofit) {// ������ �˻��� �����ϴٸ� ����
			enqueue(&Q, u);

		}
		printf("\n");
		if (isEmpty(&Q)) {
			printf(" Weight : 9 profit : 55 bound : 55\n"); // maxprofit ��� 
			printf(" Max Profit\n");
			printf(" %d\n", Bread_First_maxprofit);
		}


	}

}
int bound(node* u) { //Breath-First bound ��� �Լ�
	int j, k, totweight, result;
	if (u->weight > Bread_First_W) // ���� �ʰ��� 
		return 0; 
	else {
		result = u->profit;
		j = u->level + 1;
		totweight = u->weight;// ���� ��� ���� +
		while ((j <= 5) && (totweight + Bread_First_w[j] <= Bread_First_W)) {// ���� �ȳ�ĥ������ ������ ����
			totweight = totweight + Bread_First_w[j];
			result = result + Bread_First_p[j];
			j++;
		}
		k = j;
		if (k <= 5)//�Ѱ� ���� ���� ������ �ɰ��� ����
			result = result + (Bread_First_W - totweight) * Bread_First_p[k] / Bread_First_w[k];
		return result;
	}
}

void initialize(Queue* Q) { // ť�ʱ�ȭ
	Q->front = NULL;
	Q->rear = NULL;
	Q->size = 0;
}

int isEmpty(Queue* Q) { //ť�� ������� Ȯ��
	if (Q->size == 0)
		return 1;
	else
		return 0;
}

void enqueue(Queue* Q, node* v) {//ť�� ��� ����
	node* tmp = (node*)malloc(sizeof(node));
	if (isEmpty(Q)) {
		tmp->level = v->level;
		tmp->profit = v->profit;
		tmp->weight = v->weight;
		tmp->next = NULL;
		Q->front = tmp;
	}
	else {
		tmp->level = v->level;
		tmp->profit = v->profit;
		tmp->weight = v->weight;
		tmp->next = NULL;
		Q->rear->next = tmp;//���� �ִ��ſ� ����
	}
	Q->rear = tmp;//Q�� ���� ��� ������� ���.
	Q->size++;

}
node* dequeue(Queue* Q) {//ť���� ��� ����
	if (isEmpty(Q)) {
		return NULL;
	}
	node* tmp;
	tmp = Q->front;// �� ��� 
	Q->front = tmp->next; // ������� ����
	Q->size--;
	return tmp;
}

int pbound(heapnode* u) { //Best-First bound ��� �Լ�
	int j, k, totweight, result;
	if (u->weight > Bread_First_W) // �����ʰ���
		return 0;
	else {
		result = u->profit;
		j = u->level + 1;
		totweight = u->weight;// ���� ��� ���� +
		while ((j <= 5) && (totweight + Bread_First_w[j] <= Bread_First_W)) {// ���� �ȳ�ĥ������ ������ ����
			totweight = totweight + Bread_First_w[j];
			result = result + Bread_First_p[j];
			j++;
		}
		k = j;
		if (k <= 5)//�Ѱ� ���� ���� ������ �ɰ��� ����
			result = result + (Bread_First_W - totweight) * Bread_First_p[k] / Bread_First_w[k];
		return result;
	}
}
void knapsack3() { // Best-First �� �����ذ� �Լ�
	PriorityQueue PQ;
	heapnode* v = (heapnode*)malloc(sizeof(heapnode)); // ������ ǥ��
	heapnode*u = (heapnode*)malloc(sizeof(heapnode));//�ڽĳ�� ǥ��

	initializePQ(&PQ);
	v->level = -1;
	v->profit = 0;
	v->weight = 0;
	v->bound = pbound(v);
	maxprofit = 0;
	int level = 0;
	printf(" Best-First\n");
	enpqueue(&PQ, v);//��Ʈ ��� ����
	while (!isEmptyPQ(&PQ)) {
		v = depqueue(&PQ);	
			printf("-------------------- step %d --------------------\n", level + 1);
			level++;
		printf(" Weight : %d profit : %d bound : %d \n", v->weight, v->profit,v->bound);
		if (v->bound > maxprofit) { // ���� ����� ������ �Ǵ�
			//���� item �� �����ϴ� ���(�����ڽ�)
			u->level = v->level + 1;
			u->profit = v->profit + Bread_First_p[v->level + 1];
			u->weight = v->weight + Bread_First_w[v->level + 1];
			//�ִ����� ����
			if ((u->weight <= Bread_First_W) && (u->profit > maxprofit)) {
				if (u->weight == 9) {
					printf(" Max Node\n");
					printf(" Weight : %d profit : %d  bound : %d\n", u->weight, u->profit, bound(u));
				}
				maxprofit = u->profit;
			}
			u->bound = pbound(u);
			if (pbound(u) > maxprofit) { // �����ڽ��� �����ϴٸ� ť�� ����
				enpqueue(&PQ, u);
			}

			u->weight = v->weight;
			u->profit = v->profit;
			u->bound = pbound(u);
			if (pbound(u) > maxprofit) {//������ �ڽ��� �����ϴٸ� ť�� ����
				enpqueue(&PQ, u);

			}
			printf("\n");
			
		}
		if (isEmptyPQ(&PQ)) {
			printf("Max Profit\n");
			printf("%d\n", maxprofit);
		}

	}

}
void initializePQ(PriorityQueue* PQ)
{
	for (int i=0 ; i < 10; i++) {
		PQ->heap[i] = (heapnode*)malloc(sizeof(heapnode));
	}
	PQ->count = 0;
}
int isEmptyPQ(PriorityQueue* PQ)
{
	if (PQ->count == 0)
		return 1;
	else
		return 0;
}

void enpqueue(PriorityQueue* PQ, heapnode* v) // �켱����ť ����
{
		int k = PQ->count+1; //�� �� �� ���������
		int parent = k / 2; // ������ ����� �θ�
		while (k != 1) {
			if (PQ->heap[parent-1]->bound < v->bound) { // ���� ��ġ�� �θ� �� �۴ٸ�
				//��ġ �ٲ���
				PQ->heap[k-1]->bound = PQ->heap[parent-1]->bound;
				PQ->heap[k-1]->level = PQ->heap[parent-1]->level;
				PQ->heap[k-1]->weight = PQ->heap[parent-1]->weight;
				PQ->heap[k-1]->profit = PQ->heap[parent-1]->profit;
			}
			else
				break; // �ƴҰ�� ���� �ʿ䰡 �����Ƿ� ����
			k = parent;// �θ��� �θ�� �ö󰡼� �ѹ��� �˻�
			parent = k / 2;

		}
		// ���� �Ϸ�� ���� ����
		PQ->heap[k-1]->bound = v->bound; 
		PQ->heap[k-1]->level = v->level;
		PQ->heap[k-1]->weight = v->weight;
		PQ->heap[k-1]->profit = v->profit;
	PQ->count++;
}
heapnode* depqueue(PriorityQueue* PQ)// �켱����ť ����
{
	//�� top�� �ִ� ��� �̸� ���д�. 
	heapnode* re = (heapnode*)malloc(sizeof(heapnode));
	re->bound = PQ->heap[0]->bound;
	re->profit = PQ->heap[0]->profit;
	re->weight = PQ->heap[0]->weight;
	re->level = PQ->heap[0]->level;

	if (PQ->count == 1) { // �� ��尡 1�����̸� �׳� �Ѱ���
		PQ->count--;
	}
	else if (PQ->count==2) {//�� ��尡 2����� �ϳ� ���� ��带 top�� �־���
		PQ->heap[0]->bound = PQ->heap[PQ->count - 1]->bound;
		PQ->heap[0]->profit = PQ->heap[PQ->count - 1]->profit;
		PQ->heap[0]->weight = PQ->heap[PQ->count - 1]->weight;
		PQ->heap[0]->level = PQ->heap[PQ->count - 1]->level;
		PQ->count--;
	}
	else if (PQ->count > 2) {//�� ��尡 2�� �̻��̶�� �� ��������带 top ���� �־��ְ� �ִ� ������ ����.
	
		PQ->heap[0]->bound = PQ->heap[PQ->count - 1]->bound;
		PQ->heap[0]->profit = PQ->heap[PQ->count - 1]->profit;
		PQ->heap[0]->weight = PQ->heap[PQ->count - 1]->weight;
		PQ->heap[0]->level = PQ->heap[PQ->count - 1]->level;
		PQ->count--;
		heapify(&PQ, 1);
	}
	return re;
}
void heapify(PriorityQueue* PQ,int k) // ���� �� �ִ� ������ �����ϴ� �Լ� 
{

	int left = k * 2;
	int right = k * 2 + 1;
	int s; //����, �������� �� ū���� ���� ��带 �ľ��ϱ� ���� ���� 
	
	if (right <= PQ->count) {
		if (PQ->heap[right - 1]->bound > PQ->heap[left - 1]->bound)
			s = right;
		else
			s = left;
	}
	else if (left <= PQ->count) {
		s = left;
	}
	else
		return;

	if (PQ->heap[s-1]->bound > PQ->heap[k - 1]->bound) { //���� �������� �� ū ��尡 �θ𺸴ٵ� ũ�ٸ� ��ü
		heapnode* small = (heapnode*)malloc(sizeof(heapnode));
		small->bound = PQ->heap[k - 1]->bound;
		small->profit = PQ->heap[k - 1]->profit;
		small->weight = PQ->heap[k - 1]->weight;
		small->level = PQ->heap[k - 1]->level;

		PQ->heap[k-1]->bound = PQ->heap[s-1]->bound;
		PQ->heap[k-1]->profit = PQ->heap[s-1]->profit;
		PQ->heap[k-1]->weight = PQ->heap[s-1]->weight;
		PQ->heap[k-1]->level = PQ->heap[s-1]->level;

		PQ->heap[s-1]->bound = small->bound;
		PQ->heap[s-1]->profit = small->profit;
		PQ->heap[s-1]->weight = small->weight;
		PQ->heap[s-1]->level = small->level;

		heapify(&PQ, s);//��ü�� ����� �θ�,���� ��忡�� �ٽ� �˻�.
	}
}
