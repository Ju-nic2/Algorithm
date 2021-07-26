#include <iostream>
#include <algorithm>
using namespace std;
int arr1[100001];
bool binarySearch(int target,int n)
{
    int low = 0; int high = n-1;
    while(low<=high)
    {
        int mid = (low+high) /2;
        if(arr1[mid] == target) return true;
        if(arr1[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return 0;
}
int main()
{
    cin.tie(NULL);
	ios::sync_with_stdio(false);
    int n, m, num;
    cin >> n;
    for(int i = 0; i < n ; i++){
        cin >> num;
        arr1[i] = num;
    }
    sort(arr1,arr1+n);
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> num;
        cout << binarySearch(num,n)<<'\n';
    }
   
    

}