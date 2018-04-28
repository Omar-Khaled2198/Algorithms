#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

long long CountInvMerge(long long* a, int n)
{
    int mid=n/2,i,j,k;
    long long cnt=0;
    int n1=mid;
    int n2=n-mid;

    long long* L=new long long[n1];
    long long* R=new long long[n2];

    for (i=0;i<n1;i++)
    {
        L[i]=a[i];
    }
    j=0;
    for (;i<n;i++)
    {
        R[j++]=a[i];
    }
    i=0,j=0,k=0;
    while(i<n1&&j<n2)
    {
        if(L[i]>R[j])
        {
            cnt+=n1-i;
            a[k++]=R[j++];
        }
        else
        {
            a[k++]=L[i++];
        }
    }
    while(i<n1)
    {
        a[k++]=L[i++];
    }
    while(j<n2)
    {
        a[k++]=R[j++];
    }
    return cnt;
}
long long CountInv(long long* a, int n)
{
    if (n == 1)
        return 0;
    int mid=n/2;
    return CountInv(a,mid)+CountInv(a+mid,n-mid) + CountInvMerge(a,n);
}

int main()
{
    int n;
    long long *ar;
    cin>>n;
    int j = 0;
    while (n != 0)
    {
        ar=new long long[n];
        for (int i=0;i<n;i++)
        {
            cin>>ar[i];
        }
        cout<<CountInv(ar,n)<< "\n";
        cin>>n;
    }
    return 0;
}
