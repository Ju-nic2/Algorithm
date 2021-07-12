#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
class Friends
{
private:
    vector<vector<int>> relation;
    vector<int> friendNum;
    vector<bool> visit;
    queue<int> q;
public:
    Friends(const int N)
    {
        relation.resize(N);
        friendNum.resize(N,0);
        visit.resize(N),0;
    }
    void input(const int n,const int f)
    {
        relation[n].push_back(f);
        relation[f].push_back(n);
    }

    int find2_friend(int start)
    {
        int depth = 0;
        int count = 0;
        q.push(start);
        visit[start] = true;
        while(!q.empty())
        {
            int now = q.front();
            q.pop();
            if(depth < 1)
            {
                for(auto next : relation[now])
                {
                    if(!visit[next])
                    {
                        visit[next] = true;
                        q.push(next);
                        count++;
                    }
                }
            }else{
                for(auto next : relation[now])
                {
                    if(!visit[next])
                    {
                        visit[next] = true;
                        count++;
                    }
                }
            }
            depth++;
        }
        return count;

    }
    void resetvisit()
    {
        for(auto v : visit)
            v = false;
    }
    void findMax()
    {
        int max = 0;
        for(int i = 0; i < relation.size(); i++)
        {
            int cur = find2_friend(i);
            if(max < cur) max = cur;
            resetvisit();
        }
        cout << max;
    }
};
int main()
{
    int n;
    cin >> n;
    string relation;
    Friends fs(n);
    for(int i = 0; i < n; i++)
    {
        cin >> relation;
        for(int j = 0; j < relation.size(); j++)
        {
            if(relation[j] == 'N') continue;
            else fs.input(i,j);
        }
    }
    fs.findMax();
}