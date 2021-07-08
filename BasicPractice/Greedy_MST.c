#include <stdio.h>
#include <stdlib.h>

#define INF 9999
#define edgeNum  15//주어진 그래프의 간선갯수

int W[8][8] = { {0,11,9,8,INF,INF,INF,INF},
				{11,0,3,INF,8,8,INF,INF},
				{9,3,0,15,INF,12,1,INF},
				{8,INF,15,0,INF,INF,10,INF},
				{INF,8,INF,INF,5,7,INF,4},
				{INF,8,12,INF,7,0,INF,5},
				{INF,INF,1,10,INF,INF,0,2},
				{INF,INF,INF,INF,4,5,2,0}
};

int F[8] = { 0, };//Prim Algorithm 에서 만들어지는 MST를 위한 배열,초기화

typedef struct Edge {
	int start;
	int end;
	int distance;
}Edge;// KrusKal Algorithm 에서 Edge, weight를 표현하기위한 구조체

Edge* Edge_set[edgeNum] = { NULL }; // Kruskal Algorithm에서 쓰일 Edge들의 정보를 담기위한 구조체 배열



void Prim(int start);

void initial(int* cycleCheck);//n개의 서로소 부분집합을 초기화
int find( int i,int *set);//i의 헤더를 표현
void sortEdgeSet();//그래프의 엣지들을 가중치 순으로 정렬
void makeEdgeSet();//그래프를 시작-끝-가중치 로 표현 
void merge(int p, int q, int* cycleCheck);//F집합에 e삽입
void kruskal();//크루스칼 알고리즘

void printMST(Edge* F[]);

int main()
{
	Prim(3);
	for (int i = 1; i < 8; i++) {
		printf("V%d -> V%d\n", i+1, F[i]+1);
	}
	kruskal();
}

void Prim(int start)//프림 알고리즘
{
	int nearest[8];//vi에서 가장 가까운 vj 표현
	int distance[8];//vi 에서의 가중치
	int vnear;
	
	for (int i = 1; i < 8; i++) { // vi ->start 로 초기화
		nearest[i] = start;
		distance[i] = W[start][i];
	}

	for (int k = 0; k < 7; k++) {
		int min = INF;
		for (int i = 1; i < 8; i++) {//vi 에서 최소가 되게 해주는 Vvnear 찾음
			if (0 <= distance[i] && distance[i] <= min) {
				min = distance[i];
				vnear = i;
			}
		}

		F[vnear] = nearest[vnear];// 찾은노드 F에 추가(MST 만들어감)

		distance[vnear] = -1;//사이클 되는걸 방지하기위해 표시해줌
		for (int i = 1; i < 8; i++) {//그외의 노드들에서 갱신
			if (W[i][vnear] < distance[i]) {
				distance[i] = W[i][vnear];
				nearest[i] = vnear;
			}
		}
	}
}

void initial(int* cycleCheck) { // 집합 초기화 위한 함수
	for (int j = 0; j < 8; j++) {
		cycleCheck[j] = j;
	}
	

}
int find(int i, int* set) {//i가포함된 집합의 루트를 찾아줌
	int j = i;
	while (set[j] != j)
		j = set[j];
	return j;
}
void merge(int p, int q, int* cycleCheck) {//두 집합 합병
	if (p < q) {
		cycleCheck[q] = p;
	}else
		cycleCheck[p] = q;

}
void makeEdgeSet() { // 그래프의 모든 간선들 집합 만듬
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (W[i][j] != 0 && W[i][j] != INF) {
				Edge* tmp;
				tmp = (Edge*)malloc(sizeof(Edge));
				tmp->start = i;
				tmp->end = j;
				tmp->distance = W[i][j];
				Edge_set[count] = tmp;
				W[j][i] = INF;
				count++;
			}
		}
	}

}
void sortEdgeSet() {//만들어진 간선들의 집합을 가중치순으로 오름차순 정렬

	for (int i = 0; i < edgeNum - 1; i++) {
		for (int j = 1; j < edgeNum - i; j++)
			if (Edge_set[j - 1]->distance > Edge_set[j]->distance) {
				Edge* tmp;
				tmp = Edge_set[j];
				Edge_set[j] = Edge_set[j - 1];
				Edge_set[j - 1] = tmp;
			}
	}

}
void kruskal()
{
	int cycleCheck[8];
	int p, q;
	Edge* F[7] = { NULL };//작은순으로 F에 넣어 MST를 만든다.

	makeEdgeSet();//간선들의 집합 만들고
	sortEdgeSet();//정렬
	initial(cycleCheck);// 각 노드들은 자기자신을 가르키게 초기화

	int count = 0;//MST의 간선수 (노드갯수-1)
	int cursor = 0;// 정렬된 간선들을 가리키는 커서역활의 변수
	while (count <= 6) {//0~6 7개 간선 택해서 MST만든다.
		p = find(Edge_set[cursor]->start, cycleCheck);
		q = find(Edge_set[cursor]->end, cycleCheck);
		if (p != q) {//p==q 같으면 사이클 이므로 넘어가고 다를경우만 합쳐서 MST만듬
			merge(q, p, cycleCheck);
			F[count++] = Edge_set[cursor];
		}
		cursor++;
	}
	printMST(F);

}
void printMST(Edge* F[])
{
	for (int i = 0; i < 7; i++) {
		printf("V%d -> V%d = %d\n",(F[i]->start)+1, (F[i]->end)+1, F[i]->distance);
	}
}
