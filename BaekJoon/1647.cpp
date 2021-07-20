#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge{
    int u;
    int v;
    int w;
};
edge arr[10000000];
int set[10000001];
int rnk[10000001];
void init(int n)
{
    for(int i = 0; i <= n; i++)
    {
        set[i] = i;
        rnk[i] = 1;
    }
}
int find(const int x)
{
    if(x == set[x]) return x;
    else return set[x] = find(set[x]);
}

void Union(int u, int v)
{
    int a = find(u);
    int b = find(v);
    if(a==b) return;

    if(rnk[a] > rnk[b])
    {
        set[b] = a;
    }else{
        set[a] = b;
        if(rnk[a] == rnk[b]) rnk[a]++;
    }
}
bool cmp(const edge a, const edge b){return a.w < b.w;}
int main()
{
    int n,m; cin >> n >> m;
    init(n);
    for(int i = 0; i < m; i++)
    {
        int u,v,w; cin >> u >> v >> w;
        arr[i].u=u;arr[i].v=v;arr[i].w=w;
    }
    sort(arr, arr +m, cmp);
    int sum = 0;
    int count = 0;
    int last;
    for(int i = 0; i < m; i++)
    {
        if(count == n-1) break;
        if(find(arr[i].u) != find(arr[i].v)) 
        {
            Union(arr[i].u,arr[i].v);
            count++;
            sum+=arr[i].w;
            last=arr[i].w;
        }
    }
    cout << sum-last;


}