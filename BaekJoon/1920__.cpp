#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int arr1[100001];
    int n,m,num;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr1[i];
    sort(arr1,arr1+n);
    cin >> m;
    for(int i = 0; i < m; i++) {cin >> num; cout << binary_search(arr1,arr1+n,num) << '\n';}
}