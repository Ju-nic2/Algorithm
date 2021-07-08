#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
private:
    vector<int>set;
public:
    UnionFind(const int& size=0)
        :set(size)
        {
            initializetion(set);
        }
    void initializetion(vector<int>&set)
    {
        for(int i=0; i<set.size(); i++)
        {
            set[i] = i;
        }
            
    }

    int find(int p)
    {
        while(p != set[p])
            p=set[p];
        return p;
    }
    bool cycleCheck(int p,int q)
    {
        int rootp = find(p);
        int rootq = find(q);
        cout <<"root : "<< rootp<<" " << rootq<<endl;
        return rootp == rootq;
    }
    void unionqp(int p,int q)
    {
        if(cycleCheck(p,q)) return;
        else {
            int rootp = find(p);
            int rootq = find(q);
            
            set[rootq] = rootp;
        }
    }
};
int main()
{
    int n,m;
    cin >> n >> m;
    UnionFind uf(n);
    bool result = false;
    for(int i = 0; i<m; i++)
    {
        int p,q;
        cin >> p>>q;
        if(uf.cycleCheck(p,q))
        {
            result = true;
            cout << 1 << endl;
            break;
        }else uf.unionqp(p,q);
    }
    if(!result)
        cout << 0;

   
}