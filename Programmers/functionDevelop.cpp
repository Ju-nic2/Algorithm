#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    vector<int> works;
    
    for(int i = 0; i <progresses.size(); i++)
    {
        int remain; int work;
        remain = 100 - progresses[i];
        remain % speeds[i] == 0 ? work = remain/speeds[i] : work = remain/speeds[i]+1;
        works.push_back(work);
    }
    int count = 1;
    int release = works[0];
    for(int i = 1; i < works.size(); i++)
    {
        if(release >= works[i])
        {
            count++;
        }else
        {
            answer.push_back(count);
            release = works[i];
            count = 1;
        }
    }
     answer.push_back(count);
   
    
    return answer;
}