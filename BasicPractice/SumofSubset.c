#include <stdio.h>
#include <stdlib.h>

void sum_of_subsets(int index, int weight, int total);// sum Of subsets Ǯ�� �Լ�
int promising(int index, int weight, int total);//��� ������ �Ǵ� �Լ�
int estimate_sum_of_subset(int index, int weight, int total);//���� ī���� �˰����� ������ ���� �Լ�

int W = 52;
int w[6] = { 2,10,13,17,22,42 };
int include[6] = { 0,0,0,0,0,0 };


int main()
{
	int count;
	int a = 0;
	int b = 0;
	int c = 0;

	sum_of_subsets(-1, 0, 106);
	printf("\n");
	for (int i = 0; i < 100000; i++) {
		count = estimate_sum_of_subset(-1, 0, 106);
		if (count == 47)
			a++;
		else if (count == 63)
			b++;
		else
			c++;
	}
	printf("numnodes : 47 �� %d �� \n", a);
	printf("numnodes : 63 �� %d �� \n", b);
	printf("numnodes : 127 �� %d �� \n", c);


}

void sum_of_subsets(int index, int weight, int total) 
{
	if (promising(index,weight,total)) {// ����� ������ �Ǵ�
		if (weight == W){ // ����� ������ 
			for (int i = 0; i < 6; i++) {
				if (include[i] == 1) {// ���� ���
					printf("w(%d) %d  ", i + 1, w[i]);
				}
			}
			printf("\n");
		}
		else {
			include[index + 1] = 1;//wi ���� == ���� ����� �������� 
			sum_of_subsets(index + 1, weight + w[index + 1], total - w[index + 1]);
			include[index + 1] = 0;//wi�� ������ ���� == ���� ����� ����������
			sum_of_subsets(index + 1, weight, total - w[index + 1]);
		}
	}
}

int promising(int index, int weight, int total) // ����� ������ �Ǵ�
{
		return((weight + total >= W) && (W == weight || weight + w[index + 1] <= W));
				
}

int estimate_sum_of_subset(int index, int weight, int total) {
	int m, mprod, t, numnodes;
	numnodes = 1;
	m = 1; // ù ���� 1+t0 �� ���� �ʱ�ȭ,����� ������ �ڽĳ���� ����
	mprod = 1;//������鼭 �þ�� ������ ����ġ
	int wh,random; // ������ ��尡 �ϳ��� ������ ������ �����ִ� wh,�ΰ��� ������ �������� �������� random

	while (m != 0&& index!=6) {// �ε����� �Ѿ�� ������ �� ������ �������� ���� �߰�

		wh= 0;
		t = 2;
		mprod = mprod * m;
		numnodes = numnodes + mprod * t;
		m = 0;
		//���� �ڽĳ�尡 �������� �Ǵ�
		if (promising(index + 1, weight + w[index + 1] , total - w[index + 1] )) {
			m++;
			wh = 1;//���� �ϳ��� ����
		}
		//������ �ڽĳ�尡 �������� �Ǵ�
		if (promising(index + 1, weight, total - w[index + 1] )) {
			m++;
			wh = 0;//������ �ϳ��� ����
		}
		
		random = rand() % 2;
		if (m == 2) {//�ڽĳ�� 2����� �����Ұ�� �������� ��
			if (random == 1) {
				weight = weight + w[index + 1];
				total = total - w[index + 1];
				index++;
			}
			else {
				total = total - w[index + 1];
				index++;
			}
			
		}
		else if (m == 1 && wh == 1) {//������ ������ ��尡 ����
			weight = weight + w[index + 1];
			total = total - w[index + 1];
			index++;
		}
		else if (m == 1 && wh == 0) {//������ ������ ��尡 ������
			total = total - w[index + 1];
			index++;
		}
		
	}
	return numnodes;
}