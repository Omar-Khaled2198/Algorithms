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

template<class Elem>
struct Heap
{
    int n;
	int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);
	void Initialize(bool (*_IsBefore)(Elem&, Elem&), int _n) // n is required to allocate and initialize pos[]
	{
        n=_n;
		pos=new int[n];
		for(int i=0;i<n;i++)
			pos[i]=-1;
		IsBefore=_IsBefore;
		a.Initialize();
	}
	void Destroy()
	{
		a.Destroy();
		delete [] pos;
	}
	int Child(int i)
	{
		if(2*i+1>=a.n)
			return -1;
		else
			return 2*i+1;
	}
	int Parent(int i)
	{
		if((i-1)/2<0)
			return -1;
		else
			return (i-1)/2;
	}
	void MoveUp(int ind)
	{
		while(ind!=0&&IsBefore(a[ind],a[Parent(ind)]))
		{
			Elem temp=a[ind];
			a[ind]=a[Parent(ind)];
            pos[a[ind].v]=ind;
			a[Parent(ind)]=temp;
			ind=Parent(ind);
            pos[a[ind].v]=ind;
		}
	}
	void MoveDown(int ind)
	{
		int left=Child(ind);
		if (left==-1)
			return ;
		int right=left+1;
		if (right<a.n&&IsBefore(a[right],a[left]))
			left=right ;
		if (IsBefore(a[left],a[ind]))
		{
			Elem temp=a[left];
			a[left]=a[ind];
			a[ind]=temp;
            pos[a[left].v]=left;
            pos[a[ind].v]=ind;
			MoveDown(left) ;
		}
	}
	void Add(Elem e)
	{
		a.AddLast(e);
        pos[a[a.n-1].v]=a.n-1;
		MoveUp(a.n-1);
	}
	Elem GetFirst()
	{
		return a[0];
	}
	Elem RetrieveFirst()
	{
		Elem temp=a[0];
        pos[a[0].v]=-1;
		a[0]=a[a.n-1];
        pos[a[0].v]=0;
		a.RemoveLast();
		MoveDown(0);
		return temp;
	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int	v;
	int	w;
};

struct Node
{
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
	Node *nodes;

	void Initialize(int _n)
	{
		n=_n;
		nodes= new Node[n];
		for(int i=0;i<n;i++)
			nodes[i].Initialize();
	}
	void Destroy()
	{
		for(int i=0;i<n;i++)
			nodes[i].Destroy();
		delete [] nodes;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int num,counter=0;
	cin>>num;
	while(true)
	{
		if(counter==num)
			break;
		int n,m,s,t;
		cin>>n>>m>>s>>t;
		Graph graph;
		graph.Initialize(n);
		for(int i=0;i<m;i++)
		{
			int x,y,w;
			cin>>x>>y>>w;
			Edge edge;
			edge.v=y;
			edge.w=w;
			graph.nodes[x].adj.AddLast(edge);
			edge.v=x;
			graph.nodes[y].adj.AddLast(edge);
		}

		Heap<Edge>heap;
		heap.Initialize(IsBefore,n);
		Edge edge;
		edge.v=s;
		edge.w=0;
		heap.Add(edge);
		Edge tempEdge=edge;
        for(int i=0;i<n;i++)
        {
            if(i!=s)
            {
                edge.v=i;
                edge.w=INT32_MAX;
                heap.Add(edge);
            }
        }
		int maxi=-1;
		while(true)
		{
			if(tempEdge.v==t)
			{
				maxi=tempEdge.w;
				break;
			}
			tempEdge=heap.RetrieveFirst();
			for(int i=0;i<graph.nodes[tempEdge.v].adj.n;i++)
			{
				edge.w = tempEdge.w + graph.nodes[tempEdge.v].adj[i].w;
                if(heap.pos[graph.nodes[tempEdge.v].adj[i].v]!=-1)
                {
                    if(heap.a[heap.pos[graph.nodes[tempEdge.v].adj[i].v]].w>edge.w)
                    {
                        heap.a[heap.pos[graph.nodes[tempEdge.v].adj[i].v]].w=edge.w;
                        heap.MoveUp(heap.pos[graph.nodes[tempEdge.v].adj[i].v]);
                    }
                }
			}

		}
		if(maxi==INT32_MAX||maxi<0)
			cout<<"Case #"<<counter+1<<": unreachable\n";
		else
			cout<<"Case #"<<counter+1<<": "<<maxi<<"\n";
		counter++;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
