#include <iostream>
using namespace std;

int map[501][501];
int dp[501][501];
bool visit[501][501];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int n,m; 
int solve(int x, int y) {
    if (y == 1 && x == 1){
        return 1;
    }
    if(visit[y][x]) return dp[y][x];
    else{
        visit[y][x] = true;
        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k];
            int nx = x + dx[k];
            if (ny >= 1 && ny <= n && nx >= 1 && nx <= m && map[y][x] < map[ny][nx]) {
                 dp[y][x] += solve(nx, ny);
            }
        }
    }
    return dp[y][x];
}
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j<= m; j++)
        {
            cin >> map[i][j];
        }
    }

    cout << solve(m,n);


}