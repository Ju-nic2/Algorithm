#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

class houses
{
private:
    int **map;
    int mapsize=0;
    vector<int> subdivision;
public:
    houses(const int& count)
    {
        mapsize = count;
        map = (int**)malloc(sizeof(int*)*count);
        for(int i = 0; i<count; i++)
        {
            map[i] = (int*)malloc(sizeof(int)*count);
        }
    }
    void input(const int &y, const string &line)
    {
        for(int i=0; i<mapsize;i++)
        {
            map[y][i] = line[i]-'0';
        }
    }

    void DFS(int x, int y, int sub) 
    { 
         if (map[y][x] != 1)
        {  
                return; 
        } 
             map[y][x] = map[y][x]+sub+1;
             subdivision[sub]++;
             if (y > 0 && map[y - 1][x] != 0) DFS(x, y - 1, sub); 
             if (y < mapsize - 1 && map[y + 1][x] != 0) DFS(x, y + 1,sub); 
             if (x > 0 && map[y][x - 1] != 0) DFS(x - 1, y, sub); 
             if (x < mapsize - 1 && map[y][x + 1] != 0) DFS(x + 1, y, sub); 
   
    }

    void find()
    {
        int index = 0;
        for(int i=0; i<mapsize; i++)
        {
            for(int j=0; j<mapsize; j++)
            {
                if(map[i][j] == 1)
                {
                    subdivision.push_back(0);
                    DFS(j,i,index++);
                }
            }
        }
    }

    void printResult()
    {
        printf("%d\n",subdivision.size());
        sort(subdivision.begin(),subdivision.end());
        for(int i =0; i<subdivision.size(); i++)
        printf("%d\n",subdivision[i]);
    }
    

    ~houses()
    {
        for(int i = 0; i<mapsize; i++)
        {
            free(map[i]);
        }


        free(map);
    }

} ;
int main()
{
    int size;
    scanf("%d",&size);
    string line;
    houses *h = new houses(size);
    for(int i = 0; i<size; i++)
    {
      cin >> line;
      h->input(i,line);
    }
    h->find();
    h->printResult();
}

