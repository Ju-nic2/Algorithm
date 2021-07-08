#include <stdio.h>
#include <stdlib.h>

#define INF 9999
#define edgeNum  15//�־��� �׷����� ��������

int W[8][8] = { {0,11,9,8,INF,INF,INF,INF},
				{11,0,3,INF,8,8,INF,INF},
				{9,3,0,15,INF,12,1,INF},
				{8,INF,15,0,INF,INF,10,INF},
				{INF,8,INF,INF,5,7,INF,4},
				{INF,8,12,INF,7,0,INF,5},
				{INF,INF,1,10,INF,INF,0,2},
				{INF,INF,INF,INF,4,5,2,0}
};

int F[8] = { 0, };//Prim Algorithm ���� ��������� MST�� ���� �迭,�ʱ�ȭ

typedef struct Edge {
	int start;
	int end;
	int distance;
}Edge;// KrusKal Algorithm ���� Edge, weight�� ǥ���ϱ����� ����ü

Edge* Edge_set[edgeNum] = { NULL }; // Kruskal Algorithm���� ���� Edge���� ������ ������� ����ü �迭



void Prim(int start);

void initial(int* cycleCheck);//n���� ���μ� �κ������� �ʱ�ȭ
int find( int i,int *set);//i�� ����� ǥ��
void sortEdgeSet();//�׷����� �������� ����ġ ������ ����
void makeEdgeSet();//�׷����� ����-��-����ġ �� ǥ�� 
void merge(int p, int q, int* cycleCheck);//F���տ� e����
void kruskal();//ũ�罺Į �˰���

void printMST(Edge* F[]);

int main()
{
	Prim(3);
	for (int i = 1; i < 8; i++) {
		printf("V%d -> V%d\n", i+1, F[i]+1);
	}
	kruskal();
}

void Prim(int start)//���� �˰���
{
	int nearest[8];//vi���� ���� ����� vj ǥ��
	int distance[8];//vi ������ ����ġ
	int vnear;
	
	for (int i = 1; i < 8; i++) { // vi ->start �� �ʱ�ȭ
		nearest[i] = start;
		distance[i] = W[start][i];
	}

	for (int k = 0; k < 7; k++) {
		int min = INF;
		for (int i = 1; i < 8; i++) {//vi ���� �ּҰ� �ǰ� ���ִ� Vvnear ã��
			if (0 <= distance[i] && distance[i] <= min) {
				min = distance[i];
				vnear = i;
			}
		}

		F[vnear] = nearest[vnear];// ã����� F�� �߰�(MST ����)

		distance[vnear] = -1;//����Ŭ �Ǵ°� �����ϱ����� ǥ������
		for (int i = 1; i < 8; i++) {//�׿��� ���鿡�� ����
			if (W[i][vnear] < distance[i]) {
				distance[i] = W[i][vnear];
				nearest[i] = vnear;
			}
		}
	}
}

void initial(int* cycleCheck) { // ���� �ʱ�ȭ ���� �Լ�
	for (int j = 0; j < 8; j++) {
		cycleCheck[j] = j;
	}
	

}
int find(int i, int* set) {//i�����Ե� ������ ��Ʈ�� ã����
	int j = i;
	while (set[j] != j)
		j = set[j];
	return j;
}
void merge(int p, int q, int* cycleCheck) {//�� ���� �պ�
	if (p < q) {
		cycleCheck[q] = p;
	}else
		cycleCheck[p] = q;

}
void makeEdgeSet() { // �׷����� ��� ������ ���� ����
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
void sortEdgeSet() {//������� �������� ������ ����ġ������ �������� ����

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
	Edge* F[7] = { NULL };//���������� F�� �־� MST�� �����.

	makeEdgeSet();//�������� ���� �����
	sortEdgeSet();//����
	initial(cycleCheck);// �� ������ �ڱ��ڽ��� ����Ű�� �ʱ�ȭ

	int count = 0;//MST�� ������ (��尹��-1)
	int cursor = 0;// ���ĵ� �������� ����Ű�� Ŀ����Ȱ�� ����
	while (count <= 6) {//0~6 7�� ���� ���ؼ� MST�����.
		p = find(Edge_set[cursor]->start, cycleCheck);
		q = find(Edge_set[cursor]->end, cycleCheck);
		if (p != q) {//p==q ������ ����Ŭ �̹Ƿ� �Ѿ�� �ٸ���츸 ���ļ� MST����
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
