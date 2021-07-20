#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip> 
using namespace std;
#define P pair<int,int>
#define X second
#define Y first
class edge
{
public:
    int u;
    int v;
    double w;
    edge(const int u_,const int v_,const double w_)
    {u=u_;v=v_;w=w_;}
};
int set[1001];
int rnk[1001];
double getDistance(const P& a, const P& b)
{
    double xd = pow((a.X-b.X),2);
    double yd = pow((a.Y-b.Y),2);
    return sqrt(xd+yd);
}
int find(const int& x)
{
    if(x == set[x])return x;
    return set[x] = find(set[x]);
}
void Union(const int a, const int b)
{
    int u = find(a);
    int v = find(b);
    if(u==v) return;
    if(rnk[u] > rnk[v]) set[v] = u;
    else
    {
        set[u] = v;
        if(rnk[u] == rnk[v]) rnk[u]++;
    }
}
bool cmp(const edge a, const edge b)
{
    return a.w<b.w;
}
int main()
{
    int n,m; cin >> n >> m;
    vector<P> points(n+1);
    vector<P> connected;
    vector<edge> edges;
    for(int i = 1; i <= n; i++)
    {
        set[i] = i;
        rnk[i] = 1;
    }
    for(int i = 1; i <= n; i++)
    {
        int x,y; cin>>x>>y;
        points[i].X=x; points[i].Y=y;
    }
    for(int i = 0; i < m; i++)
    {
        int a,b; cin >>a >> b;
        connected.push_back({a,b});
    }

    for(int i = 0; i < m; i++)
    {
        if(find(connected[i].first) != find(connected[i].second))
            Union(connected[i].first,connected[i].second);
    }
    for(int i = 1; i <n; i++)
    {
        for(int j = i+1; j <= n; j++)
        {
            edges.push_back(edge(i,j,getDistance(points[i],points[j])));
        }
    }

    sort(edges.begin(), edges.end(), cmp);
    double sum = 0;
    int count = 0;
    for(int i = 0; i < edges.size(); i++)
    {
        if(count == n-1-m) break;
        if(find(edges[i].u) != find(edges[i].v)) 
        {
            Union(edges[i].u,edges[i].v);
            count++;
            sum+=edges[i].w;
        }
    }
    cout << fixed << setprecision(2) << sum;

}


