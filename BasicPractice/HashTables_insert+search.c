#include <stdio.h>

typedef struct chainedHash {
	int n;
	struct chainedHash * next;
}chainedHash;
/*선형 조사 삽입 검색*/
void hashInsert(int h[], int x);
void hashSearch(int h[], int x);
/*이차원 조사 삽입 검색*/
void hash2Insert(int h[], int x);
void hash2Search(int h[], int x);
/*체이닝 삽입 검색*/
void chaindHashInsert(chainedHash* ch[], int x);
void chainedhashSearch(chainedHash* ch[], int x);

void printhash(int h[]);
void printChainedHash(chainedHash* ch[]);

int main()
{
	int h[13] = { NULL, };/*선형조사 를 위한 배열*/
	int h2[13] = { NULL };/*이차원 조사를 위한 배열*/
	chainedHash* ch[13] = { NULL };/*체이닝을 위한 배열 */

	/*선형 조사*/
	hashInsert(h, 10);
	hashInsert(h, 20);
	hashInsert(h, 30);
	hashInsert(h, 40);
	hashInsert(h, 33);
	printf("33 삽입\n");
	printhash(h);
	hashInsert(h, 46);
	printf("46 삽입\n");
	printhash(h);
	hashInsert(h, 50);
	printf("50 삽입\n");
	printhash(h);
	hashInsert(h, 60);
	printf("60 삽입\n");
	printhash(h);

	/*2차원 조사*/
	hash2Insert(h2, 10);
	hash2Insert(h2, 20);
	hash2Insert(h2, 30);
	hash2Insert(h2, 40);
	hash2Insert(h2, 33);
	printf("33 삽입\n");
	printhash(h);
	hash2Insert(h2, 46);
	printf("46 삽입\n");
	printhash(h);
	hash2Insert(h2, 50);
	printf("50 삽입\n");
	printhash(h);
	hash2Insert(h2, 60);
	printf("60 삽입\n");
	printhash(h2);

	/*체이닝*/
	chaindHashInsert(ch, 10);
	chaindHashInsert(ch, 20);
	chaindHashInsert(ch, 30);
	chaindHashInsert(ch, 40);
	chaindHashInsert(ch, 33);
	printf("33 삽입\n");
	printChainedHash(ch);
	chaindHashInsert(ch, 46);
	printf("46 삽입\n");
	printChainedHash(ch);
	chaindHashInsert(ch, 50);
	printf("50 삽입\n");
	printChainedHash(ch);
	chaindHashInsert(ch, 60);
	printf("60 삽입\n");
	printChainedHash(ch);

}
void printhash(int h[])/*선형,2차원 조사 출력 */
{
	for (int i = 0; i < 13; i++) {
		if (h[i] == NULL)/* 데이터가 없을시 */
			printf("h[%d] = x\n", i);
		else
			printf("h[%d] = %d\n", i, h[i]);
	}
	printf("\n");
}

void printChainedHash(chainedHash* ch[])/*체이닝 출력*/
{
	for (int i = 0; i < 13; i++) {
		if (ch[i] == NULL)/*데이터가 없을시*/
			printf("h[%d] = x\n",i);
		else {
			chainedHash* tmp = ch[i];
			while (tmp != NULL) {
				if(tmp->next == NULL)/*이 데이터가 마지막 일경우*/
					printf("h[%d] = %d ", i, tmp->n);
				else
					printf("h[%d] = %d -> ", i, tmp->n);
				tmp = tmp->next;
			}
			printf("\n");
		}
	}
	printf("\n");
}

void hashInsert(int h[], int x)
{
	int j = x % 13;
	if (h[j] == NULL)/*비어있으면 충돌이 일어나지 않음*/
		h[j] = x;
	else {
		for (int i = 1; i < 13; i++) {/*충돌 일어난 바로 뒷자리 비교 비어있을떄 까지*/
			j = (x + i) % 13;/*hi(x) = (x+i)mod13 */
			if (h[j] == NULL) {
				h[j] = x;
				return;
			}
		}
	}
}
void hashSearch(int h[], int x)
{
	int j = x % 13;
	if (h[j] != NULL && h[j] == x)
		printf("h[%d] == %d\n", j, h[j]);
	else {
		for (int i = 1; i < 13; i++) {
			j = (x + i) % 13;   
			if (h[j] != NULL && h[j] == x) {
				printf("h[%d] == %d\n", j, h[j]);
				return;
			}
		}
	}
}

void hash2Insert(int h[], int x)
{
	int j = x % 13;
	if (h[j] == NULL)
		h[j] = x;
	else {
		for (int i = 1; i < 13; i++) {
			j = (x + (i*i)) % 13;  /*hi(x) = (h(x) = i^2) Mod 13 의 2차원 조사*/
			if (h[j] == NULL) {
				h[j] = x;
				return;
			}

		}
	}
}
void hash2Search(int h[], int x) {
	int j = x % 13;
	if (h[j] != NULL && h[j] == x)
		printf("h[%d] == %d\n", j, h[j]);
	else {
		for (int i = 1; i < 13; i++) {
			j = (x + (i*i)) % 13;
			if (h[j] != NULL && h[j] == x) {
				printf("h[%d] == %d\n", j, h[j]);
				return;
			}
		}
	}
}
void chaindHashInsert(chainedHash *ch[], int x)
{
	int j = x % 13;
	if (ch[j] == NULL) {
		ch[j] = (chainedHash*)malloc(sizeof(chainedHash));
		ch[j]->n = x;
		ch[j]->next = NULL;
	}

	else {/*새로운 노드를 맨 앞으로 끼워 넣는다*/
	chainedHash* tmp;/*삽입을 위한 임시 노드*/
	tmp = (chainedHash*)malloc(sizeof(chainedHash));/*임시 노드에 새로운 데이터 삽입*/
	tmp->n = x;
	tmp->next = ch[j];/*원래 맨앞에 있던노드를 새로운 노드의 next로 지정*/
	ch[j] = tmp;/*새로운 노드가 가장 앞에 온다*/
	}
}
void chainedhashSearch(chainedHash* ch[], int x) 
{
	int j = x % 13;
	if (ch[j]->n == x) {
		printf("%d \n", ch[j]->n);
	}

	else {
		chainedHash* tmp = ch[j];
		int i=0;
		while (tmp->n != x) {
			tmp = tmp->next;
			i++;
		}
		printf("%d번쨰 %d \n", i+1,tmp->n);
	}
}