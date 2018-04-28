#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b)// Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
{
    if(a==b)
    {
        T[a][b]=0;
        return T[a][b];
    }

    if(T[a][b]>=0)
        return T[a][b];

    T[a][b]=INT32_MAX;
    for(int k=a;k<b;k++)
    {
        int v=MatChain(a,k)+MatChain(k+1,b)+p[a-1]*p[k]*p[b];
        if(v<T[a][b])
        {
            T[a][b]=v;
            D[a][b]=k;
        }
    }
    return T[a][b];

}
void MatChainTopDown(int n)
{
    for(int i=0;i<n;i++)
        for(int x=0;x<n;x++)
            T[i][x]=-1;
    MatChain(0,n-1);
}

void MatChainBottomUp(int n)
{
    for(int i=1;i<n;i++)
    {
        for(int x=0;x<=n-i;x++)
        {
            int j=i+x-1;
            if(x==j)
            {
                T[x][j]=0;
                continue;
            }
            else
            {
                T[x][j]=INT32_MAX;
                for(int k=x;k<=j;k++)
                {
                    int v=T[x][k]+T[k+1][j]+(p[x-1]*p[k]*p[j]);
                    if(v<T[x][j])
                    {
                        T[x][j]=v;
                        D[x][j]=k;
                    }
                }
            }
        }
    }
}


void MatChainSol(int a, int b)// Recursive to output the solution for both versions
{
    if(a==b)
    {
        cout<<"A"<<b;
        return;
    }
    int k=D[a][b];
    cout<<"(";
    MatChainSol(a,k);
    cout<<" x ";
    MatChainSol(k+1,b);
    cout<<")";
}
void Compute()
{
    int counter=1;
    while(true)
    {
        int num;
        cin>>num;
        if(num==0)
            break;
        for(int i=0;i<num;i++)
        {
            int x,y;
            cin>>x>>y;
            if(i==num-1)
            {
                p[i]=x;
                p[i+1]=y;
            }
            else
                p[i]=x;
        }
        if(counter%2==0)
            MatChainBottomUp(num+1);
        else
            MatChainTopDown(num+1);
        cout<<"Case "<<counter<<": ";
        MatChainSol(1,num);
        cout<<"\n";
        counter++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

