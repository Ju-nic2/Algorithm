#include <iostream>
#include <string>
using namespace std;
int gcd(const int&a, const int& b)
{
    return b ? gcd(b,a%b) : a;
}

bool myfind(string &s1, string &s2)
{ 
    int GCD = gcd(s1.size(),s2.size()); 
    string tmp1 = s1;
    string tmp2 = s2;
    for(int i = 0; i<tmp2.size()/GCD-1; i++)
    {
        s1.append(tmp1);
    }
    for(int i = 0; i<tmp1.size()/GCD-1; i++)
    {       
        s2.append(tmp2);
    }
    if(s1 == s2)
        return true;
    else
        return false;
}


int main()
{
    string s1,s2;
    cin >> s1;
    cin >> s2;
    if(s1.size() == s2.size()){
        if(s1 == s2) cout << "1";
        else cout << 0;
    }else{
        cout << myfind(s1,s2);
    }

}
