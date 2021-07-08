#include <stdio.h>


#define INF 10000000 // ��ΰ� ���ºκ� ǥ��

int d[7][7] = { 0, };
int w[7][7] = { {0,4,INF,INF,INF,10,INF}, {3,0,INF,18,INF,INF,INF},{INF,6,0,INF,INF,INF,INF},
				{INF,5,15,0,2,19,5},{INF,INF,12,1,0,INF,INF},{INF,INF,INF,INF,INF,0,10},
				{INF,INF,INF,8,INF,INF,0} };
int D[7][7] = { 0, };
int P[7][7] = { 0, };

void simpleShortestPath();// ���� �ִܰ��
void floyd(); // �÷��̵� �˰���
void reversFloyd(); // 3������
void path(int i, int j);// ������ �Լ�
void printMatrixs(int A[][7]);

int main()
{

		simpleShortestPath();
		printf("1. ���� �ִܰ�� ��� \n");
		printMatrixs(d);

		floyd();
		printf("2. Floyd ��� D\n");
		printMatrixs(D);
		printf("2. Floyd ��� P\n");
		printMatrixs(P);
		printf("V3 -> V6 �ִܰ��\n");
		path(2, 5);

		reversFloyd();
		printf("\n\n");
		printf("3. Floyd Reverse��� D\n");
		printMatrixs(D);
		printf("3. Floyd REverce ��� P\n");
		printMatrixs(P);
		printf("A5 - A2�ִܰ�� ���\n");
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

	for (int i = 0; i < 7; i++) {// 1�� ���� ��ġ�°��� ���� �ʱ�ȭ
		for (int j = 0; j < 7; j++) {
			d[i][j] = w[i][j];
		}
	}
	for (int m = 2; m < 7; m++) {//m�� ���� ��ĥ��
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				int tmp = 100000;//�ӽ� �ּڰ� ����
				for (int k = 0; k < 7; k++) {// ���� 1-7�� �ּҰ� �Ǵ� ���� ã�´�.
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

	for (int i = 0; i < 7; i++) {// ���� �ʱ�ȭ
		for (int j = 0; j < 7; j++) {
			D[i][j] = w[i][j];
			P[i][j] = -1;// �迭 �ε��� �������� ǥ��Ǿ����� V1==0 �ϰ�� ����
		}
	}
	for (int k = 0; k < 7; k++) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {//�ּҰ��ã��
					P[i][j] = k;// ��λ� �ּҰ� �ǰ��ϴ� ���� ����.
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}
void reversFloyd()// v1~v7 �� a7~a1���� �ٲ㼭 �ٽ�.
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
void path(int i, int j)//��� ��� �Լ�
{
	if (P[i][j] == -1) {
		printf("V%d->V%d, ", i + 1, j + 1);
	}
	else {
		path(i, P[i][j]);
		path(P[i][j], j);
		
	}

}
