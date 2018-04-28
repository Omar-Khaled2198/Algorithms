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

template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(int&, int&);
	void Initialize(bool (*_IsBefore)(int&, int&))
	{
		IsBefore=_IsBefore;
		a.Initialize();
	}
	void Destroy()
	{
		a.Destroy();
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
            a[Parent(ind)]=temp;
			ind=Parent(ind);
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
			MoveDown(left) ;
		}
	}
	void Add(Elem e)
	{
		a.AddLast(e);
		MoveUp(a.n-1);
	}
	Elem GetFirst()
	{
		return a[0];
	}
	Elem RetrieveFirst()
	{
		Elem temp=a[0];
		a[0]=a[a.n-1];
		a.RemoveLast();
		MoveDown(0);
		return temp;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	while(true)
	{
		int num,cost=0,temp=0;
		cin>>num;
		if(num==0)
			break;
		Heap<int> heap ;
		heap.Initialize(IsBeforeInt);
		for(int i=0;i<num;i++)
		{
			int x;
			cin>>x;
			heap.Add(x);
		}
		while(heap.a.n>1)
		{
			int a=heap.RetrieveFirst();
			int b=heap.RetrieveFirst();
			cost=a+b;
			temp+=cost;
			heap.Add(cost);
		}
		cout<<temp<<endl;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
