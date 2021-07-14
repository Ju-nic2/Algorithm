#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Maze_Search
{
private:
    vector<string> maze;
    queue<pair<int,int>> q;
    pair<int,int> end_point;
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,1,0,-1};
    int **visit;
    int **check;

public:
    Maze_Search(const int& N=0, const int& M=0)
    {
        end_point.first = M-1;
        end_point.second = N-1;
        visit = (int**)malloc(sizeof(int*)*N);
        check = (int**)malloc(sizeof(int*)*N);

        for(int i = 0; i<N; i++)
        {
            check[i] = (int*)malloc(sizeof(int)*M);
            visit[i] = (int*)malloc(sizeof(int)*M);
        }
        initializecon(N,M);
    }

    void initializecon(const int& N, const int& M)
    {
        for(int i = 0; i<N; i++)
        {
            for(int j = 0; j<M; j++)
            {
                check[i][j] = 0;
                visit[i][j] = 0;
            }

        }
    }


    void input(const string& str)
    {
        maze.push_back(str);
    }

    void BFS(int x, int y)
    {
        visit[y][x] = 1;
        q.push(make_pair(x,y));

        while(!q.empty())
        {
            int x = q.front().first;
            int y = q.front().second;

            q.pop();
            for(int i = 0; i<4; i++)
            {
                int next_x = x + dx[i];
			    int next_y = y + dy[i];
                if (0 <= next_x && next_x <= end_point.first && 0 <= next_y && next_y <= end_point.second ) 
                {
				    if (maze[next_y][next_x] == '1' && visit[next_y][next_x] == 0)
				    {
					    check[next_y][next_x] = check[y][x] + 1;
					    visit[next_y][next_x] = 1;
					    q.push(make_pair(next_x, next_y)); // 큐에 데이터 밀어넣기
				    }
                }
            }
        }

    }

    void findRoute()
    {
        BFS(0,0);
    }
    void getMoveCount()
    {
      cout << check[end_point.second][end_point.first] + 1<< endl;
    }
};

int main()
{
    int N,M;
    cin >> N >> M;
    Maze_Search ms(N,M);
    string tmp;
    for(int i = 0; i<N; i++)
    {
        cin >> tmp;
        ms.input(tmp);
    }
    ms.findRoute();
    ms.getMoveCount();
}