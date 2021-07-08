#include <iostream>
#include <map>

using namespace std;

int main()
{
    int a,b,n;
    cin >> a >> b;
    map<int,int> A;
    map<int,int> B;
    int Set=0;
    for(int i = 0 ; i<a; i++)
    {
        cin >> n;
        A.insert({n,1});
    }
    for(int i = 0 ; i<b; i++)
    {
        cin >> n;
        B.insert({n,1});
    }
    for(auto a : A)
    {
        if(B.find(a.first) == B.end()) Set++;
    }
    for(auto b : B)
    {
        if(A.find(b.first) == A.end()) Set++;
    }
    cout << Set;
}