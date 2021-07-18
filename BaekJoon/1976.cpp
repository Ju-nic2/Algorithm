#include <iostream>
#include <iostream>
using namespace std;
const int mn = 201;
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
    int n, m;
    cin >> n >> m;
    init(n);
    
    int t;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> t;
            if(j > i && t == 1) Union(i,j);
        }
    }
    int sum = 0;
    int city;
    for(int i = 0; i < m; i++)
    {
        cin >> city;
        sum += find(city-1);
    }
    if(find(city-1)*m == sum) cout << "YES";
    else cout << "NO";
}