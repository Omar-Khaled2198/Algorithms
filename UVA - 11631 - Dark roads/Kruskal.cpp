#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n)
    {
        n=_n;
        parent=new int[n];
        num_nodes=new int[n];
        for(int i=0;i<n;i++)
        {
            parent[i]=-1;
            num_nodes[i]=1;
        }
    }
    void Destroy()
    {
        delete[] parent;
        delete[] num_nodes;
    }
    int Find(int i)
    {
        if(parent[i]==-1)
            return i;
        else
            return Find(parent[i]);
    }
    bool Union(int i, int j)
    {
        int a=Find(i),b=Find(j);
        if(a==b)
            return false;
        if(num_nodes[a]<num_nodes[b])
        {
            parent[b]=a;
            num_nodes[a]+=num_nodes[b];
        }
        else
        {
            parent[a]=b;
            num_nodes[b]+=num_nodes[a];
        }
        return true;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid=n/2,i,j,k;
    int n1=mid;
    int n2=n-mid;

    Type* L=new Type[n1];
    Type* R=new Type[n2];

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
        if(IsBefore(R[j],L[i]))
        {
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
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if (n <= 1)
        return;
    int mid=n/2;
    MergeSort(a,mid,IsBefore);
    MergeSort(a+mid,n-mid,IsBefore);
    Merge(a,n,IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int u, v;
    int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
    return a.w<b.w;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    while(true)
    {
        int n,m;
        cin>>n>>m;
        if(n==0||m==0)
            break;
        Edge *arr=new Edge[m];
        int sum=0,sum2=0;
        for(int i=0;i<m;i++)
        {
            cin>>arr[i].u>>arr[i].v>>arr[i].w;
            sum+=arr[i].w;
        }
        MergeSort(arr,m,IsBeforeEdge);
        DisjointSets disjointSets;
        disjointSets.Initialize(n);
        for(int i=0;i<m;i++)
        {
            bool check=disjointSets.Union(arr[i].u,arr[i].v);
            if(check)
                sum2+=arr[i].w;
        }
        cout<<sum-sum2<<endl;

    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
