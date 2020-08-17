#include<iostream>
#include<fstream>  
using namespace std;
ofstream fout;
ifstream fin;

int vi[10][10]={0};//用做标记路径


struct p//节点定义
{
int x;
int y;
};


class Stack 
{
    int top;
    p s[100];
    
    public:
        Stack()//初始化一个栈
        {
            top=-1;
        }

        bool empty()//判断栈是否为空
        {
            if(top==-1)
            {
                return 1;
            }
            else 
            {
                return 0;
            }
        }

        bool push(p a)//压栈
        {
            top++;
            s[top].x=a.x;
            s[top].y=a.y;
            return 1;
        }

        bool bout()//回到上一个位置再找出路
        {
            if(empty())
            {
                return 0;
            }
            else 
            {
                top--;
                return 1;
            }
        }

        p ntop()//返回栈顶元素
        {
            return s[top];
        }

        void sc()//打印路径
        {
            int m=top;
            int d[100][2];
            int i;
            for(i=0;i<m;i++)
            {
                d[i][0]=s[i].x;
                d[i][1]=s[i].y;
            }
            fout<<"迷宫路径是："<<endl;
            for(i=0;i<m;i++)
            {
                fout<<"("<<d[i][0]<<","<<d[i][1]<<")"<<endl;
            }
        }
};


bool pass(int x,int y,int (*Map)[10])//判断该点是否可以走
{
    if(x<0||x>9)//起始点横坐标非法
    {
        return 0;
    }
    else if(y<0||y>9)//起始点纵坐标非法
    {
        return 0;
    }
    else if(vi[x][y]==1)//这个方向格子走过了
    {
        return 0;
    }
    else if(Map[x][y]==1)//有墙
    {
        return 0;
    }
    else return 1;
}


void slove(p c,Stack &a,int (*Map)[10])//递归寻找路径
{
    p l=a.ntop();//栈顶元素，即起点
    if(l.x==c.x&&l.y==c.y)//该点就是终点
    {
        return;
    }
    if(pass(l.x,l.y+1,Map))//如果该点右边可以走
    { 
        p m;
        m.x=l.x;
        m.y=l.y+1;
        vi[m.x][m.y]=1;//标记该点可走
        a.push(m);//将该点出栈
        slove(c,a,Map);//递归求解下一个点
    }
    else if(pass(l.x,l.y-1,Map))//如果该点左边可以走
    { 
        p m;
        m.x=l.x;m.y=l.y-1;
        vi[m.x][m.y]=1;
        a.push(m);  
        slove(c,a,Map);
    }
    else if(pass(l.x-1,l.y,Map))//如果该点上面可以走
    { 
        p m;
        m.x=l.x-1;m.y=l.y;
        vi[m.x][m.y]=1;
        a.push(m);  
        slove(c,a,Map);
    }
    else if(pass(l.x+1,l.y,Map))//如果该点下面可以走
    { 
        p m;
        m.x=l.x+1;m.y=l.y;
        vi[m.x][m.y]=1;
        a.push(m);          
        slove(c,a,Map);
    }
    else//四个方向都不能走
    {
        if(a.bout())//回到上一个位置找出路
        {
            slove(c,a,Map);
        }
        else//没路了 
        {
            fout<<"no way";
        }
    } 
}


int main()
{
    fin.open("input.txt");
    fout.open("output.txt");
    int Map[10][10];
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            fin>>Map[i][j];
        }

    p c,r;
    Stack a;

    fin>>r.x>>r.y;
    fin>>c.x>>c.y;

    vi[r.x][r.y]=1;
    a.push(r);//将起点压栈
    slove(c,a,Map);
    if(!a.empty())//求解路径非空则打印路径
    {   
        a.push(c);
        a.sc();
    }   
    return 0;
}
