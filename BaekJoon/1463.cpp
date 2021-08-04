#include <iostream>
#include <algorithm>
using namespace std;
#define INF 2147483647
int dp[1000001][4];
void init()
{
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            if(i < j ) dp[i][j] = INF;
            else if (i==j) dp[i][j] = 1;
            else{
                if(i%j != 0 )dp[i][j] = INF;
                else dp[i][j] = i/j;
            }   
        }
    }
}
int main()
{
    int n; cin >> n;
    if(n == 1) {cout << 1; return;}
    init();
    for(int i = 4; i <= n; i++)
    {
        dp[i][1] = min({dp[i-1][1],dp[i-1][2],dp[i-1][3]}) + 1;
        if(i % 2 == 0)
            dp[i][2] = min({dp[i/2][1],dp[i/2][2],dp[i/2][3]}) + 1;
        else dp[i][2] = INF;
        if(i % 3 == 0)
            dp[i][3] = min({dp[i/3][1],dp[i/3][2],dp[i/3][3]}) + 1;
        else dp[i][3] = INF;
    }
    cout << min({dp[n][1],dp[n][2],dp[n][3]});
}

