#include <iostream>
#include <string>
#include <list>
using namespace std;

void findBomb(list<char> &str, string bomb)
{
    while(true)
    {
        bool check = true;
        int index = 0;
        for(list<char>::iterator it = str.begin(); it != str.end(); ++it)
        {
            list<char>::iterator it1 = it;
            for(int j = 0; j <bomb.size(); j++){ 
                if(*it1 == bomb[j]) {
                    it1++;
                    if(j == bomb.size()-1){
                        str.erase(it,it1);
                        check = false;
                        it = it1;
                        for(int k = 0; k<bomb.size()-1; k++ ){
                            it--;
                            it1--;
                        }
                        j=-1;
                }
                }else{           
                    break;
                }  
            }
   
        }
 
        if(check) break;
    }
}

int main()
{
    string tmp,bomb;
    cin>>tmp;
    cin>>bomb;
    list<char> str;
    for(int i = 0; i <tmp.size(); i++) str.push_back(tmp[i]);
    findBomb(str,bomb);
    if(str.size() == 0) cout <<"FRULA";
    else{
        for(auto s : str)
            cout << s;
    }
  
}