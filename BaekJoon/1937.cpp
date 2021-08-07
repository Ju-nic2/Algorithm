#include <iostream>
#include <algorithm>
using namespace std;

int map[501][501];
int visit[501][501];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int n;
int f(int x, int y)
{
    if(visit[y][x] != 0) return visit[y][x];
    else{
        visit[y][x]++;
        for (int k = 0; k < 4; k++) {
            int ny = y + dy[k];
            int nx = x + dx[k];
            if (ny >= 1 && ny <= n && nx >= 1 && nx <= n && map[y][x] < map[ny][nx]) {
                 visit[y][x] = max(visit[y][x],f(nx, ny)+1);
            }
        }
    }
    return visit[y][x];
}

void solution()
{
    int max = 0;
     for(int i = 1; i<= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            int cur = f(i,j);
            if(cur > max) max = cur;
        }
    }
    cout << max;
}
int main()
{
    cin >> n;
   for(int i = 1; i<= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cin >> map[i][j];
        }
    }
    solution();
}
