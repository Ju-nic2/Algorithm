#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
void parseExpressoin(vector<char> &ops,vector<long long> &nums, string expression)
{
    string str;
    for(int i = 0; i < expression.size(); i++)
    {
        char c = expression[i];
        if(c == '+' || c == '-' || c == '*') {
            ops.push_back(c);
            nums.push_back(stoi(str));
            str.clear();
        }
        else str.push_back(c);
    }
    nums.push_back(stoi(str));
    
}

void calculate(vector<long long>&nums_, vector<char> &ops_, char op)
{
    vector<int> location;
    bool check = true;
    while(check){
        check = false;
        for(int i = 0; i < ops_.size(); i++)
        {
            if(op == ops_[i])
            {
                check = true;
                switch(op){
                    case '+': nums_[i] = nums_[i] + nums_[i+1];break;
                    case '-': nums_[i] = nums_[i] - nums_[i+1];break;
                    case '*': nums_[i] = nums_[i] * nums_[i+1];break;
                }
            nums_.erase(nums_.begin() + (i+1));
            ops_.erase(ops_.begin() + i);
            i--;
            }
        }
    }
}

long long solution(string expression)
{
    long long answer = 0;
    vector<char> op{'*','+','-'};
    vector<char> ops; vector<long long> nums;
    parseExpressoin(ops,nums,expression);

    do{
        vector<long long> tmpnum = nums;
        vector<char> tmpops = ops;
        for(auto o : op)
        {
            calculate(tmpnum,tmpops,o);
        }
        if(answer < abs(tmpnum[0])) answer = abs(tmpnum[0]);

    }while(next_permutation(op.begin(),op.end()));
    
    return answer;
}