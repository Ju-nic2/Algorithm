#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string str;
    vector<string> subpixs;
    cin>>str;
    for(int i = 0; i<str.size(); i++)
    {
        string tmp = str.substr(i,str.size());
        subpixs.push_back(tmp); 
    }
    sort(subpixs.begin(), subpixs.end());

    for(auto &str : subpixs)
        cout << str <<'\n';


}