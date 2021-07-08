#include <iostream>
#include <string>
using namespace std;

int myfind(string &page, string &word)
{
    int count = 0;
    int check = 0;
    for(int i = 0; i<page.size(); i++)
    {
        for(int j = 0; j <word.size(); j++)
        {
              if(page[i+j] != word[j]) {
                  check = 0; 
                  break;
              }
              check = 1; 
        }
        if(check == 1){
          count++;
          i = i+word.size()-1;  
        } 
    }
    return count;
}

int main()
{
    string page,word;
    getline(cin,page);
    getline(cin,word);
    cout << myfind(page,word);
    

}