#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int arr[1000001];
int dp[1000001];
int index[1000001];
int main()
{
    int n; cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int l = 0;
    for(int i = 0; i < n; i++)
    {
        auto it = lower_bound(dp,dp+l,arr[i]);
        if(*it == 0) l++;
        //save arr[i] in LIS 
        *it = arr[i];

        //save index in LIS
        index[i] = it-dp;
    }

    for(int i = 0; i < n; i++)
        cout << index[i] << " ";
    cout << endl;
     for(int i = 0; i < l; i++)
        cout << dp[i] << " ";
    cout << endl;

    cout << l << '\n';
    vector<int> ans;
    for(int i = n-1; i>=0; i--)
    {
        if(index[i] == l-1){
            ans.push_back(arr[i]);
            l--;
        }
    }
    reverse(ans.begin(), ans.end());
    for(auto a : ans)
        cout << a << " ";
}