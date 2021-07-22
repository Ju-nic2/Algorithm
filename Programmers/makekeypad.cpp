#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
void find(int &x,int&y,int num);
int keypad[4][3] = {
    {10,0,12},
    {7,8,9},
    {4,5,6},
    {1,2,3},
    };

string solution(vector<int> numbers, string hand) {
    pair<int,int> left = make_pair(0,0);
    pair<int,int> right = make_pair(2,0);
   
    string answer = "";
    for(int i = 0; i<numbers.size(); i++)
    {
        int x = 0; int y = 0;
       if(numbers[i] == 1||numbers[i] == 4||numbers[i] == 7)
       {
           find(x,y,numbers[i]);
           left.first = x;
           left.second = y;
           answer.push_back('L');
       }else if(numbers[i] == 3||numbers[i] == 6||numbers[i] == 9)
       {
           find(x,y,numbers[i]);
           right.first = x;
           right.second = y;
           answer.push_back('R');
       }else{
           int distanceL = 0; int distanceR = 0;
           find(x,y,numbers[i]);
           
           distanceL = abs(x-left.first) +abs(y-left.second);
           distanceR = abs(x-right.first) +abs(y-right.second);
           if(distanceL < distanceR)
           {
                left.first = x;
                left.second = y;
                answer.push_back('L');
           }else if(distanceL > distanceR)
           {
                right.first = x;
                right.second = y;
                answer.push_back('R');
           }else{
               if(hand[0] == 'r')
               {
                    right.first = x;
                    right.second = y;
                answer.push_back('R');
               }else{
                   left.first = x;
                left.second = y;
                answer.push_back('L');
               }
           }
           //printf("%d %d %d\n",numbers[i],x,y);
       }
    }
    
    
    return answer;
}

void find(int &x,int &y,int num)
{
    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(keypad[i][j] == num)
            {
                x = j;
                y = i;
            }
        }
    }
}