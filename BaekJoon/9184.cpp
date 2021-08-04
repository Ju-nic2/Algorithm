#include <iostream>
#include <vector>
#include <string>
using namespace std;
int dp[101][101][101];
vector<string> ans;

int func(int a, int b, int c)
{
        if(a<=0||b<=0||c<=0) return 1;
        if(dp[a][b][c] != 0) return dp[a][b][c];
        if (a > 20 || b > 20 || c > 20) {
            return dp[a][b][c] = func(20, 20, 20);
        }
        if(dp[a][b][c] != 0) return dp[a][b][c];

        if (a < b && b < c) {
            return dp[a][b][c] = func(a, b, c - 1) + func(a, b - 1, c - 1) - func(a, b - 1, c);
        }
        return dp[a][b][c] =  func(a - 1, b, c) + func(a - 1, b - 1, c) + func(a - 1, b, c - 1) - func(a - 1, b - 1, c - 1);
}
void init()
{
 
    for(int i = 0; i <= 100; i++)
    {
        for(int j = 0; j <= 100; j++)
        {
            for(int k = 0; k <= 100; k++)
            {
                if(i <= 50 || j <= 50 || k <= 50) dp[i][j][k] = 1;
                else if(i > 70 || j > 70 || k > 70)  dp[i][j][k] = 1048576;
                else if(i < j  && j < k) dp[i][j][k] = dp[i][j][k-1] + dp[i][j-1][k-1] - dp[i][j-1][k];
                else  dp[i][j][k] = dp[i-1][j][k] + dp[i-1][j-1][k] + dp[i-1][j][k-1] - dp[i-1][j-1][k-1];

            }
        }
    }
}
void makeans(int a,int b,int c)
{
    string str;
    str.push_back('w');
    str.push_back('(');
    str.append(to_string(a));
    str.push_back(',');
    str.push_back(' ');
    str.append(to_string(b));
    str.push_back(',');
    str.push_back(' ');
    str.append(to_string(c));
    str.push_back(')');
    str.push_back(' ');
    str.push_back('=');
    str.push_back(' ');
    str.append(to_string(dp[50 + a][50 + b][50 + c]));
    ans.push_back(str);
}
void makeans2(int a,int b,int c)
{
    string str;
    str.push_back('w');
    str.push_back('(');
    str.append(to_string(a));
    str.push_back(',');
    str.push_back(' ');
    str.append(to_string(b));
    str.push_back(',');
    str.push_back(' ');
    str.append(to_string(c));
    str.push_back(')');
    str.push_back(' ');
    str.push_back('=');
    str.push_back(' ');
    str.append(to_string(func(a,b,c)));
    ans.push_back(str);
}
int main()
{
    //init();
    while(true)
    {
        int a,b,c; cin >> a >> b >> c;
        if(a == -1 && b == -1 && c == -1) break;
        makeans2(a,b,c);
    }
    for(int i = 0; i < ans.size(); i++)
    {
        cout << ans[i]<<endl;
    }
}