#include <iostream>
#include <map>
#include <vector>
using namespace std;

class DPQueue{
private:
    map<long,int> data;
    map<long,int>::iterator it;
public:
    DPQueue(){}
    void operate(const char& op, const long &number)
    {
        if(op == 'I')
        {
            if(data.find(number) != data.end()) data[number]++;
            else data[number] = 1;
        }
        else if(op == 'D' && !data.empty())
        {
            if(number == -1)
            {
                it = data.begin();
                if(it->second > 1) it->second--;
                else data.erase(it);
            }else if(number == 1)
            {
                 it = data.end();
                 it--;
                if(it->second > 1) it->second--;
                else data.erase(it);
            }
        }
    }
    void print()
    {
        if(data.empty()) cout << "EMPTY";
      
        else{
            it = data.end();
            it--;
            cout << it->first<< " ";
            it = data.begin();
            cout << it->first;
        }
        cout << '\n';
    }

};

int main()
{
    
    int Tcase;
    cin>>Tcase;
    vector<DPQueue> answer(Tcase);
    for(int i = 0; i<Tcase; i++)
    {
        int n;
        cin >> n;
        for(int k = 0; k < n; k++)
        {
            long num; char op;
            cin >> op >>num;
            answer[i].operate(op,num);
        }
    }
    for(int i = 0; i<Tcase; i++)
    {
        answer[i].print();
    }

}

