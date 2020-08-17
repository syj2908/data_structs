#include <iostream>
#include <cstdlib>
using namespace std;
class SeqStack
{
    private:
        int maxsize;
        int* base;
        int top;

    public:
        SeqStack(int size)
        {
            maxsize=size;
            base=new int[maxsize];
            top=0;
        }
        void push(int c)//入栈
        {
            base[top]=c;
            top++;
        }
        char pop()//出栈
        {   
            top--;
            return base[top];
        }
};

int main()
{
    SeqStack stack(10000);
    char* c;
    int sum=0;
    while (cin>>c)
    {
        if(c[0]=='#') break;
        if(atoi(c)!=0)
        {
			stack.push(atoi(c));
        }
        else
        {
            int num2=stack.pop();//注意先后！
            int num1=stack.pop();
            switch(c[0])
            {
                case '+' :
                {
                    sum=num1+num2;
                    stack.push(num1+num2);
                    break;
                }
                case '-' :
                {
                    sum=num1-num2;
                    stack.push(num1-num2);
                    break;
                }
                case '*' :
                {
                    sum=num1*num2;
                    stack.push(num1*num2);  
                    break;
                }
                case '/' :
                {
                    sum=num1/num2;
                    stack.push(num1/num2);
                    break;
                }

            }
        }
        
    }
    cout<<sum<<endl;
    return 0;
    
}
