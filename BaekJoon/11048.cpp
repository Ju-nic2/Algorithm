#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define X first
#define Y second
int map[1001][1001];
int ans[1001][1001];
bool visit[1001][1001];
int dx[3] = {1,0,1};
int dy[3] = {0,1,1};
int n,m;
void BFS(int startx,int starty)
{
    queue<pair<int,int>> q;
    q.push({startx,starty});
    visit[starty][startx] = true;
    ans[starty][startx] = map[starty][startx];
    while(!q.empty())
    {
        int nowx = q.front().X;
        int nowy = q.front().Y;
        q.pop();
        for(int i = 0; i < 3; i++)
        {
            int nextx = nowx + dx[i];
            int nexty = nowy + dy[i];
            if(nextx >= 1 && nextx <= m && nexty >= 1 && nexty <= n)
            {
                if(!visit[nexty][nextx])
                {
                    visit[nexty][nextx] = true;
                    q.push({nextx,nexty});
                }
                if(ans[nexty][nextx] < ans[nowy][nowx] + map[nexty][nextx])
                {
                    ans[nexty][nextx] = ans[nowy][nowx] + map[nexty][nextx];
                }
            }
        }
    }
    cout<<ans[n][m];
}
void dp()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            map[i][j] += max({map[i-1][j],map[i][j-1],map[i-1][j-1]});
        }
    }
    cout << map[n][m];
}
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
        }
    }
    //BFS(1,1);
    dp();
}