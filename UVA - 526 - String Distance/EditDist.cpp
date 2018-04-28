#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];
int EditDist1(int n, int m)
{
    if(n==0||m==0)
    {
        T1[n][m]=n+m;
        return T1[n][m];
    }
    if(T1[n][m]!=-1)
        return T1[n][m];

    int value=1;
    if(a[n-1]==b[m-1])
        value=0;
    int remove=1+EditDist1(n-1,m);
    int replace=value+EditDist1(n-1,m-1);
    int insert=1+EditDist1(n,m-1);
    T1[n][m]=min(min(insert,remove),replace);
    if(T1[n][m]==replace)
        D[n][m]=1;
    else if(T1[n][m]==insert)
        D[n][m]=2;
    else
        D[n][m]=3;
    return T1[n][m];
}
int ComputeEditDist1(int N, int M) // Recursive - memoization - initialize T then call EditDist1(N,M);
{
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= M; j++)
            T1[i][j] = -1;
    }
    return EditDist1(N, M);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M) // Bottom-up, do not save space
{
    for(int i=0;i<=N;i++)
    {
        for(int x=0;x<=M;x++)
        {
            if(i==0||x==0)
                T2[i][x]=i+x;
            int value=1;
            if(a[i-1]==b[x-1])
                value=0;
            int remove=1+T2[i-1][x];
            int replace=value+T2[i-1][x-1];
            int insert=1+T2[i][x-1];
            T2[i][x]=min(min(insert,remove),replace);
            if(T2[i][x]==replace)
                D[i][x]=1;
            else if(T2[i][x]==insert)
                D[i][x]=2;
            else
                D[i][x]=3;
        }
    }
    return T2[N][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M) // Bottom-up, use two rows only
{
    for(int i=0;i<=N;i++)
    {
        for(int x=0;x<=M;x++)
        {
            if(i==0||x==0)
                T3[1][x]=i+x;
            int value=1;
            if(a[i-1]==b[x-1])
                value=0;
            int remove=1+T3[0][x];
            int replace=value+T3[0][x-1];
            int insert=1+T3[1][x-1];
            T3[1][x]=min(min(insert,remove),replace);
            if(T3[1][x]==replace)
                D[i][x]=1;
            else if(T3[1][x]==insert)
                D[i][x]=2;
            else
                D[i][x]=3;
        }
        for(int x=0;x<=M;x++)
            T3[0][x]=T3[1][x];
    }
    return T3[0][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M) // Bottom-up, save maximum space
{
    int temp;
    for(int i=0;i<=N;i++)
    {
        for(int x=0;x<=M;x++)
        {

            if(x==0||i==0)
            {
                temp=T4[x];
                T4[x]=i+x;

            }
            int value=1;
            if(a[i-1]==b[x-1])
                value=0;
            int remove=1+T4[x];
            int replace=value+temp;
            int insert=1+T4[x-1];
            temp=T4[x];
            T4[x]=min(min(insert,remove),replace);
            if(T4[x]==replace)
                D[i][x]=1;
            else if(T4[x]==insert)
                D[i][x]=2;
            else
                D[i][x]=3;

        }
    }
    return T4[M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
    int n,m;
    int oper;
};

Oper opers[81];

int EditDistSol(int N, int M) // Print the solution using D[][]
{
    int n = N, m = M;
    int i = 0;
    int shift = 0;
    while (n>0 && m>0)
    {
        if(D[n][m]==3)
        {
            Oper oper;
            oper.oper = 3;
            oper.n = n;
            n -= 1;
            opers[i++] = oper;
            continue;
        }
        else if (D[n][m] == 2)
        {
            Oper oper;
            oper.oper = 2;
            oper.n = n;
            oper.m = b[m - 1];
            m -= 1;
            opers[i++] = oper;
            continue;
        }
        else if (D[n][m] == 1 && a[n - 1] != b[m - 1])
        {
            Oper oper;
            oper.oper = 1;
            oper.n = n;
            oper.m = b[m - 1];
            n -= 1;
            m -= 1;
            opers[i++] = oper;
            continue;
        }
        n--;
        m--;
    }
    while (true)
    {
        if (n == 0 && m == 0)break;

        if (n == 0 && m != 0)
        {
            Oper oper;
            oper.oper = 2;
            oper.n = n;
            oper.m = b[m - 1];
            m -= 1;
            opers[i++] = oper;
        }
        if (n != 0 && m == 0)
        {
            Oper oper;
            oper.oper = 3;
            oper.n = n;
            n -= 1;
            opers[i++] = oper;
        }
    }
    int c = 0;
    for (int j = i - 1; j >= 0; j--)
    {
        c++;

        cout << c << " ";
        Oper curr = opers[j];
        switch (curr.oper){
            case 1:
                cout << "Replace " << curr.n + shift << "," << char(curr.m);
                break;
            case 2:
                cout << "Insert " << curr.n + 1 + shift << "," << char(curr.m);
                shift++;
                break;
            case 3:
                cout << "Delete " << curr.n + shift;
                shift--;

                break;

        }
        cout << endl;

    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
  //return ComputeEditDist1(N,M);
    //return ComputeEditDist2(N,M);
   // return ComputeEditDist3(N,M);
  return ComputeEditDist4(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{

    int cas=0;
    while(true)
    {
        a[0]=0; b[0]=0;
        if(!fgets(a,82,stdin)) break; fgets(b,82,stdin);
        a[strlen(a)-1]=0;
        b[strlen(b)-1]=0;
        if(cas) cout<<endl; // print an empty line between test cases
        int N=strlen(a), M=strlen(b);
        cout<<ComputeEditDist(N,M)<<endl;
        EditDistSol(N,M);
        cas++;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign11_00526.txt", "r", stdin);
    Compute();


    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
