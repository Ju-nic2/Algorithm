#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int binary_search_upp(vector<long long> &arr, const long long target)
{
    int boundary = -1;
    int low = 0; int high = arr.size() - 1;
    while(low<=high)
    {
        int mid = (low + high) / 2;
        if(arr[mid] <= target) {
            if(arr[mid] == target) boundary = mid;
            low = mid + 1;
        }
        else high = mid - 1;
    }
    return boundary;
}
int binary_search_low(vector<long long> &arr, const long long target)
{
    int boundary = -1;
    int low = 0; int high = arr.size() - 1;
    while(low<=high)
    {
        int mid = (low + high) / 2;
        if(arr[mid] >= target) {
            if(arr[mid] == target) boundary = mid;
            high = mid - 1;
        }
        else low = mid + 1; 
    }
    return boundary;
}
int main()
{
    int n;
    cin >> n;

    vector<int> A(n);
    vector<int> B(n);
    vector<int> C(n);
    vector<int> D(n);
    for(int i = 0; i < n; i++)
    {
        int a,b,c,d; cin >> a >> b >> c >> d;
        A[i] = a; B[i] = b; C[i] = c; D[i] = d;
    }
    vector<long long> AB(n*n);
    vector<long long> CD(n*n);
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; j++)
        {
            AB[n*i+j] = A[i] + B[j];
            CD[n*i+j] = C[i] + D[j];
        }
    }

    sort(AB.begin(), AB.end());
    sort(CD.begin(), CD.end());
    long long count = 0; 
    for(int i = 0; i <n*n; i++)
    {
        int u = binary_search_upp(CD,-AB[i]);
        int l = binary_search_low(CD,-AB[i]);
        if(u >= 0 && l >= 0) count += (u-l) + 1;
    }
    cout << count;
    
    
}