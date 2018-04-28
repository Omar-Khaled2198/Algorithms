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

int main()
{
	int num,x=0;
	cin>>num;
	while(x<num)
	{
		int n,m,max=0;
		cin>>n>>m;
		DisjointSets disjointSets;
		disjointSets.Initialize(n);
		for(int i=0;i<m;i++)
		{
			int p1,p2;
			cin>>p1>>p2;
			disjointSets.Union(p1,p2);
		}
		for(int i=0;i<n;i++)
			if(max<disjointSets.num_nodes[i])
				max=disjointSets.num_nodes[i];
		cout<<max<<endl;
		x++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
