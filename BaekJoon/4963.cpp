#include <iostream>
#include <vector>
using namespace std;

int dx[8] = {1,0,-1,0,1,-1,1,-1};
int dy[8] = {0,1,0,-1,1,-1,-1,1};

class Map
{
private:
    vector<vector<int>> map;
    vector<vector<bool>> visit;
    int landCount;
public:
    Map(const int& width, const int& hight)
    {
        for(int i = 0; i < hight; i++){
            map.push_back(vector<int>(width,0));
            visit.push_back(vector<bool>(width,false));
        }
       
        landCount = 0;
    }
    void input(const int x, const int y, const int data)
    {
        map[y][x] = data;
    }
    void dfs(const int x, const int y)
    {
        visit[y][x] = true;
        for(int i = 0; i < 8; i++)
        {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            if(nextX >= 0 && nextX < map[0].size() && nextY >= 0 && nextY < map.size())
            {
                if(!visit[nextY][nextX] && map[nextY][nextX] == 1) dfs(nextX,nextY);
            }
        }
    }
    void findLand()
    {
       for(int i = 0; i < map.size(); i++)
       {
           for(int j = 0; j < map[i].size(); j++)
           {
               if(!visit[i][j] && map[i][j] == 1){landCount++; dfs(j,i);}
           }
       }
       cout << landCount << endl;
    }

};

int main()
{
    vector<Map> m;
    int index = 0;
    while(true)
    {
        int h,w,t;
        cin >> w >> h;
        if(h == 0 && w == 0) break;
        m.push_back(Map(w,h));
      
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                cin >> t;
                m[index].input(j,i,t);
            }
        }
        
        index++;
    }
    for(auto map : m)
        map.findLand();
}