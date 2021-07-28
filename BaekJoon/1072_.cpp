#include <iostream>
using namespace std;
int main()
{
    long long x,y;
    long long z;
    cin >> x >> y;
    z = (100*y)/x;
    if(z >= 99) {cout << -1; return 0;}
    long long  low = 1; long long  high = x;
    while(low <= high)
    {
        long long mid = (low + high) / 2;
        long long newRatio = (100*(y+mid))/(x+mid);
        if(newRatio > z) high = mid - 1;
        else low = mid + 1;
    }
    cout << low;

}