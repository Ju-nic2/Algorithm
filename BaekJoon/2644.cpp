#include <iostream>
#include <vector>
using namespace std;
vector<int> persons[101];
bool visit[101];
int chon = -1;
void DFS(int now, int depth, int target)
{
    visit[now] = true;
    if(now == target)
        chon = depth;
    for(auto next : persons[now]){
        if(!visit[next]) DFS(next,depth+1,target);
    }
}
int main()
{
    int n;
    cin >> n;
    int start,des;
    cin >> start >> des;
    int m;
    cin >> m;
    for(int i = 0 ; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        persons[a].push_back(b);
        persons[b].push_back(a);
    }
    DFS(start,0,des);
    cout << chon;

}

