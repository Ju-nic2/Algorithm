#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
   vector<vector<int>> graph;
   vector<bool> visit;
   int links;
public:
    Graph(const int& points)
    {
        links=0;
        visit.resize(points,false);
        for(int i = 0; i<points; i++)
            graph.push_back(vector<int>());
    }
    void input(const int u, const int v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    void dfs(int p)
    {
        visit[p] = true;
        for(int i = 0; i<graph[p].size(); i++)
        {
            if(!visit[graph[p][i]]) dfs(graph[p][i]);
        }
    }
    void findLinked()
    {
        for(int i = 0; i<graph.size(); i++)
        {
            if(!visit[i] )
            {
                dfs(i);
                links++;
            }
        }
        cout << links;
    }
};

int main()
{
    int n,m;
    cin >> n >> m;
    Graph g(n);
    for(int i = 0; i < m; i++)
    {
        int u,v;
        cin >> u >>v;
        g.input(u-1,v-1);
    }
    g.findLinked();
}