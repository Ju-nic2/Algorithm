#include <iostream>
#include <vector>
using namespace std;
bool visit[501];
bool f1[501];
vector<int> f[501];
int count = 0;
void dfs(int index,int depth)
{
    visit[index] = true;
    if(depth >= 1)
    {
        if(!f1[index]) return;
    }
    for(auto next : f[index])
        if(!visit[next]){count++;dfs(next,depth+1);} 
}
int main()
{
    int n,m;
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int u,v;
        cin >> u >> v;
        f[u].push_back(v);
        f[v].push_back(u);
    }
    visit[1] = true;
    for(auto link : f[1])
    {
        f1[link] = true;
    }
    for(auto link : f[1])
    {
        if(!visit[link]){count++; dfs(link,0);}
    }
    cout << count;
}