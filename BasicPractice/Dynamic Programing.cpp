#include <iostream>
using namespace std;
long long DP[91];
long long DP1[91];
//DP top down
long long solve(long long n)
{
    if(n <= 1) return n;
    if(DP1[n] != 0) return DP1[n];
    else return DP1[n] = solve(n-1) + solve(n-2);
}

int main()
{
    int n;
    cin >> n;
    DP[1] = 1;
    DP1[1] = 1;
    //DP bottom up
    for(int i = 2; i <= n; i++)
    {
        DP[i] = DP[i-1] + DP[i-2];
    }
    cout << DP[n] ; /*" "<< solve(n);*/
}