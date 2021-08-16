#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
bool cmp(int a, int b)
{
    string as = to_string(a);
    string bs = to_string(b);
    return as+bs > bs+as;
    
}
string solution(vector<int> numbers) {
    string answer = "";
    sort(numbers.begin(),numbers.end(),cmp);
    for(auto e : numbers)
    {
        string tmp = to_string(e);
        for(int i = 0; i < tmp.length(); i++)
            answer.push_back(tmp[i]);
    }
    if(answer[0] == '0') return "0";
    return answer;
}