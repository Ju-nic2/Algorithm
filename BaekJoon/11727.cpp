#include <iostream>
using namespace std;
int tiling[1001];
int main()
{
    int n; cin >> n;
    tiling[1] = 1;
    tiling[2] = 3;
    for(int i = 3; i <= n; i++)
    {
        tiling[i] = (tiling[i-1] + 2*tiling[i-2])%10007;
    }
    cout << tiling[n];
}