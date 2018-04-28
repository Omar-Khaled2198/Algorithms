#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <tgmath.h>
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;

    void Initialize()
    {
        n=0 ; sz = 1 ; arr = new Value [sz] ;
    }
    void Destroy()
    {
        delete [] arr;
    }
    void AddLast(Value v)
    {
        if (n == sz)
        {
            sz *= 2 ;
            Value *new_arr = new Value[sz] ;
            for (int i = 0 ; i < n ; ++i)
                new_arr[i] = arr[i] ;

            delete []arr ;
            arr = new_arr ;
        }
        arr[n++] = v ;
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

struct Edge
{
	int		v;  // id of the adjacent node
	double	w;  // edge weight = distance between the two nodes
};

struct Node
{
	int x,y; // x and y coordinates of the node
	Array<Edge> adj;

	void Initialize()
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
            nodes[i].Initialize();
    }
	void Destroy()
    {
        for(int i=0;i<n;i++)
            nodes[i].Destroy();
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Array<int>indexer;
    Array<double>minDistance;
    int counter=1;
    while(true)
    {
        int n;
        cin>>n;
        if(n==0)
            break;
        Graph graph;
        graph.Initialize(n);
        for(int i=0;i<n;i++)
            cin>>graph.nodes[i].x>>graph.nodes[i].y;
        string space;
        getline(cin, space);

        for(int i=0;i<n;i++)
        {
            for(int x=0;x<n;x++)
            {
                Edge edge;
                edge.v=x;
                edge.w=(double)sqrt(pow(graph.nodes[x].x-graph.nodes[i].x,2)+pow(graph.nodes[x].y-graph.nodes[i].y,2));
                graph.nodes[i].adj.AddLast(edge);
            }
        }
        indexer.Initialize();
        minDistance.Initialize();
        int minIndexX=-1,minIndexY=-1;
        double minValue;
        indexer.AddLast(0);
        while(minIndexY!=1)
        {
            minIndexX=minIndexY=-1;
            minValue=1000.0;
            for(int i=0;i<indexer.n;i++)
            {
                for(int x=0;x<n;x++)
                {
                    if(graph.nodes[indexer[i]].adj[x].w<minValue&&graph.nodes[indexer[i]].adj[x].w!=0)
                    {
                        minValue=graph.nodes[indexer[i]].adj[x].w;
                        minIndexX=indexer[i];
                        minIndexY=x;
                    }
                }
            }
            graph.nodes[minIndexX].adj[minIndexY].w=0;
            graph.nodes[minIndexY].adj[minIndexX].w=0;
            minDistance.AddLast(minValue);
            indexer.AddLast(minIndexY);
        }
        double maxi=0.000;
        for(int i=0;i<minDistance.n;i++)
        {
            if(maxi<minDistance[i])
                maxi=minDistance[i];
        }
        cout<<"Scenario #"<<counter<<endl;
        counter++;
        cout<<"Frog Distance = "<<fixed<<setprecision(3)<<maxi<<endl;
        cout<<endl;
        minDistance.Destroy();
        indexer.Destroy();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
