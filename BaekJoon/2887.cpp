#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define P pair<int,int>
#define L first
#define N second

class edge
{
public:
    int u;
    int v;
    int w;
    edge(const int& u_,const int& v_,const int& w_)
    {u=u_;v=v_;w=w_;}
};
int set[100001];
int rnk[100001];
vector<P> planets[3];
vector<edge> e;
void init(int n)
{
    for(int i=1;i<=n; i++)
    {
        set[i] = i;
        rnk[i] = 1;
    }
}
int find(const int x)
{
    if(x==set[x])return x;
    return set[x] = find(set[x]);
}

void Union(const int u, const int v)
{
    int U = find(u);
    int V = find(v);
    if(U==V) return;
    if(rnk[U] > rnk[V]) set[V] = U;
    else
    {
        set[U] = V;
        if(rnk[U] == rnk[V])rnk[U]++;
    }
}
int getCost(const P& a, const P& b)
{
    return abs(a.L-b.L);
}
bool cmp(const P a, const P b)
{
    return a.L < b.L;
}
bool cmp2(const edge a, const edge b)
{
    return a.w<b.w;
}
void getInput(const int n)
{
    for(int i = 1; i <= n; i++)
    {
        int x,y,z; cin>>x>>y>>z;
        planets[0].push_back({x,i});
        planets[1].push_back({y,i});
        planets[2].push_back({z,i});
    }
}
void solution(const int n)
{
    sort(planets[0].begin(),planets[0].end(),cmp);
    sort(planets[1].begin(),planets[1].end(),cmp);
    sort(planets[2].begin(),planets[2].end(),cmp);
    init(n);
    for(int i = 1; i < n; i++)
    {
         e.push_back(edge(planets[0][i-1].N,planets[0][i].N, getCost(planets[0][i-1],planets[0][i])));
         e.push_back(edge(planets[1][i-1].N,planets[1][i].N, getCost(planets[1][i-1],planets[1][i])));
         e.push_back(edge(planets[2][i-1].N,planets[2][i].N, getCost(planets[2][i-1],planets[2][i])));
    }
    sort(e.begin(),e.end(),cmp2);
    int count = 0;
    int sum = 0;
    for(int i = 0; i < e.size(); i++)
    {
        if(count == n-1) break;
        int u = e[i].u;
        int v = e[i].v;
        if(find(u) != find(v)) 
        {
            Union(u,v);
            count++;
            sum+=e[i].w;
        }
    }
    cout << sum;

}
int main()
{
    int n;
    cin >>n;
    getInput(n);
    solution(n);
}