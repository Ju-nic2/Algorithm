#include <iostream>
#include <queue>
using namespace std;
int visit[1000001];
queue<int> q;
int main()
{
    int f,s,g,U,D;
    int d[2];
    cin >> f >> s >> g >> U >> D;
    d[0] = U;
    d[1] = -D;
    q.push(s); 
    while(!q.empty())
    {
        int now = q.front();
        if(now == g) {cout << visit[now]; return 0;}
        q.pop();
        for(int i = 0; i < 2; i++)
        {
            int next = now + d[i];
            if(next >= 1 && next <= f){
                if(next == now) continue;
                if(visit[next] == 0)
                {
                    visit[next] = visit[now] + 1;
                    q.push(next);
                }
            }
        }
    }
    cout <<"use the stairs";

}