#include <iostream>
using namespace std;
int main()
{
    string num1;
    string num2;
    int ans[100]={0};
    cin>>num1;
    cin>>num2;
    int n=0;
    int l1=num1.length();
    int l2=num2.length();
    int j=l2-1;
    for(int i=l1-1;i>=0;i--)
    {
        if(j>=0)
        {
            if(ans[n]+(num1[i]-'0')+(num2[j]-'0')<10)
            {
                ans[n]=ans[n]+(num1[i]-'0')+(num2[j]-'0');
            }
            else
            {
                ans[n]=(ans[n]+(num1[i]-'0')+(num2[j]-'0'))%10;
                ans[n+1]++;
            }
            n++;
            j--;
        }
            
        else
        {
            if(ans[n]+(num1[i]-'0')<10)
            {
                ans[n]=ans[n]+(num1[i]-'0');
            }
            else
            {
                ans[n]=(ans[n]+(num1[i]-'0'))%10;
                ans[n+1]++;
            }
            n++;
        }
    }
    for(int i=n-1;i>=0;i--)
    cout<<ans[i];
    return 0;
}