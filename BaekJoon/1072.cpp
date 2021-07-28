#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long long x; long long y;
    long long z;
    cin >> x >> y;
    z = (y*100/x);
    if(z >= 99) {cout << -1; return 0;}
    long long numerator = (long long)(z*x + x - 100*y);
    long long denominator = (long long)(99 - z);
    (numerator%denominator == 0 ) ? cout <<  numerator/denominator << endl : cout << numerator/denominator+1;
    
}