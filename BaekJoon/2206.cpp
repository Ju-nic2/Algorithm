#include <iostream>
#include <vector>
#include <string>
#include <queue>
//비가중치 행렬 최단경로 -> BFS
using namespace std;
class Status
{
public:
    int x;
    int y;
    bool wall;
    Status(const int x_, const int y_, const bool wall_)
    {x=x_;y=y_;wall=wall_;}
};
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int visit[2][1000][1000];
vector<string> map;
queue<Status> q;

int Move(const int x, const int y)
{
    visit[0][y][x] = 1;
    q.push(Status(x,y,0));
    while(!q.empty())
    {
        int x = q.front().x;
        int y = q.front().y;
        bool block = q.front().wall;
        cout << y << " " << x << " " <<block << endl;
        if(x == map[0].size()-1 && y == map.size()-1) return visit[block][y][x];
        q.pop();

        for(int i = 0; i < 4; i++)
        {
            int nextx = x + dx[i];
            int nexty = y + dy[i];
            if(nextx >= 0 && nextx < map[0].size() && nexty >= 0 && nexty < map.size())
            {
                if(visit[block][nexty][nextx] != 0) continue;
                if(map[nexty][nextx] == '0'){ 
                    q.push(Status(nextx,nexty,block));
                    visit[block][nexty][nextx] = visit[block][y][x] + 1;
                }
                else if(map[nexty][nextx] == '1')
                {
                    if(!block)
                    {
                        visit[!block][nexty][nextx] = visit[block][y][x] + 1;
                        q.push(Status(nextx,nexty,!block));
                    }
                }

            }
        }

    }
    return -1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    string str;
    for(int i = 0; i < n; i++)
    {
        cin>>str;
        map.push_back(str);
    }
    cout << Move(0,0) << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
    {  
        cout << visit[1][i][j] << " ";
    }
    cout << endl;
    }

}