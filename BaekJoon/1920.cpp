#include <unordered_map>
#include <iostream>
using namespace std;

int main()
{
    unordered_map<int,int> h;
    int n,m;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int data;
        cin >> data;
        h[data] = 0;
    }
    cin >> m;
    for(int i = 0; i < m; i++)
    {
        int data;
        cin >> data;
       if(h.find(data) != h.end()) cout << 1<<'\n';
       else cout << 0 << '\n';
    }
}