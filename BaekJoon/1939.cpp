#include <iostream>
#include <vector>
#include <queue>
#define P pair<int,int>
#define W first;
#define V second
using namespace std;

bool findRoute(vector<vector<P>> &map,vector<bool>& visit, const int start, const int limit, const int endpoint)
{
    queue<int> q;
    visit[start] = true;
    q.push(start);
    while(!q.empty())
    {
        int now = q.front();
        if(now == endpoint) return true;
        q.pop();
        for(auto next : map[now])
        {
            int next_v = next.V;
            int cost = next.W;
            if(cost >= limit && !visit[next_v])
            {
                visit[next_v] = true;
                q.push(next_v);
            }
        }
    }
    return false;
}
int main()
{
    int n,m;
    cin >> n >> m;
    vector<vector<P>> map(n+1);
    int max = 0;
    for(int i = 0; i < m; i++)
    {
        int u,v,w; cin >> u >> v >> w;
        map[u].push_back({w,v});
        map[v].push_back({w,u});
        if(max < w) max = w;
    }
    int start,end; cin >> start >> end;
    int low = 1; int high = max;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        vector<bool> visit(n+1,false);
        if(findRoute(map,visit,start,mid,end)) low = mid + 1;
        else high = mid - 1;
    }
    cout << low - 1;
}