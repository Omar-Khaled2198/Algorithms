#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
#include <iomanip>

using namespace std;


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

struct Point
{
    double x,y;
};

bool IsBeforeX(Point& a, Point& b)
{
    if(a.x<b.x)
        return 1;
    else
        return 0;
}
bool IsBeforeY(Point& a, Point& b)
{
    if(a.y<b.y)
        return 1;
    else
        return 0;
}

double dist(Point& a, Point& b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{
    if (n < 4)
    {
        double min = INT32_MAX;
        for (int i=0;i<n;i++)
            for (int j=i+1;j<n;j++)
                if (dist(p[i], p[j]) < min)
                    min = dist(p[i], p[j]);
        return min;
    }

    int mid = n/2;
    Point middle = p[mid];
    double left = ClosestPair(p,mid);
    double right = ClosestPair(p+mid,n-mid);

    double d = min(left, right);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(p[i].x - middle.x) < d)
            strip[j] = p[i], j++;
    MergeSort(strip,j,IsBeforeY);

    for (int i = 0; i < j; i++)
        for (int x = i+1; x < j && (strip[j].y-strip[i].y)<d;x++)
            if (dist(strip[i],strip[x]) < d)
                d = dist(strip[i], strip[x]);

    return d;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    while(true)
    {
        int n;
        cin>>n;
        if(n==0)
            break;
        Point *points=new Point[n];
        for(int i=0;i<n;i++)
            cin>>points[i].x>>points[i].y;
        MergeSort(points,n,IsBeforeX);
        double distance=ClosestPair(points,n);
        if(distance>10000)
            cout<<"INFINITY"<<endl;
        else
            cout<<fixed<<setprecision(4)<<distance<<endl;

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
