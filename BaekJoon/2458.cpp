#include <iostream>
using namespace std;
int student[501][501];
int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int x, y; cin >> x >> y;
        student[x][y] = 1; 
    }
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(student[i][k] != 0 && student[k][j] != 0) student[i][j] = 1;
            }
        }
    }
    int count = 0;
    bool check = false;
     for(int i = 1; i <= n; i++)
    {
        check = false;
        for(int j = 1; j <= n; j++)
        {
            if(student[i][j] == 0 && student[j][i] == 0 && i != j) {check = true; break;}
        }
        if(!check) count++;
    }
    cout << count;
}