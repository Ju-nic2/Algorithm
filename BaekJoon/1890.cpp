#include <iostream>
using namespace std;
int map[101][101];
long long ans[101][101];

int main()
{
    int n; cin >> n;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cin >> map[i][j];
        }
    }
    ans[1][1] = 1;
   for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            int jump = map[i][j];
            if(jump == 0) continue;
            if(i + jump <= n)
            {
                ans[i + jump][j] += ans[i][j]; 
            }
            if(j + jump <= n)
            {
                ans[i][j + jump] += ans[i][j]; 
            }
        }
    }
    cout << ans[n][n];

}