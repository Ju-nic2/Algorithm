#include <stdio.h>

int D[5][32] = { 0, };
int P[5][32] = { 0, };
int w[5][5] = {
	{ 0,8,13,18,20 }, { 3,0,7,8,10 }, { 4,11,0,10,7 }, { 6,6,7,0,11 }, { 10,6,2,1,0 }
};

void travel(int n);
void tour(int n,int A);
int minMum(int i, int A, int* makeMinj, int n);
int countVertics(int A, int n);
int Square_2(int n);
int where(int a, int n);

int main()
{

	travel(5);
	tour(5,0b11110);
	printf("D[i][A]\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 32; j++) {
			printf("%d ", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("P[i][A]\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 32; j++) {
			printf("%d ", P[i][j]);
		}
		printf("\n");
	}
		
	
}

int Square_2(int n) { // 2^n의 값
	int num = 1;
	for (int i = 0; i < n; i++)
		num *= 2;
	return num;
}


int countVertics(int A, int n) { // {A} 의 노드 수 구하기
	int cnt = 0;
	int checkbit = 1;
	for (int i = 0; i < n; i++) {
		if (A & checkbit)
			cnt++;
		checkbit = checkbit << 1;
	}

	return cnt;
}

void travel(int n)
{

	int j;//D[i][A] 최솟값 만들어주는 Vj

	for (int i = 0; i < n; i++) {
		D[i][0] = w[i][0];
	}
	//노드들의 집합 {V5,V4,V3,V2,V1} = 11111 처럼 비트로 표현함. 
	for (int k = 1; k < n - 1; k++) { // 노드 1개를 지나갈때~ 노드 3개를 지나갈때
		for (int A = 0b00010; A <= 0b11110; A++) {// V-{v1} 의 모든 부분집합
			if ((countVertics(A, 5) == k) && !(A & 1))  {// 그 부분집합중 K개의 노드를 가지고 V1를 포함하지않음
				for (int i = 1; i < 5; i++) {
					if (!(A & Square_2(i))) {// A 가 Vi 를 포함하지 않음
						D[i][A] = minMum(i, A, &j, n); //Vi 에서 출발후 {A} 노드들을 거쳐 V1까지 경로의 최솟값.
						P[i][A] = j;//Vi에서 {A} 노드들을 거쳐 V1으로 갈때 최소가 되게하는 최초노드 Vi->Vj
						printf("D[%d]{%d} = %d\n",i,A,D[i][A]);
					}
				}
			}
		}
	}
	int A = 0b11110;// A = {v5,v4,v3,v2}
	D[0][A] = minMum(0, A, &j, n);
	P[0][A] = j;
	printf("D[%d]{%d} = %d\n", 0, A, D[0][A]);

}
int where(int a, int n) { // Vi 의 i 값구하기
	int position = 0;
	int checkbit = 1;
	for (int i = 0; i < n; i++) {
		if (a & checkbit)// 켜진자리가 어디인지 파악
			position = i;
		checkbit = checkbit << 1;//2^i 한자리씩 비교위해
	}

	return position;
}
int minMum(int i, int A, int* makeMinj, int n) {//최솟값 구하기 함수 
	int j;
	int tmp;
	int min = 100000;
	for (int a = 0b00010; a <= 0b10000; a=a<<1) { //a = {v2} ~ {v5} 중 
		if (A & a) {//A의 원소
			j = where(a, n);//Vj 의 j값 구하기
			tmp = w[i][j] + D[j][A ^ a];//D[j][A-{Vj}]
			if (tmp < min) {
				min = tmp;
				*makeMinj = j;
			}
		}
	}
	return min;
}
void tour(int n, int A) // 경로 출력 함수
{
	int vi=0, a=A;
	printf("\nV1 -> ");
	for (int i = 0; i < n-1; i++) {
		vi = P[vi][a];
		a = A ^ Square_2(vi);
		printf("v%d -> ", vi + 1);
	}
	printf("V1\n");
	
}