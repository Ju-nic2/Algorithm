#include <iostream>
#include <string>
#include <vector>
using namespace std;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

class maze_search
{
private:
    vector<string> map;
    vector<vector<int>> visit;
public:
    maze_search(const int& x, const int& y)
    {
        for(int i = 0; i < y; i++)
        {
            visit.push_back(vector<int>(x,0));
        }
        visit[0][0] = 1;
    }
    void inputMap(const string str)
    {
        map.push_back(str);
    }

    void walkRoute(int x, int y)
    {
        
        for(int d = 0; d < 4; d++)
        {
            int nextx = x + dx[d];
            int nexty = y + dy[d];
            if(nextx >= 0 && nextx < map[0].size() && nexty >= 0 && nexty < map.size())
            {
                if(map[nexty][nextx] == '1' && visit[nexty][nextx] < 1){
                    visit[nexty][nextx] = visit[y][x] + 1;
                    walkRoute(nextx,nexty);
                }else if(map[nexty][nextx] == '1' && visit[nexty][nextx] > 1)
                {
                    if(visit[nexty][nextx] > visit[y][x]){
                        visit[nexty][nextx] = visit[y][x] + 1;
                        walkRoute(nextx,nexty);
                    }
                }
            }
        }
    }
    void getMinRoute(const int x, const int y)
    {
       cout << visit[y][x];
       
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    maze_search ms(m,n);
    string str;
    for(int i = 0; i < n; i ++){
        cin >> str;
        ms.inputMap(str);
    }

    ms.walkRoute(0,0);
    ms.getMinRoute(m-1,n-1);
}