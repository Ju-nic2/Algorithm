#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void fasionKing(unordered_map<string,int> closet,vector<int> &answer)
{
    unordered_map<string,int>::iterator it;
    int sum = 1;
    for(it = closet.begin(); it != closet.end(); ++it)
    {
        sum = sum*(it->second + 1);
      
    }
    answer.push_back(sum-1);
}
int main()
{
    int tcase,n;
    string wear,category;
    cin >> tcase;
    vector<int> answer;
    for(int t = 0; t < tcase; t++){
        cin >> n;
        unordered_map<string,int> closet;
        for(int i = 0; i < n; i++)
        {
            cin >> wear >> category;
            if(closet.find(category) != closet.end()) closet[category]++;
            else closet[category] = 1;
        }
        fasionKing(closet,answer);
    }

    for(auto ans : answer)
        cout << ans << '\n';



}