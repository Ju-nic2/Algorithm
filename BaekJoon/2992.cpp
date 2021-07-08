#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

string v;
string number;
vector<string> numbers;
bool first = true;
bool cmp(string a, string b)
{
    return stoi(a) < stoi(b);
}
void swap(char &a, char &b)
{
    char tmp = a;
    a = b;
    b = tmp;
}
void findNum(int index)
{
    if(index == v.size()-1)
    {
        if(stoi(v) > stoi(number)){
            numbers.push_back(v);
        }
        return;
    }
    for(int i = index; i<v.size(); i++)
    {
        swap(v[index],v[i]);
        findNum(index+1);
        swap(v[index],v[i]);
    }
}

int main()
{
    cin >> number;
    for(auto s : number){
        v.push_back(s);
    }
    sort(v.begin(), v.end());
    findNum(0);
    sort(numbers.begin(), numbers.end(),cmp);
    for(auto n : numbers){
        if(stoi(n) > stoi(number))
        {
            cout << n;
            return 0;
        }
    }
    cout << 0;
}