#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
int set[200202];
int rnk[200202];
void init(int n)
{
    for(int i=1;i<=n; i++)
    {
        set[i] = i;
        rnk[i] = 1;
    }
}
int find(int p)
{
    while(p != set[p])
        p=set[p];
    return p;
}

int Union(const int u, const int v)
{
    int U = find(u);
    int V = find(v);
    if(U==V) return rnk[U];
    if(rnk[U] > rnk[V]){
        set[V] = U;
        rnk[U] += rnk[V];
        return rnk[U];
    }
    else if(rnk[V] < rnk[U])
    {
        set[U] = V;
        rnk[V] += rnk[U];
        return rnk[V];
    }else
    {
        set[V] = U;
        rnk[U] += rnk[V];
        return rnk[U];
    }
}
int main()
{
    int Tcase; cin >> Tcase;
    vector<int> answer;
    for(int t = 0; t < Tcase; t++)
    {
        int n; cin >> n;
        int index = 1;
        init(n*2);
        unordered_map<string,int> f;
        for(int i = 0; i < n; i++){
            string name1,name2; cin >> name1 >> name2;
            if(f.find(name1) == f.end()){f[name1] = index; index++;}
            if(f.find(name2) == f.end()){f[name2] = index; index++;}
            int u = f[name1];
            int v = f[name2];
            answer.push_back(Union(u,v));
        }
    }
    for(auto a : answer)
        cout << a << '\n';
}