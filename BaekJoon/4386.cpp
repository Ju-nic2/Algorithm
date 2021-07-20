#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip> 
using namespace std;
#define P pair<double,double>
#define X second
#define Y first
class edge
{
public:
    int u;
    int v;
    double w;
    edge(const double& u_,const double& v_,const double& w_)
    {u=u_;v=v_;w=w_;}
};
int set[101];
int rnk[101];
vector<P> stars(101);
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
double getDistance(const P& a, const P& b)
{
    double xd = pow((a.X-b.X),2);
    double yd = pow((a.Y-b.Y),2);
    return sqrt(xd+yd);
}
void getInput(const int n)
{
    for(int i = 1; i <= n; i++)
    {
        double x,y;cin>>x>>y;
        stars[i].X=x;stars[i].Y=y;
 
    }
}
bool cmp(const edge a, const edge b)
{
    return a.w<b.w;
}
void solution(const int n)
{
    for(int i = 1; i < n; i++)
    {
        for(int j = i+1; j<=n; j++)
        {
            e.push_back(edge(i,j,getDistance(stars[i],stars[j])));
        }
    }
    init(n);
    int count = 0;
    double sum = 0;
    sort(e.begin(),e.end(),cmp);
    for(int i = 0; i < e.size(); i++)
    {
        if(count == n-1) break;
        if(find(e[i].u) != find(e[i].v)) 
        {
            Union(e[i].u,e[i].v);
            count++;
            sum+=e[i].w;
        }
    }
    cout << fixed << setprecision(2) << sum;


}
int main()
{
    int n;
    cin >>n;
    getInput(n);
    solution(n);
}
