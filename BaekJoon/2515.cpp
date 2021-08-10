#include <iostream>
#include <vector>
#include <algorithm>
#define H first
#define C second
using namespace std;
int dp[300001];

bool cmp(const pair<int,int> &a, const pair<int,int> &b)
{
    if(a.H == b.H)
    {
        return a.C > b.C;
    }else{
        return a.H < b.H;
    }
}

int main()
{
    vector<pair<int,int>> pictures;
    int n,s; cin >> n >> s;
    for(int i = 0; i < n; i++)
    {
        int h,c; cin >> h >> c;
        pictures.push_back({h,c});
    }
    sort(pictures.begin(),pictures.end(),cmp);

    dp[0] = pictures[0].C;
    int index = 0;
    int ans = -1;
    for(int i = 1; i < n; i++)
    {
        for(int j = index; pictures[j].H + s <= pictures[i].H; j++)
        {
            if(dp[i] < dp[j] + pictures[i].C)
            {
                index = j;
                dp[i] = dp[j] + pictures[i].C;
            }
        }
        dp[i] = max(dp[i],pictures[i].C);
        ans = max(ans,dp[i]);
    }
    cout << max(dp[0],ans);
}