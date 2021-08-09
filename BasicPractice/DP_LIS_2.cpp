#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int dp2[100001];
int main()
{
    //1. use Vector Size()
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
    //2. use dp arr
    int l = 0;
    for(int i = 0; i < n; i++)
    {
        int a; cin >> a;
        for(int i = 0; i < n; i++)
        {
            int a; cin >> a;
            auto it = lower_bound(dp2,dp2+l,a);
            if(*it==0) l++;
            *it = a;
        }
    }
    cout << dp.size() -1;   
    cout << l;  
}