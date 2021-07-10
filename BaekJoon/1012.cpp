#include <iostream>
#include <vector>

using namespace std;
int dx[4] = {0,-1,0,1};
int dy[4] = {1,0,-1,0};

class BeaCuField{
private:
    vector<vector<int>> map;
    vector<vector<bool>> visit;
    int count;
public:
    BeaCuField(){}
    void initialization(const int x, const int y)
    {
        for(int i = 0; i < y; i++){

            map.push_back(vector<int>(x,0));
            visit.push_back(vector<bool>(x,false));
        }
        count = 0;
    }
    void input(const int x, const int y)
    {
        map[y][x] = 1;
    }
    void dfs(int x, int y)
    {
        visit[y][x] = true;
        for(int d = 0; d < 4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx >= 0 && nx < map[0].size() && ny >= 0 && ny < map.size())
            {
                if(!visit[ny][nx] && map[ny][nx] == 1) {
                    dfs(nx,ny);
                }
            }
        }
    }

    void findBaechu()
    {
        for(int i = 0; i < map.size(); i++)
        {
            for(int j = 0; j < map[0].size(); j++)
            {
                if(map[i][j] == 1 && !visit[i][j])
                {
                    count++;
                    dfs(j,i);
                }
            }
        }
        return;
    }
    void getCount()
    {
        cout << count << endl;
    }

};

int main()
{
    int Tcase;
    cin >> Tcase;
    vector<BeaCuField> fdv(Tcase);
    for(int t = 0; t < Tcase; t++)
    {
        int M,N,K;
        cin >> M >>N >>K;
        fdv[t].initialization(M,N);
        for(int k = 0; k < K; k++)
        {
            int x,y;
            cin>> x >> y;
            fdv[t].input(x,y);
        }
    }
     for(int t = 0; t < Tcase; t++)
    {
        fdv[t].findBaechu();
        fdv[t].getCount();
    }
}