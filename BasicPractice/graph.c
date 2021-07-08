#include <stdio.h>


#define INF 10000000 // 경로가 없는부분 표현

int d[7][7] = { 0, };
int w[7][7] = { {0,4,INF,INF,INF,10,INF}, {3,0,INF,18,INF,INF,INF},{INF,6,0,INF,INF,INF,INF},
				{INF,5,15,0,2,19,5},{INF,INF,12,1,0,INF,INF},{INF,INF,INF,INF,INF,0,10},
				{INF,INF,INF,8,INF,INF,0} };
int D[7][7] = { 0, };
int P[7][7] = { 0, };

void simpleShortestPath();// 모든쌍 최단경로
void floyd(); // 플로이드 알고리즘
void reversFloyd(); // 3번문제
void path(int i, int j);// 경로출력 함수
void printMatrixs(int A[][7]);

int main()
{

		simpleShortestPath();
		printf("1. 모든쌍 최단경로 출력 \n");
		printMatrixs(d);

		floyd();
		printf("2. Floyd 행렬 D\n");
		printMatrixs(D);
		printf("2. Floyd 행렬 P\n");
		printMatrixs(P);
		printf("V3 -> V6 최단경로\n");
		path(2, 5);

		reversFloyd();
		printf("\n\n");
		printf("3. Floyd Reverse행렬 D\n");
		printMatrixs(D);
		printf("3. Floyd REverce 행렬 P\n");
		printMatrixs(P);
		printf("A5 - A2최단경로 출력\n");
		path(4, 1);

}
void printMatrixs(int A[][7])
{
	
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (A[i][j] == -1)
				printf("%2c ",'x');
			else
				printf("%2d ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void simpleShortestPath() {

	for (int i = 0; i < 7; i++) {// 1개 간선 거치는경우로 최초 초기화
		for (int j = 0; j < 7; j++) {
			d[i][j] = w[i][j];
		}
	}
	for (int m = 2; m < 7; m++) {//m개 간선 거칠때
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				int tmp = 100000;//임시 최솟값 변수
				for (int k = 0; k < 7; k++) {// 정점 1-7중 최소가 되는 정점 찾는다.
					if (tmp > d[i][k] + w[k][j])
						tmp = d[i][k] + w[k][j];

				}
				d[i][j] = tmp;
			}
		}
	}
}
void floyd()
{

	for (int i = 0; i < 7; i++) {// 최초 초기화
		for (int j = 0; j < 7; j++) {
			D[i][j] = w[i][j];
			P[i][j] = -1;// 배열 인덱스 로정점이 표기되어있음 V1==0 일경우 구분
		}
	}
	for (int k = 0; k < 7; k++) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {//최소경로찾기
					P[i][j] = k;// 경로상 최소가 되게하는 정점 저장.
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}
void reversFloyd()// v1~v7 을 a7~a1으로 바꿔서 다시.
{

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			D[i][j] = w[6-i][6-j];
			P[i][j] = -1;
		}
	}
	
	for (int k = 0; k < 7; k++) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}
void path(int i, int j)//경로 출력 함수
{
	if (P[i][j] == -1) {
		printf("V%d->V%d, ", i + 1, j + 1);
	}
	else {
		path(i, P[i][j]);
		path(P[i][j], j);
		
	}

}
