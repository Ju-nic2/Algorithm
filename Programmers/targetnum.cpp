#include <string>
#include <vector>
#include <iostream>
using namespace std;
int answer = 0;
int targetNum = 0;
vector<int> number;

void FindTarget(int num, int index)
{
    if(index == number.size())
    {

        if(num == targetNum) answer++;
    }
    else{
        FindTarget(num-number[index],index+1);
        FindTarget(num+number[index],index+1);
    }
}
int solution(vector<int> numbers, int target) {
    number = numbers;
    targetNum = target;
    FindTarget(0,0);
    return answer;
}