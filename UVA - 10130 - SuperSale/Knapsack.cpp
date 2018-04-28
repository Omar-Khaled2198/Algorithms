#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int N, int W)
{
    if(N==0)
        return 0;
    if(T1[N][W]>=0)
        return T1[N][W];
    if(a[N].w>W)
    {
        T1[N][W]=Knapsack1(N-1,W);
    }
    else
    {
        int temp1=Knapsack1(N-1,W);
        int temp2=Knapsack1(N-1,W-a[N].w);
        if (temp1<temp2+a[N].v)
            T1[N][W]=temp2+a[N].v;
        else
            T1[N][W]=temp1;
    }
    return T1[N][W];
}
int ComputeKnapsack1(int N, int W)// Recursive - memoization - initialize T then call Knapsack1(N,W);
{
    for(int i=0;i<=N;i++)
        for(int x=0;x<=W;x++)
                T1[i][x]=-1;
    return Knapsack1(N,W);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W) // Bottom-up, do not save space
{

    for(int i=0;i<=N;i++)
    {
        for(int x=0;x<=W;x++)
        {
            if(i==0||x==0)
                T1[i][x]=0;
            else if(a[i].w>x)
                T1[i][x]=T1[i-1][x];
            else
            {
                if(T1[i-1][x]<a[i].v+T1[i-1][x-a[i].w])
                    T1[i][x]=a[i].v+T1[i-1][x-a[i].w];
                else
                    T1[i][x]=T1[i-1][x];
            }
        }
    }
    return T1[N][W];

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W) // Bottom-up, use two rows only
{
    for(int i=0;i<=N;i++)
    {
        for(int x=0;x<=W;x++)
        {
            if(i==0||x==0)
                T1[1][x]=0;
            else if(a[i].w>x)
                T1[1][x]=T1[0][x];
            else
            {
                if(T1[0][x]<a[i].v+T1[0][x-a[i].w])
                    T1[1][x]=a[i].v+T1[0][x-a[i].w];
                else
                    T1[1][x]=T1[0][x];
            }
        }
        for(int x=0;x<=W;x++)
            T1[0][x]=T1[1][x];
    }
    return T1[0][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W) // Bottom-up, save maximum space
{
    for(int i=0;i<=N;i++)
    {
        for(int x=W;x>=0;x--)
        {
            if(x==0||i==0)
                T4[x]=0;
            else if(a[i].w<=x&&T4[x]<T4[x-a[i].w]+a[i].v)
                    T4[x]=T4[x-a[i].w]+a[i].v;
        }
    }
    return T4[W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
    //return ComputeKnapsack1(N,W);
    //return ComputeKnapsack2(N,W);
    //return ComputeKnapsack3(N,W);
    //return ComputeKnapsack4(N,W);
}

void Compute(); // Get input and call ComputeKnapsack() whenever needed

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign09_10130.txt", "r", stdin);
    //Compute();
    int n,counter=0;
    cin>>n;
    while(true)
    {
        if(counter==n)
            break;
        int num;
        cin>>num;
        a[0].v=0;
        a[0].w=0;
        for(int i=1;i<=num;i++)
            cin>>a[i].v>>a[i].w;
        int fam;
        cin>>fam;
        int weight;
        int sum=0;
        for(int i=0;i<fam;i++)
        {
            cin>>weight;
            sum+=ComputeKnapsack4(num,weight);
        }
        cout<<sum<<endl;
        counter++;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
