#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Kevin
{
private:
    vector<vector<int>> relations;
    vector<bool> visit;
    vector<int> depth;
    queue<int> q;
public:
    Kevin(const int& num)
    {
        for(int i = 0; i < num; i++)
            relations.push_back(vector<int>());
        visit.resize(num,false);
        depth.resize(num,0);
    }
    void input(const int a, const int b)
    {
        relations[a].push_back(b);
        relations[b].push_back(a);
    }
    void initvisit()
    {
        for(auto v : visit) v = false;
        for(auto d : depth) d = 0;
    }
    int BFS(int start)
    {
        int bacon = 0;
        q.push(start);
        visit[start] = true;
        depth[start] = 0;
        while(!q.empty())
        {
            int now = q.front(); q.pop();
            for(auto next : relations[now])
            {
                if(!visit[next])
                {
                    visit[next] = true;
                    q.push(next);
                    depth[next] = depth[now]+1;
                    bacon += depth[next];
                }
            }
        }
        return bacon;
    }
    void findMin()
    {
        int MIN = INT32_MAX;
        int person = -1;
        for(int i = 0; i < relations.size(); i++)
        {
            int now = BFS(i);
            if(now < MIN) {MIN = now; person = i+1;}
            initvisit();
        }
        cout << person;
    }

};
int main()
{
    int n,m;
    cin >> n >> m;
    Kevin k(n);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        k.input(a-1,b-1);
    }
    k.findMin();
}