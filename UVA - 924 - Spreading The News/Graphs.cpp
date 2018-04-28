#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;

    void Initialize()
    {
        n=0;
        sz = 1;
        arr = new Value [sz] ;
    }
    void Destroy()
    {
        delete [] arr;
    }
    void AddLast(Value v)
    {
        if (n==sz)
        {
            sz *=2;
            Value *new_arr=new Value[sz];
            for(int i=0;i<n;i++)
                new_arr[i] = arr[i];
            delete []arr ;
            arr=new_arr ;
        }
        arr[n++]=v;
    }
    void RemoveLast()
    {
        if (n==0)
            return;
        n--;
    }
    Value& operator[](int i)
    {
        return arr[i];
    }

    void print()
    {
        for (int i=0;i<n;i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl ;
    }
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
    Array<int> adj;

    void Initialize(int n)
    {
        adj.Initialize();
    }
    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n)
    {
        n=_n;
        nodes=new Node[n];
        for(int i=0;i<n;i++)
            nodes[i].Initialize(n);
    }
    void Destroy()
    {
        for(int i=0;i<n;i++)
            nodes[i].Destroy();
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue
{
    int f, n;
    Type* elems;

    void Initialize(int size)
    {
        f=n=0;
        elems=new Type[size];
    }
    void Destroy()
    {
        delete[] elems;
    }
    void Add(Type t)
    {
        if(n==0)
        {
            f=n;
            elems[n++]=t;
        }
        else
            elems[n++]=t;
    }
    Type Pop()
    {
        int temp=elems[f];
        f++;
        return temp;
    }
    Type Peek()
    {
        return elems[f];
    }
    int Num()
    {
        return n-f;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int num;
    cin>>num;
    Graph graph;
    graph.Initialize(num);
    Array<int>keepTrack,days,visited;
    visited.Initialize();
    days.Initialize();
    keepTrack.Initialize();
    for(int i=0;i<num;i++)
    {
        int n;
        cin>>n;
        for(int x=0;x<n;x++)
        {
            int e;
            cin>>e;
            graph.nodes[i].adj.AddLast(e);
        }
        days.AddLast(0);
        keepTrack.AddLast(0);
        visited.AddLast(0);
    }
    int t;
    cin>>t;
    int test;

    for(int i=0;i<t;i++)
    {
        Queue<int>queue;
        queue.Initialize(num);
        cin>>test;
        queue.Add(test);
        int maximum=0;
        for(int x=0;x<num;x++)
        {
            visited[x]=0;
            days[x]=0;
            keepTrack[x]=0;
        }
        keepTrack[test]=0;
        visited[test]=1;
        while(queue.Num())
        {
            int source=queue.Pop();
            for(int x=0;x<graph.nodes[source].adj.n;x++)
            {
                if(!visited[graph.nodes[source].adj[x]])
                {
                    keepTrack[graph.nodes[source].adj[x]]=keepTrack[source]+1;
                    visited[graph.nodes[source].adj[x]]=1;
                    days[keepTrack[source]]++;
                    if(maximum<days[keepTrack[source]])
                        maximum=days[keepTrack[source]];
                    queue.Add(graph.nodes[source].adj[x]);
                }
            }
        }
        if(maximum==0)
            cout<<0<<endl;
        else
        {
            for(int x=0;x<days.n;x++)
            {
                if(days[x]==maximum)
                {
                    cout<<maximum<<" "<<x+1<<endl;
                    break;
                }
            }
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
