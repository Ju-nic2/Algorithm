#include <iostream>
#include <vector>
using namespace std;
int f[41];
int main()
{
    vector<int> vip;
    int n,m;
    cin >> n;
    cin >> m;
    f[0] = 1;
    f[1] = 1;
    f[2] = 2;
   
    for(int i = 3; i <= n; i++) f[i] = f[i-1] + f[i-2];
    if(m == 0)
    {
        cout << f[n];
        return 0;
    }
    for(int i = 0; i < m; i++)
    {
        int num; cin >> num;
        vip.push_back(num);
    }

    int sum = f[vip[0] - 1];
    for(int i = 1; i <= vip.size() - 1; i++)
    {
        sum *= f[vip[i] - vip[i-1] - 1];
    }
    sum *= f[n - vip[vip.size()-1]];
    cout << sum; 
}