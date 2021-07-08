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
void reset(double arr[],int n); /*배열정렬후 다시 정렬안된상태로 초기화 시키기 위해 만든함수*/


void swap(double* a, double* b) {
	double tmp = (*b);
	(*b) = (*a);
	(*a) = tmp;
}

int main() {
	
	clock_t finish, start;
	double duration;
	for (int n = 1000; n <= 20000; n+=1000) {
		double* arr1 = malloc(sizeof(double) * n);/* n 만큼 동적할당*/
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
	srand(1);/*  일정한 값 넣기위해 */
	for (int i = 0; i < n; i++) {
		arr[i] = (double)(rand() % 2000 - 1000) / (1000);
	}

}

void SelectionSort(double arr[], int n)
{

	for (int i = 0; i < n; i++) {
		double max = arr[0];
		int maxLocation = 0;
		for (int j = 0; j < n - i; j++) {/* 정렬된부분 (arr[n-i]~arr[n-i-1]) 제외하고 가장큰수 찾음*/
			if (max < arr[j]) {
				max = arr[j];
				maxLocation = j;
			}
		}
		swap(&arr[maxLocation], &arr[n - i - 1]);/* i번째 비교에서 i번째 큰수를 arr[n-i]에 넣음*/
	}
	
}
void BubleSort(double arr[], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i-1; j++) {/*j부터 n-1까지 arr[j] 바로 옆을 비교하면서 작으면 위치바꿈 => 가장 큰게 오른쪽으로이동*/
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
		while (loc >= 0 && newitem < arr[loc]) {/*위치가 배열 범위 안지나가고 넣어야할께 현 위치보다 작으면?*/
			arr[loc + 1] = arr[loc];/*하나씩 밀리면서 자리확보*/
			loc--;
		}
		swap(&newitem, &arr[loc + 1]);/*확보한 자리에 삽입.*/
	}
}
void MergeSort(double arr[], int p, int r)
{
	if (p < r)  {
		int q = (p + r) / 2;/*반으로 분할*/
		MergeSort(arr, p, q);/*왼쪽*/
		MergeSort(arr, q + 1, r);/*오른쪽*/
		merge(arr, p, q, r);/*합체*/
	}


}
void merge(double arr[], int p, int q, int r)
{
	
	int i = p, j = q + 1, k = 0;
	double *sort = malloc(sizeof(double) * (r+1));/*정렬 된 결과를 넣기위한 임시 배열*/
	while (i <= q && j <= r) {/*나뉜거의 왼쪽~반 반~오른쪽 비교하면서 작은거부터 임시배열에 채워넣음*/
		if (arr[i] <= arr[j])
			sort[k++] = arr[i++];
		else
			sort[k++] = arr[j++];
	}
	while (i <= q)/*왼쪽 ~ 반중 남은 요소가 있을때*/
		sort[k++] = arr[i++];
	while (j <= r)/*반~오른쪽 남은 요소가 있을때*/
		sort[k++] = arr[j++];
	i = p;
	k = 0;
	while (i <= r)/*원래 배열에 넣기*/
		arr[i++] = sort[k++];
	free(sort);
}
void QuickSort(double arr[], int p, int r)
{
	if (p < r) {
		int pv = partition(arr, p, r);/*비교의 기준이될 피벗 구해오고 위치저장,*/
		QuickSort(arr, p, pv - 1);/*왼쪽~ 피벗전 까지 다시 정렬*/
		QuickSort(arr, pv + 1, r);/*피벗이후 ~ 오른쪽 까지 다시 정렬*/
	}
	

}
int partition(double arr[], int p, int r)
{
	double pivot = arr[r];/*피벗은 주어진 배열의 가장 오른쪽*/
	int count = p;/* 피벗기준으로 작은게 왼쪽 큰게 오른쪽 가기위해 위치 파악*/
	for (int i = p; i < r; i++) {
		if (arr[i] < pivot) {/* 작아? */
			swap(&arr[count++], &arr[i]);/*작으면 컸던거 있던 위치랑 바꿔줌*/
		}
	}
	swap(&arr[count], &arr[r]);/* 배열은 0 부터 시작이니깐 피벗의 위치는 arr[작은거개수 +1] 그자리에 넣어준다*/
	return count;/*이게 피벗 위치다 */
}
void makeHeap(double arr[], int n)
{
	for (int i = n/2; i >0; i--)/* 마지막 부모 부터 시작, 힙성질 만족하게 바꿔줌*/
		Heapify(arr, i, n);
}
void Heapify(double arr[], int k, int n)
{
	int left = 2 * k;
	int right = (2 * k) + 1;
	int small;
	if (right <= n) {/*오른쪽이 n보다 크면 찾을수 없지!왜? 배열 크기 넘어간곳에 데이터가 없거든~*/
		if (arr[right - 1] <= arr[left - 1]) {/*왼쪽 오른쪽 중 더작은거 찾아봐라*/
			small = right;
		}
		else
			small = left;
	}
	else if (left <= n) {/* 근데 오른쪽은 없고 왼쪽만 있을수도 그럼 무조건 왼쪽이 젤작자너*/
		small = left;
	}
	else
		return;/* 왼오 둘다없어? 그럼 그만해~*/
	if (arr[small-1] < arr[k - 1]) {
		swap(&arr[small- 1], &arr[k - 1]);
		Heapify(arr, small, n);/*바꾼위치 가서 한번더 체크*/
	}
}
void HeapSort(double arr[], int n)
{
	makeHeap(arr, n);/* 처음 배열 힙성질로 함 바꿔주고*/
	for (int i = n; i > 0; i--) {
		swap(&arr[0], &arr[i]);/*제일 작은거 꺼내고 젤 마지막꺼 루트로!*/
		Heapify(arr, 1, i);/*이거 다시 바꿔와 ! 힙처럼*/
	}
}