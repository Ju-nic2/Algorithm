#include <stdio.h>
#include <stdlib.h>

int bestset[5] = { 0,0,0,0,0 }; //item 포함관계 표현 배열(최고이익)
int include[5] = { 0,0,0,0,0 };// item 포함관계 파악
int W = 9;
int p[5] = { 20,30,35,12,3 };
int w[5] = { 2,5,7,3,1 };
int maxprofit = 0;
int Bread_First_W = 9;
int Bread_First_p[5] = { 20,30,35,12,3 };
int Bread_First_w[5] = { 2,5,7,3,1 };
int Bread_First_maxprofit = 0;

int Best_maxprofit = 0;

typedef struct heapnode {//Best-First 노드 정의
	
	int level;
	int profit;
	int weight;
	int bound;
}heapnode;

typedef struct PriorityQueue { // 우선순위 큐 구조체
	heapnode* heap[10];
	int count;
}PriorityQueue;


typedef struct node {//Breadth-First 노드 정의
	struct node* next;
	int level;
	int profit;
	int weight;
}node;

typedef struct Queue { // 큐 구조체
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
			printf(" %d번째 item 포함 \n", i + 1);
		}

	}
	printf(" maxprofit : %d\n", maxprofit);
	knapsack2();
	knapsack3();
}

void knapsack(int index, int profit, int weight) {// Depth-First 로 문제해결 함수
	if ((weight <= W) && (profit > maxprofit)) {
		maxprofit = profit;
		for (int i = 0; i < 5; i++)
			bestset[i] = include[i]; // 최대 이익 노드 저장
	}
	if (promising(index,profit,weight)) {//유망성 판단
		include[index + 1] = 1;
		knapsack(index + 1, profit + p[index + 1], weight + w[index + 1]); //왼쪽부터 (그수준 아이템 포함한는경우)
		include[index + 1] = 0;
		knapsack(index + 1, profit, weight );//오른쪽으로  (그수준 아이템 포함하지 않는 경우)

	}
}

int promising(int index, int profit, int weight) // 노드의 유망함 판단함수 
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
		while ((j <= 5) && (totweight+w[j] <= W)) { //무게가 가득 찰때까지 넣는다
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		}
		k = j;
		if (k <= 5) { // 그다음 아이템을 쪼개서 한계까지 넣는다
			bound = bound + (W - totweight) * (p[k] / w[k]);
			
		}
		if (bound > maxprofit) {// 최대이익이 bound 보다 작아야 유망.
			printf(" %d %d %d\n", profit, weight, bound);
			return 1;
		}
		else
			return 0;
	}
}
void knapsack2() { // Breath-First 로 문제해결 함수
	Queue Q;
	node* v, * u;
	initialize(&Q);
	v = (node*)malloc(sizeof(node)); // 현재 노드 표현
	u = (node*)malloc(sizeof(node));// 자식 노드 표현
	int level = 0;
	v->level = -1; v->profit = 0; v->weight = 0; v->next == NULL; Bread_First_maxprofit = 0;
	printf("Breath-First\n");
	printf("-------------------- Level %d --------------------\n", level);
	enqueue(&Q, v); // root 삽입
	while (!isEmpty(&Q)) { // 큐가 빌때까지 반복
		v = dequeue(&Q);// 큐에서 노드를 꺼낸후 
		if (v->level + 1 > level) {
			printf("-------------------- Level %d --------------------\n", level+1);
			level++;
		}
		printf(" Weight : %d profit : %d  bound : %d\n", v->weight, v->profit, bound(v));
		//왼쪽 노드(item 포함하는 경우)
		u->level = v->level + 1;
		u->profit = v->profit + Bread_First_p[v->level + 1];
		u->weight = v->weight + Bread_First_w[v->level + 1];

		if ((u->weight <= Bread_First_W) && (u->profit > Bread_First_maxprofit)) // 최대이익 갱신
		{ 
			if (u->weight == 9) {
				printf(" Max Node\n");
				printf(" Weight : %d profit : %d  bound : %d\n", u->weight, u->profit, bound(u));
			}
			Bread_First_maxprofit = u->profit;
		}
		if (bound(u) > Bread_First_maxprofit) { // 유망성 검사후 유망하다면 삽입
			enqueue(&Q, u);
		}
		//오른쪽 노드(item 포함하지 않는 경우)
		u->weight = v->weight;
		u->profit = v->profit;
		if (bound(u) > Bread_First_maxprofit) {// 유망성 검사후 유망하다면 삽입
			enqueue(&Q, u);

		}
		printf("\n");
		if (isEmpty(&Q)) {
			printf(" Weight : 9 profit : 55 bound : 55\n"); // maxprofit 노드 
			printf(" Max Profit\n");
			printf(" %d\n", Bread_First_maxprofit);
		}


	}

}
int bound(node* u) { //Breath-First bound 계산 함수
	int j, k, totweight, result;
	if (u->weight > Bread_First_W) // 무게 초과시 
		return 0; 
	else {
		result = u->profit;
		j = u->level + 1;
		totweight = u->weight;// 현재 노드 정보 +
		while ((j <= 5) && (totweight + Bread_First_w[j] <= Bread_First_W)) {// 무게 안넘칠때까지 아이템 넣음
			totweight = totweight + Bread_First_w[j];
			result = result + Bread_First_p[j];
			j++;
		}
		k = j;
		if (k <= 5)//한계 까지 다음 물건을 쪼개서 삽입
			result = result + (Bread_First_W - totweight) * Bread_First_p[k] / Bread_First_w[k];
		return result;
	}
}

void initialize(Queue* Q) { // 큐초기화
	Q->front = NULL;
	Q->rear = NULL;
	Q->size = 0;
}

int isEmpty(Queue* Q) { //큐가 비었는지 확인
	if (Q->size == 0)
		return 1;
	else
		return 0;
}

void enqueue(Queue* Q, node* v) {//큐에 노드 삽입
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
		Q->rear->next = tmp;//원래 있던거에 연결
	}
	Q->rear = tmp;//Q의 끝은 방금 만들어진 노드.
	Q->size++;

}
node* dequeue(Queue* Q) {//큐에서 노드 빼기
	if (isEmpty(Q)) {
		return NULL;
	}
	node* tmp;
	tmp = Q->front;// 뺄 노드 
	Q->front = tmp->next; // 연결관계 갱신
	Q->size--;
	return tmp;
}

int pbound(heapnode* u) { //Best-First bound 계산 함수
	int j, k, totweight, result;
	if (u->weight > Bread_First_W) // 무게초과시
		return 0;
	else {
		result = u->profit;
		j = u->level + 1;
		totweight = u->weight;// 현재 노드 정보 +
		while ((j <= 5) && (totweight + Bread_First_w[j] <= Bread_First_W)) {// 무게 안넘칠때까지 아이템 넣음
			totweight = totweight + Bread_First_w[j];
			result = result + Bread_First_p[j];
			j++;
		}
		k = j;
		if (k <= 5)//한계 까지 다음 물건을 쪼개서 삽입
			result = result + (Bread_First_W - totweight) * Bread_First_p[k] / Bread_First_w[k];
		return result;
	}
}
void knapsack3() { // Best-First 로 문제해결 함수
	PriorityQueue PQ;
	heapnode* v = (heapnode*)malloc(sizeof(heapnode)); // 현재노드 표현
	heapnode*u = (heapnode*)malloc(sizeof(heapnode));//자식노드 표현

	initializePQ(&PQ);
	v->level = -1;
	v->profit = 0;
	v->weight = 0;
	v->bound = pbound(v);
	maxprofit = 0;
	int level = 0;
	printf(" Best-First\n");
	enpqueue(&PQ, v);//루트 노드 삽입
	while (!isEmptyPQ(&PQ)) {
		v = depqueue(&PQ);	
			printf("-------------------- step %d --------------------\n", level + 1);
			level++;
		printf(" Weight : %d profit : %d bound : %d \n", v->weight, v->profit,v->bound);
		if (v->bound > maxprofit) { // 빼낸 노드의 유망성 판단
			//다음 item 을 포함하는 경우(왼쪽자식)
			u->level = v->level + 1;
			u->profit = v->profit + Bread_First_p[v->level + 1];
			u->weight = v->weight + Bread_First_w[v->level + 1];
			//최대이익 갱신
			if ((u->weight <= Bread_First_W) && (u->profit > maxprofit)) {
				if (u->weight == 9) {
					printf(" Max Node\n");
					printf(" Weight : %d profit : %d  bound : %d\n", u->weight, u->profit, bound(u));
				}
				maxprofit = u->profit;
			}
			u->bound = pbound(u);
			if (pbound(u) > maxprofit) { // 왼쪽자식이 유망하다면 큐에 삽입
				enpqueue(&PQ, u);
			}

			u->weight = v->weight;
			u->profit = v->profit;
			u->bound = pbound(u);
			if (pbound(u) > maxprofit) {//오른쪽 자식이 유망하다면 큐에 삽입
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

void enpqueue(PriorityQueue* PQ, heapnode* v) // 우선순위큐 삽입
{
		int k = PQ->count+1; //힙 의 젤 마지막노드
		int parent = k / 2; // 마지막 노드의 부모
		while (k != 1) {
			if (PQ->heap[parent-1]->bound < v->bound) { // 삽입 위치의 부모가 더 작다면
				//위치 바꿔줌
				PQ->heap[k-1]->bound = PQ->heap[parent-1]->bound;
				PQ->heap[k-1]->level = PQ->heap[parent-1]->level;
				PQ->heap[k-1]->weight = PQ->heap[parent-1]->weight;
				PQ->heap[k-1]->profit = PQ->heap[parent-1]->profit;
			}
			else
				break; // 아닐경우 더할 필요가 없으므로 종료
			k = parent;// 부모의 부모로 올라가서 한번더 검사
			parent = k / 2;

		}
		// 정리 완료된 힙에 삽입
		PQ->heap[k-1]->bound = v->bound; 
		PQ->heap[k-1]->level = v->level;
		PQ->heap[k-1]->weight = v->weight;
		PQ->heap[k-1]->profit = v->profit;
	PQ->count++;
}
heapnode* depqueue(PriorityQueue* PQ)// 우선순위큐 삭제
{
	//힙 top에 있는 노드 미리 빼둔다. 
	heapnode* re = (heapnode*)malloc(sizeof(heapnode));
	re->bound = PQ->heap[0]->bound;
	re->profit = PQ->heap[0]->profit;
	re->weight = PQ->heap[0]->weight;
	re->level = PQ->heap[0]->level;

	if (PQ->count == 1) { // 힙 노드가 1개뿐이면 그냥 넘겨줌
		PQ->count--;
	}
	else if (PQ->count==2) {//힙 노드가 2개라면 하나 남은 노드를 top에 넣어줌
		PQ->heap[0]->bound = PQ->heap[PQ->count - 1]->bound;
		PQ->heap[0]->profit = PQ->heap[PQ->count - 1]->profit;
		PQ->heap[0]->weight = PQ->heap[PQ->count - 1]->weight;
		PQ->heap[0]->level = PQ->heap[PQ->count - 1]->level;
		PQ->count--;
	}
	else if (PQ->count > 2) {//힙 노드가 2개 이상이라면 맨 마지막노드를 top 으로 넣어주고 최대 힙으로 만듬.
	
		PQ->heap[0]->bound = PQ->heap[PQ->count - 1]->bound;
		PQ->heap[0]->profit = PQ->heap[PQ->count - 1]->profit;
		PQ->heap[0]->weight = PQ->heap[PQ->count - 1]->weight;
		PQ->heap[0]->level = PQ->heap[PQ->count - 1]->level;
		PQ->count--;
		heapify(&PQ, 1);
	}
	return re;
}
void heapify(PriorityQueue* PQ,int k) // 노드들 을 최대 힙으로 구성하는 함수 
{

	int left = k * 2;
	int right = k * 2 + 1;
	int s; //왼쪽, 오른쪽중 더 큰값을 가진 노드를 파악하기 위한 변수 
	
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

	if (PQ->heap[s-1]->bound > PQ->heap[k - 1]->bound) { //왼쪽 오른쪽중 더 큰 노드가 부모보다도 크다면 교체
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

		heapify(&PQ, s);//교체된 노드의 부모,형제 노드에서 다시 검사.
	}
}
