#include <iostream>
using namespace std;

int n,k;
const int nk = 10001;
long long arr[nk];

long long getCount(int length)
{
    long long count = 0;
    for(int i = 0; i < k; i++)
    {
        count += arr[i]/length;
    }
    return count;
}
void getMaxlength(long long low, long long high)
{
    while(low<=high)
    {       
        long long mid = (low+high)/2;
        if(getCount(mid) >= n)
        {
            low = mid+1;
        }else high = mid-1; 
    }
    cout << low-1;
}
int main()
{

    cin >> k >> n;

    long long high = 0;
    for(int i = 0 ; i < k; i++)
    {
        cin >> arr[i];
        if(arr[i] > high) high = arr[i];
    }
    getMaxlength(1,high);


}