#include <iostream>
#include <algorithm>
using namespace std;
int arr1[500001];
int binarySearch_low(int target,int n)
{
    int low = 0; int high = n-1;
    int low_b = -1;
    while(low<=high)
    {
        int mid = (low+high) /2;
        if(arr1[mid] >= target) {
            low_b = mid;
            high = mid - 1;
            
        }  
        else low = mid + 1;
    }
    if(arr1[low_b] == target) return low_b;
    else return -1;
}
int binarySearch_upp(int target,int n)
{
    int low = 0; int high = n-1;
    int upp_b = -1;
    while(low<=high)
    {
        int mid = (low+high) /2;
        if(arr1[mid] <= target) {
            upp_b = mid;
            low = mid + 1;
            
        }
        else high = mid - 1;
    }
    if(arr1[upp_b] == target) return upp_b;
    else return -1;
}
int main()
{
    cin.tie(NULL);
	ios::sync_with_stdio(false);
    int n, m, num,count;
    cin >> n;
    for(int i = 0; i < n ; i++){
        cin >> num;
        arr1[i] = num;
    }
    sort(arr1,arr1+n);
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> num;
        int u = binarySearch_upp(num,n);
        int l = binarySearch_low(num,n);
       if(u >= 0 && l >= 0) cout << u-l + 1 << " ";
       else cout << 0 << " ";
    }
   
    

}