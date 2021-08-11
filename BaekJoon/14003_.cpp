#include <iostream>
#include <algorithm>
using namespace std;
int dp[1000001]; // LIS from first
int lis[1000001];
int arr[1000001];

int main()
{
    int n;cin >> n;
    for(int i = 0; i< n; i++) 
        cin >> arr[i];

    // LIS from first
    int l = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(arr[i] > arr[j]) 
            {
                dp[i] = max(dp[i],dp[j]+1);
                if(lis[dp[j]] == 0)
                    lis[dp[j]] = arr[j];
                else if(lis[dp[i]] > arr[j])
                    lis[dp[j]] = arr[j];
            }
        }
        l = max(l,dp[i]);
        lis[dp[i]] = arr[i];
    }
    cout << l+1<<endl;
    for(int i = 0; i <= l; i++) 
        cout << lis[i] << " ";
 
}
