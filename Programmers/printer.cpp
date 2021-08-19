#include <string>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

int solution(vector<int> priorities, int location)
{
    int answer = 0;
    list<pair<int,int>> print;
    for(int i = 0; i < priorities.size(); i++)
        print.push_back({priorities[i],i});

    list<pair<int,int>>::iterator it = print.begin();
    while(true)
    {
        bool check = true;
        for(list<pair<int,int>>::iterator it2 = it; it2 != print.end(); it2++)
        {
            if(it->first < it2->first)
            {
                print.push_back(*it);
                check = false;
                break;
            }
        }
        if(check)
        {
            answer++;
            if(it->second == location) break;
        }
        it = print.erase(it);
       
        
    }
    return answer;
}