#include <iostream>
#include <vector>
using namespace std;
class Edge{
public:
    int u;
    int v;
    Edge(){}
    Edge(const int u_, const int v_)
        :u(u_),v(v_)
    {}
};
const int nm = 500001;
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
    int n,m;
    cin >> n >> m;
    init(n);
    vector<Edge> e(m);
    for(int i = 0; i < m ; i++)
    {
        int u, v; cin >> u >> v;
        e[i].u=u; e[i].v=v;
    }
    for(int i = 0; i < m ; i++)
    {
        if(find(e[i].u) == find(e[i].v))
        {
            cout << i+1 << endl;
            return 0;
        }
        Union(e[i].u, e[i].v);
    }
    cout << 0 << endl;
}