#include <iostream>
#include <algorithm>
using namespace std;
int dp[1001]; // LIS from first
int dp2[1001]; // LIS from last
int arr[1001];

int main()
{
    int n;cin >> n;
    for(int i = 1; i<= n; i++) 
        cin >> arr[i];

    // LIS from first
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j < i; j++)
        {
            if(arr[i] > arr[j]) dp[i] = max(dp[i],dp[j]+1);
            
        }
        
    }
     // LIS from last
     for(int i = n; i >= 1; i--)
    {
        for(int j = n; j > i; j--)
        {
            if(arr[i] > arr[j]) dp2[i] = max(dp2[i],dp2[j]+1);         
        }
        
    }
    int ans = -1;
    for(int i = 1; i <= n; i++)
    {
        ans = max(ans,dp[i]+dp2[i]);
    }
    cout << ans+1;
    /*for(int i = 1; i<= n; i++) 
        cout << dp[i] << " ";
    cout << endl;
    for(int i = 1; i<= n; i++) 
        cout << dp2[i] << " ";*/
   
}
