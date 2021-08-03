#include <iostream>
using namespace std;
        //n k
int dp[1001][1001];
void nCk(int n, int k)
{
    for(int i = 0; i <= n; i++){
        dp[i][0] = 1;
        if(i <= k) dp[i][i] = 1;
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= k; j++)
        {
            dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % 10007;
        }
    }
    cout << dp[n][k];
}
// time out .. 
int nCk_(int n, int k)
{
    if(k == 0 || n == k) return dp[n][k] = 1;
    else return dp[n][k] = nCk_(n-1,k) + nCk_(n-1,k-1);
}
int main()
{
    int n,k; cin >> n >> k;
    //nCk(n,k);
    nCk_(n,k);
    cout << dp[n][k];
}