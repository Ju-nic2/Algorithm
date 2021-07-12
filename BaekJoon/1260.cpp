#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
class Graph
{
private:
    vector<vector<int>> graph;
    vector<bool> visit;
    queue<int> q;
public:
    Graph(const int& size_=1)
        :graph(size_+1),visit(size_+1)
    {
        initialization(size_);
    }
    void initialization(const int& size_)
    {
        for(int i=0; i<=size_; i++)
        {
            visit[i] = false;
        }
    }
    void connect(const int a,const int b)
    {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    void sortPoint()
    {
        for(int i = 1; i<graph.size();i++)
        sort(graph[i].begin(),graph[i].end());
    }
    void dfs(int index)
    {
        visit[index] = true;
        cout << index << " " ;
        for(int i = 0;i<graph[index].size();i++)
        {
            
            int next = graph[index][i];
            if(!visit[next]) 
            {
                dfs(next);
                visit[next] = true;
            }
        }
    }
    void bfs(int index)
    {
        q.push(index);
        visit[index] = true;
        while(!q.empty())
        {
            int now = q.front();
            q.pop();
            cout << now << " ";
            for(int i = 0 ; i<graph[now].size();i++)
            {
                int next = graph[now][i];
                if(!visit[next]) 
                {
                    q.push(next);
                    visit[next] = true;
                }
            }
        }
    }

};
void input(Graph& graph,const int m)
{
    for(int i = 0; i<m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph.connect(a,b);
    }

}
int main()
{
    int n,m,start;
    cin >> n >> m >> start;
    Graph g(n);
    input(g,m);
    g.sortPoint();
    g.dfs(start);
    g.initialization(n);
    cout << endl;
    g.bfs(start);
}