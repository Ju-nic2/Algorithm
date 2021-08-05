#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class BigNum
{
public:
    string data ;
public:
    BigNum(){};
    BigNum(const string num)
    {
        data = num;
    }
    //Don't receieve parameter reference ..
    //DP need origin data in other operation 
    BigNum operator + (BigNum operand)
    {
        long long sum = 0;
        string tmp = data;
        string result;
         while (!tmp.empty() || !operand.data.empty() || sum)
        {
            if (!tmp.empty())
            {
                sum += tmp.back() - '0';
                tmp.pop_back();
            }
            if (!operand.data.empty())
            {
                sum += operand.data.back() - '0';
                operand.data.pop_back();
            }
            result.push_back((sum % 10) + '0');
            sum /= 10;
        }
        reverse(result.begin(), result.end());
        return BigNum(result);
    }
      void operator = (int n)
      {
           data = to_string(n);
      }
      void operator = (const BigNum operand)
      {
          
          data = operand.data;
      }

      friend ostream& operator << (ostream & out, const BigNum num)
      {
          out << num.data;
          return out;
      }

    
};
BigNum dp[101][101];

void nCk(int n, int k)
{
    for(int i = 0; i <= n; i++){
        dp[i][0] = 1;
        if(i <= k) dp[i][i] = 1;
    }
    
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= k; j++)
        {         
            dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
        }
    }
    cout << dp[n][k].data;
}
int main()
{
    int n,k; cin >> n >> k;
    nCk(n,k);
}