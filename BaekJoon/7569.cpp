#include <iostream>
#include <queue>
class Point
{
public:
    int x;
    int y;
    int z;
    Point(const int x_, const int y_, const int z_)
    {
        x=x_;y=y_;z=z_;
    }
};
using namespace std;
          //h   /n   /m
int tomato[101][101][101];
int day[101][101][101];
bool visit[101][101][101];
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int dz[2] = {-1,1};
int main()
{
    queue<Point> q;
    int n,m,h;
    cin >> m >> n >> h;
    int t;
    for(int i = 0; i < h; i ++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int z = 0; z < m; z++)
            {
                cin >> t;
                tomato[i][j][z] = t;
            }
        }
    }

    for(int i = 0; i < h; i ++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int z = 0; z < m; z++)
            {
                if(tomato[i][j][z] == 1){
                    q.push(Point(z,j,i));
                    day[i][j][z]++;
                }
            }
        }
    }
    visit[q.front().z][q.front().y][q.front().x] = true;
    while(!q.empty())
    {
        int x = q.front().x;
        int y = q.front().y;
        int z = q.front().z;
        q.pop();     
            for(int d = 0; d < 4; d++)
            {
                int nextx = x + dx[d];
                int nexty = y + dy[d];
                int nextz = z;
                if(0 <= nextx && nextx < m && 0 <= nexty && nexty < n)
                {
                    if(tomato[nextz][nexty][nextx] == 0 && visit[nextz][nexty][nextx] == 0)
                    {
                        day[nextz][nexty][nextx] = day[z][y][x] + 1;
                        visit[nextz][nexty][nextx] = 1;
                        tomato[nextz][nexty][nextx] = 1;
                        q.push(Point(nextx,nexty,nextz));
                    }
                }
            }
            for(int d = 0; d < 2; d++)
            {
                int nextx = x;
                int nexty = y; 
                int nextz = z +dz[d];
                if(0 <= nextz && nextz < h)
                {
                     if(tomato[nextz][nexty][nextx] == 0 && visit[nextz][nexty][nextx] == 0)
                    {
                        day[nextz][nexty][nextx] = day[z][y][x] + 1;
                        visit[nextz][nexty][nextx] = 1;
                        tomato[nextz][nexty][nextx] = 1;
                        q.push(Point(nextx,nexty,nextz));
                    }
                }
            }           
    }
    int maxday = 0;
    for(int i = 0; i < h; i ++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int z = 0; z < m; z++)
            {
                if(tomato[i][j][z] == 0 && day[i][j][z] == 0){
                    cout << -1; return 0;}
                if(maxday < day[i][j][z]) maxday = day[i][j][z];
               
            }

        }

    }
    cout << maxday-1;
}