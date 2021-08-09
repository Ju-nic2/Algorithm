#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> dp;
    dp.push_back(-1);
    int n; cin >> n;
    for(int i = 0; i < n; i++)
    {
        int a; cin >> a;
        if(dp.back() < a) dp.push_back(a);
        else{
            auto it = lower_bound(dp.begin(), dp.end(),a);
            *it = a;
        }
    }
    cout << dp.size() -1;   
}