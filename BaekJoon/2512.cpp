#include <iostream>
using namespace std;
const int nm = 10101;
int arr[nm];
int n,m;

long long sumBudget(int budget)
{
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] < budget) sum += arr[i];
        else sum += budget;
    }
    return sum;
}

void budgetDistribute(int max)
{
    int low = 0; int high = max;
    while(low <= high)
    {
        int mid = (low + high)/2;
        if(sumBudget(mid) <= m) low = mid + 1;
        else high = mid -1;
        
    }
    cout << low-1;
}

int main()
{
    cin >> n;
    int max = 0;
    for(int i = 0 ; i < n; i++)
    {
        cin >> arr[i];
        if(arr[i] > max) max = arr[i];
    }
    cin >> m;
    budgetDistribute(max);
}
