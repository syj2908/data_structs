#include<iostream>
using namespace std;
int dxs[10]={0};
int ans[10]={0};
int nn;
void fun(int n1,int n2,int s1[],int s2[])
{

    for(int i=0;i<n1;i++)
        for(int j=0;j<n2;j++)
        {
            int temp=s1[i]*s2[j];
            ans[i+j]+=temp;
        }
    nn=n1+n2-1;
    for(int i=0;i<10;i++)
    {
        dxs[i]=ans[i];
        ans[i]=0;
    }
}

int main()
{
    int n;
    cin>>n;
    nn=n;
    int s1[10]={0};
    for(int i=0;i<n;i++)
    {
        cin>>s1[i];
        dxs[i]=s1[i];
    }
    int m;
    cin>>m;
    for(int i=0;i<m-1;i++)
    {
        fun(n,nn,s1,dxs);
    }
    for(int i=0;i<nn+n-3;i++)
    {
        cout<<dxs[i];
        if(i<n+nn-2)
        cout<<" ";
    }
    return 0;
}