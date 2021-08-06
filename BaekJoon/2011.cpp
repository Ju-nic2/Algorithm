#include <iostream>
#include <string>
#include <vector>
using namespace std;
int extractNum(const string &str,int i)
{
    int num = -1;
    if(i > 0)
        num = (str[i-1] - '0') * 10 + (str[i] - '0');
    return num;
}

void getNum(vector<int> &decode, string &str)
{
    for(int i = 0; i <str.size(); i++)
    {
        if(str[i]-'0' != 0)
            decode[i+1] = decode[i] % 1000000;
        if(extractNum(str,i) >= 10 && extractNum(str,i) <= 26)
            decode[i+1] = (decode[i+1] + decode[i-1]) % 1000000;
    }
    cout << decode[str.size()];
}
int main()
{
    string pw; cin >> pw;
    if(pw[0] == '0' || pw.size() == 0)
    {
   
        cout << 0 ;
        return 0;
    }
    vector<int> decode(pw.size()+1,0);
    decode[0] = 1;
    getNum(decode,pw);
}