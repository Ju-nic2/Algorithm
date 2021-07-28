#include <iostream>
using namespace std;
const int nm = 1000001;
int n,m;
int arr[nm];
long long treeLen(int len)
{
    long long sum = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > len) sum += arr[i]-len;
    }    
    return sum;
}

void maxLen(int highest)
{
    int low = 0; int high = highest;
    while(low<=high)
    {
        int mid = (low+high)/2;
        if(treeLen(mid)>=m) low = mid + 1;
        else high = mid - 1;
    }
    cout <<low -1;
}

int main()
{
    cin >>n >> m;
    int max = 0;
    for(int i = 0 ; i < n ; i++)
    {
        cin >> arr[i];
        if(max < arr[i]) max = arr[i];
    }
    maxLen(max);
}