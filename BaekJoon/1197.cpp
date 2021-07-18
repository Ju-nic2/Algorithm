#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class Edge{
public:
    int u;
    int v;
    int w;
    Edge(){}
    Edge(const int u_, const int v_, const int w_)
        :u(u_),v(v_),w(w_)
    {}
};
const int nm = 10001;
int set[nm];
int rnk[nm];
void init(int n)
{
    for(int i = 0; i < n; i++)
    {
        set[i] = i;
        rnk[i] = 1;
    }
}

int find(int x)
{
    if(x == set[x]) return x;
    return set[x] = find(set[x]);
}
bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}
void Union(int x, int y)
{
    int u = find(x);
    int v = find(y);

    if(u == v) return;
    if(rnk[u] > rnk[v]) set[v] = u;
    else
    {
        set[u] = v;
        if(rnk[u] == rnk[v]) rnk[u]++;
    }
}

int main()
{
    int V,E;
    cin >> V >> E;
    init(V);
    vector<Edge> e(E);
    for(int i = 0; i < E; i++)
    {
        int u,v,w; cin >> u >> v >> w;
        e[i].u=u; e[i].v=v; e[i].w=w;
    }
    sort(e.begin(), e.end(),cmp);

    int sum = 0;
    int cnt = 0;
    for(int i = 0; i < E; i++)
    {
        if(cnt == V-1) break;
        if(find(e[i].u) != find(e[i].v)) {
            Union(e[i].u,e[i].v);
            cnt++;
            sum+=e[i].w;
        }
    }
    cout << sum;
}