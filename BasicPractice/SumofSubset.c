#include <stdio.h>
#include <stdlib.h>

void sum_of_subsets(int index, int weight, int total);// sum Of subsets 풀이 함수
int promising(int index, int weight, int total);//노드 유망성 판단 함수
int estimate_sum_of_subset(int index, int weight, int total);//몬테 카를로 알고리즘을 적용한 추정 함수

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
	printf("numnodes : 47 개 %d 번 \n", a);
	printf("numnodes : 63 개 %d 번 \n", b);
	printf("numnodes : 127 개 %d 번 \n", c);


}

void sum_of_subsets(int index, int weight, int total) 
{
	if (promising(index,weight,total)) {// 노드의 유망성 판단
		if (weight == W){ // 정답과 같으면 
			for (int i = 0; i < 6; i++) {
				if (include[i] == 1) {// 원소 출력
					printf("w(%d) %d  ", i + 1, w[i]);
				}
			}
			printf("\n");
		}
		else {
			include[index + 1] = 1;//wi 더함 == 현재 노드의 왼쪽으로 
			sum_of_subsets(index + 1, weight + w[index + 1], total - w[index + 1]);
			include[index + 1] = 0;//wi를 더하지 않음 == 현재 노드의 오른쪽으로
			sum_of_subsets(index + 1, weight, total - w[index + 1]);
		}
	}
}

int promising(int index, int weight, int total) // 노드의 유망함 판단
{
		return((weight + total >= W) && (W == weight || weight + w[index + 1] <= W));
				
}

int estimate_sum_of_subset(int index, int weight, int total) {
	int m, mprod, t, numnodes;
	numnodes = 1;
	m = 1; // 첫 계산시 1+t0 를 위한 초기화,노드의 유망한 자식노드의 개수
	mprod = 1;//깊어지면서 늘어나는 노드들의 추정치
	int wh,random; // 유망한 노드가 하나만 있을시 방향을 정해주는 wh,두개가 있을시 무작위로 가기위한 random

	while (m != 0&& index!=6) {// 인덱스가 넘어가면 노드들을 샐 이유가 없음으로 조건 추가

		wh= 0;
		t = 2;
		mprod = mprod * m;
		numnodes = numnodes + mprod * t;
		m = 0;
		//왼쪽 자식노드가 유망한지 판단
		if (promising(index + 1, weight + w[index + 1] , total - w[index + 1] )) {
			m++;
			wh = 1;//왼쪽 하나만 유망
		}
		//오른쪽 자식노드가 유망한지 판단
		if (promising(index + 1, weight, total - w[index + 1] )) {
			m++;
			wh = 0;//오른쪽 하나만 유망
		}
		
		random = rand() % 2;
		if (m == 2) {//자식노드 2개모두 유망할경우 무작위로 들어감
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
		else if (m == 1 && wh == 1) {//유일한 유망한 노드가 왼쪽
			weight = weight + w[index + 1];
			total = total - w[index + 1];
			index++;
		}
		else if (m == 1 && wh == 0) {//유일한 유망한 노드가 오른쪽
			total = total - w[index + 1];
			index++;
		}
		
	}
	return numnodes;
}