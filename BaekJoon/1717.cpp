#include <iostream>
using namespace std;
const int mn = 1000001;
int set[mn];
int ran[mn];
void init(int n)
{
    for(int i = 1; i <= n; i++)
    {
        set[i] = i;
        ran[i] = 1;
    }
}
int find(int n)
{
    if(set[n] == n) return n;
    return set[n] = find(set[n]);
}
void Union(int x, int y)
{
     int u = find(x);
     int v = find(y);
     if(u==v) return;

     if(ran[u] > ran[v])
     {
         set[v] = u;
     } else{
         set[u] = v;
         if(ran[u] == ran[v])
            ran[u]++;
     }
}

int main()
{
    ios::sync_with_stdio(false);    cin.tie(NULL);
    int n , m; cin >> n >> m;
    init(n);
    for(int i = 0; i < m; i++)
    {
        int opt,u,v; cin >>opt >> u >> v;
        switch(opt)
        {
            case 0:
                Union(u,v);break;
            case 1:
                cout << ((find(u) == find(v)) ? "YES" : "NO")<< '\n';break;

        }
    }

}