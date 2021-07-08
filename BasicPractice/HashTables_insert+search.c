#include <stdio.h>

typedef struct chainedHash {
	int n;
	struct chainedHash * next;
}chainedHash;
/*���� ���� ���� �˻�*/
void hashInsert(int h[], int x);
void hashSearch(int h[], int x);
/*������ ���� ���� �˻�*/
void hash2Insert(int h[], int x);
void hash2Search(int h[], int x);
/*ü�̴� ���� �˻�*/
void chaindHashInsert(chainedHash* ch[], int x);
void chainedhashSearch(chainedHash* ch[], int x);

void printhash(int h[]);
void printChainedHash(chainedHash* ch[]);

int main()
{
	int h[13] = { NULL, };/*�������� �� ���� �迭*/
	int h2[13] = { NULL };/*������ ���縦 ���� �迭*/
	chainedHash* ch[13] = { NULL };/*ü�̴��� ���� �迭 */

	/*���� ����*/
	hashInsert(h, 10);
	hashInsert(h, 20);
	hashInsert(h, 30);
	hashInsert(h, 40);
	hashInsert(h, 33);
	printf("33 ����\n");
	printhash(h);
	hashInsert(h, 46);
	printf("46 ����\n");
	printhash(h);
	hashInsert(h, 50);
	printf("50 ����\n");
	printhash(h);
	hashInsert(h, 60);
	printf("60 ����\n");
	printhash(h);

	/*2���� ����*/
	hash2Insert(h2, 10);
	hash2Insert(h2, 20);
	hash2Insert(h2, 30);
	hash2Insert(h2, 40);
	hash2Insert(h2, 33);
	printf("33 ����\n");
	printhash(h);
	hash2Insert(h2, 46);
	printf("46 ����\n");
	printhash(h);
	hash2Insert(h2, 50);
	printf("50 ����\n");
	printhash(h);
	hash2Insert(h2, 60);
	printf("60 ����\n");
	printhash(h2);

	/*ü�̴�*/
	chaindHashInsert(ch, 10);
	chaindHashInsert(ch, 20);
	chaindHashInsert(ch, 30);
	chaindHashInsert(ch, 40);
	chaindHashInsert(ch, 33);
	printf("33 ����\n");
	printChainedHash(ch);
	chaindHashInsert(ch, 46);
	printf("46 ����\n");
	printChainedHash(ch);
	chaindHashInsert(ch, 50);
	printf("50 ����\n");
	printChainedHash(ch);
	chaindHashInsert(ch, 60);
	printf("60 ����\n");
	printChainedHash(ch);

}
void printhash(int h[])/*����,2���� ���� ��� */
{
	for (int i = 0; i < 13; i++) {
		if (h[i] == NULL)/* �����Ͱ� ������ */
			printf("h[%d] = x\n", i);
		else
			printf("h[%d] = %d\n", i, h[i]);
	}
	printf("\n");
}

void printChainedHash(chainedHash* ch[])/*ü�̴� ���*/
{
	for (int i = 0; i < 13; i++) {
		if (ch[i] == NULL)/*�����Ͱ� ������*/
			printf("h[%d] = x\n",i);
		else {
			chainedHash* tmp = ch[i];
			while (tmp != NULL) {
				if(tmp->next == NULL)/*�� �����Ͱ� ������ �ϰ��*/
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
	if (h[j] == NULL)/*��������� �浹�� �Ͼ�� ����*/
		h[j] = x;
	else {
		for (int i = 1; i < 13; i++) {/*�浹 �Ͼ �ٷ� ���ڸ� �� ��������� ����*/
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
			j = (x + (i*i)) % 13;  /*hi(x) = (h(x) = i^2) Mod 13 �� 2���� ����*/
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

	else {/*���ο� ��带 �� ������ ���� �ִ´�*/
	chainedHash* tmp;/*������ ���� �ӽ� ���*/
	tmp = (chainedHash*)malloc(sizeof(chainedHash));/*�ӽ� ��忡 ���ο� ������ ����*/
	tmp->n = x;
	tmp->next = ch[j];/*���� �Ǿտ� �ִ���带 ���ο� ����� next�� ����*/
	ch[j] = tmp;/*���ο� ��尡 ���� �տ� �´�*/
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
		printf("%d���� %d \n", i+1,tmp->n);
	}
}