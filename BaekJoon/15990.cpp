#include <iostream>
#include <vector>
using namespace std;
long long dp[100001][4];
void init()
{
    for(int i = 1; i <= 3; i++)
    {
        dp[i][i] = 1;
    }
    dp[3][1] = 1;
    dp[3][2] = 1;
    for(int i = 4; i < 100001; i++)
    {
        dp[i][1] = (dp[i-1][2] + dp[i-1][3]) % 1000000009;
        dp[i][2] = (dp[i-2][1] + dp[i-2][3]) % 1000000009;
        dp[i][3] = (dp[i-3][1] + dp[i-3][2]) % 1000000009;
    }
}
int main()
{
    init();
    int T,n; cin >> T ;
    vector<int> Tcase;
    for(int i = 0; i < T; i++)
    {
        cin >> n;
        Tcase.push_back(n);
    }
  
    for(int i = 0; i < T; i++)
        cout << (dp[Tcase[i]][1] + dp[Tcase[i]][2] + dp[Tcase[i]][3]) % 1000000009 << '\n';

}