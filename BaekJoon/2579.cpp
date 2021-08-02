#include <iostream>
#include <algorithm>

using namespace std;
void initarr(int * arr, const int n)
{
    for(int i = 0; i <= n; i++) arr[i] = 0;
}
//top-down
int solution(int* arr, int* dp, int n)
{
    if(n > 2 && dp[n] == 0)
        return dp[n] = max(solution(arr,dp,n-2),solution(arr,dp,n-3)+arr[n-1]) + arr[n];
    else return dp[n];
}
int main()
{
    int *arr, *dp;
    int n; cin >> n;
    arr = (int*)malloc(sizeof(int)*n+1);
    dp = (int*)malloc(sizeof(int)*n+1);
    initarr(arr,n);initarr(dp,n);

    for(int i = 1; i <= n; i++)
    {
        int data; cin >> data;
        arr[i] = data;
    }
    dp[1] = arr[1];
    dp[2] = arr[1] + arr[2];
    /*for(int i = 3; i <= n; i++)
    {
        dp[i] = max(arr[i-1]+dp[i-3], dp[i-2]) + arr[i];
    }*/
    solution(arr,dp,n);
    cout << dp[n];
}