#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void SelectionSort(double arr[], int n);
void BubleSort(double arr[], int n);
void InsertSort(double arr[], int n);
void MergeSort(double arr[], int p, int r);
void merge(double arr[], int p, int q, int r);
void QuickSort(double arr[], int p, int r);
int partition(double arr[], int p, int r);
void HeapSort(double arr[], int n);
void Heapify(double arr[], int k, int n);
void makeHeap(double arr[], int n);
void reset(double arr[],int n); /*�迭������ �ٽ� ���ľȵȻ��·� �ʱ�ȭ ��Ű�� ���� �����Լ�*/


void swap(double* a, double* b) {
	double tmp = (*b);
	(*b) = (*a);
	(*a) = tmp;
}

int main() {
	
	clock_t finish, start;
	double duration;
	for (int n = 1000; n <= 20000; n+=1000) {
		double* arr1 = malloc(sizeof(double) * n);/* n ��ŭ �����Ҵ�*/
		reset(arr1, n);
		start = clock();
		SelectionSort(arr1, n);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("when n = %d : SelectionSort process time : %.3f msec\n", n,duration);

		reset(arr1, n);
		start = clock();
		BubleSort(arr1, n);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("when n = %d : BubleSort process time : %.3f msec\n", n, duration);

		reset(arr1, n);
		start = clock();
		InsertSort(arr1, n);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("when n = %d : InsertSort process time : %.3f msec\n", n, duration);

		reset(arr1, n);
		start = clock();
		MergeSort(arr1,0, n-1);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("when n = %d : MergeSort process time : %.3f msec\n", n, duration);

		reset(arr1, n);
		start = clock();
		QuickSort(arr1, 0, n-1);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("when n = %d : QuicSort process time : %.3f msec\n", n, duration);

		reset(arr1, n);
		start = clock();
		HeapSort(arr1, n - 1);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("when n = %d :HeapSort process time : %.3f msec\n\n", n, duration);

		free(arr1);
	}
	return 0;
}
void reset(double arr[],int n)
{
	srand(1);/*  ������ �� �ֱ����� */
	for (int i = 0; i < n; i++) {
		arr[i] = (double)(rand() % 2000 - 1000) / (1000);
	}

}

void SelectionSort(double arr[], int n)
{

	for (int i = 0; i < n; i++) {
		double max = arr[0];
		int maxLocation = 0;
		for (int j = 0; j < n - i; j++) {/* ���ĵȺκ� (arr[n-i]~arr[n-i-1]) �����ϰ� ����ū�� ã��*/
			if (max < arr[j]) {
				max = arr[j];
				maxLocation = j;
			}
		}
		swap(&arr[maxLocation], &arr[n - i - 1]);/* i��° �񱳿��� i��° ū���� arr[n-i]�� ����*/
	}
	
}
void BubleSort(double arr[], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i-1; j++) {/*j���� n-1���� arr[j] �ٷ� ���� ���ϸ鼭 ������ ��ġ�ٲ� => ���� ū�� �����������̵�*/
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);

		}
			
	}

}
void InsertSort(double arr[], int n)
{
	for (int i = 1; i < n; i++) {
		int loc = i-1;
		double newitem = arr[i];
		while (loc >= 0 && newitem < arr[loc]) {/*��ġ�� �迭 ���� ���������� �־���Ҳ� �� ��ġ���� ������?*/
			arr[loc + 1] = arr[loc];/*�ϳ��� �и��鼭 �ڸ�Ȯ��*/
			loc--;
		}
		swap(&newitem, &arr[loc + 1]);/*Ȯ���� �ڸ��� ����.*/
	}
}
void MergeSort(double arr[], int p, int r)
{
	if (p < r)  {
		int q = (p + r) / 2;/*������ ����*/
		MergeSort(arr, p, q);/*����*/
		MergeSort(arr, q + 1, r);/*������*/
		merge(arr, p, q, r);/*��ü*/
	}


}
void merge(double arr[], int p, int q, int r)
{
	
	int i = p, j = q + 1, k = 0;
	double *sort = malloc(sizeof(double) * (r+1));/*���� �� ����� �ֱ����� �ӽ� �迭*/
	while (i <= q && j <= r) {/*�������� ����~�� ��~������ ���ϸ鼭 �����ź��� �ӽù迭�� ä������*/
		if (arr[i] <= arr[j])
			sort[k++] = arr[i++];
		else
			sort[k++] = arr[j++];
	}
	while (i <= q)/*���� ~ ���� ���� ��Ұ� ������*/
		sort[k++] = arr[i++];
	while (j <= r)/*��~������ ���� ��Ұ� ������*/
		sort[k++] = arr[j++];
	i = p;
	k = 0;
	while (i <= r)/*���� �迭�� �ֱ�*/
		arr[i++] = sort[k++];
	free(sort);
}
void QuickSort(double arr[], int p, int r)
{
	if (p < r) {
		int pv = partition(arr, p, r);/*���� �����̵� �ǹ� ���ؿ��� ��ġ����,*/
		QuickSort(arr, p, pv - 1);/*����~ �ǹ��� ���� �ٽ� ����*/
		QuickSort(arr, pv + 1, r);/*�ǹ����� ~ ������ ���� �ٽ� ����*/
	}
	

}
int partition(double arr[], int p, int r)
{
	double pivot = arr[r];/*�ǹ��� �־��� �迭�� ���� ������*/
	int count = p;/* �ǹ��������� ������ ���� ū�� ������ �������� ��ġ �ľ�*/
	for (int i = p; i < r; i++) {
		if (arr[i] < pivot) {/* �۾�? */
			swap(&arr[count++], &arr[i]);/*������ �Ǵ��� �ִ� ��ġ�� �ٲ���*/
		}
	}
	swap(&arr[count], &arr[r]);/* �迭�� 0 ���� �����̴ϱ� �ǹ��� ��ġ�� arr[�����Ű��� +1] ���ڸ��� �־��ش�*/
	return count;/*�̰� �ǹ� ��ġ�� */
}
void makeHeap(double arr[], int n)
{
	for (int i = n/2; i >0; i--)/* ������ �θ� ���� ����, ������ �����ϰ� �ٲ���*/
		Heapify(arr, i, n);
}
void Heapify(double arr[], int k, int n)
{
	int left = 2 * k;
	int right = (2 * k) + 1;
	int small;
	if (right <= n) {/*�������� n���� ũ�� ã���� ����!��? �迭 ũ�� �Ѿ���� �����Ͱ� ���ŵ�~*/
		if (arr[right - 1] <= arr[left - 1]) {/*���� ������ �� �������� ã�ƺ���*/
			small = right;
		}
		else
			small = left;
	}
	else if (left <= n) {/* �ٵ� �������� ���� ���ʸ� �������� �׷� ������ ������ �����ڳ�*/
		small = left;
	}
	else
		return;/* �޿� �Ѵپ���? �׷� �׸���~*/
	if (arr[small-1] < arr[k - 1]) {
		swap(&arr[small- 1], &arr[k - 1]);
		Heapify(arr, small, n);/*�ٲ���ġ ���� �ѹ��� üũ*/
	}
}
void HeapSort(double arr[], int n)
{
	makeHeap(arr, n);/* ó�� �迭 �������� �� �ٲ��ְ�*/
	for (int i = n; i > 0; i--) {
		swap(&arr[0], &arr[i]);/*���� ������ ������ �� �������� ��Ʈ��!*/
		Heapify(arr, 1, i);/*�̰� �ٽ� �ٲ�� ! ��ó��*/
	}
}