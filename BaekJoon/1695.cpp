#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int dp[5001][5001];
int main()
{
    int n; cin >> n;
    vector<int> v1(n+1),v2(n+1);
    for(int i = 1; i <= n; i++)
    {
        int data; cin >> data;
        v1[i] = data; v2[i] = data;
    }
    reverse(v2.begin()+1, v2.end());
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(v1[i] == v2[j]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    cout <<  n - dp[n][n];
}
