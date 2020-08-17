#include<iostream>
using namespace std;
int main()
{
    int n1,n2;
    int s1[10]={0};
    int s2[10]={0};
    cin>>n1;
    for(int i=0;i<n1;i++)
    {
        cin>>s1[i];
    }
    cin>>n2;
    for(int i=0;i<n2;i++)
    {
        cin>>s2[i];
    }
    int ans[10]={0};
    for(int i=0;i<n1;i++)
        for(int j=0;j<n2;j++)
        {
            int temp=s1[i]*s2[j];
            ans[i+j]+=temp;
        }
    for(int i=0;i<n1+n2-1;i++)
    {
        cout<<ans[i];
        if(i!=n1+n2-2)
        cout<<" ";
    }
    return 0;
}