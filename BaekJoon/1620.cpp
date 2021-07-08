#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
bool myIsDisgit(string str)
{
    for(auto c : str)
    {
        if(!isdigit(c)) return false;
    }
    return true;
}
int main()
{
    int n,m;
    unordered_map<string,int> name;
    unordered_map<int,string> number;
    vector<string> ans;
    cin >> n >> m;
    for(int i = 0; i< n; i++)
    {
        string tmp;
        cin >> tmp;
        name[tmp] = i+1;
        number[i+1] = tmp;
    }
    for(int i = 0; i < m; i++)
    {
        string tmp;
        cin >> tmp;
        if(myIsDisgit(tmp)) ans.push_back(number[stoi(tmp)]);
        else ans.push_back(to_string(name[tmp]));
    }
    for(auto a : ans)
        cout << a << '\n';

}