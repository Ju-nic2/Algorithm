#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> A(n);
    vector<int> B(n);
    vector<int> C(n);
    vector<int> D(n);
    for(int i = 0; i < n; i++)
    {
        int a,b,c,d; cin >> a >> b >> c >> d;
        A[i] = a; B[i] = b; C[i] = c; D[i] = d;
    }
    unordered_map<long long,int> AB;
    unordered_map<long long,int> CD;
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; j++)
        {
            if(AB.find(A[i]+A[j]) != AB.end()) AB[A[i]+B[j]]++;
            else AB[A[i]+B[j]] = 1;
            if(CD.find(C[i]+D[j]) != CD.end()) CD[C[i]+D[j]]++;
            else CD[C[i]+D[j]] = 1;
        }
    }
    long long count = 0;
    for(auto it : AB)
    {
        if(CD.find(0 - it.first) != CD.end())
        {
            count += CD[0 - it.first] * it.second;
        }
    }
    cout << count;
}
