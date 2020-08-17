#include <iostream>
#include <string>
#include <stack>
using namespace std;


const int MAX_VERTEX_NUM=100;//最大课程总数

typedef struct ArcBox//节点
{
    int tailvex;
    int headvex;
    ArcBox *headlink;
    ArcBox *taillink;
    ArcBox(int tailv, int headv, ArcBox *headl = nullptr, ArcBox *taill = nullptr) 
    {
        tailvex=tailv;
        headvex=headv;
        headlink=headl;
        taillink=taill;
    }
}ArcNode;

typedef struct VexNode//课程信息
{
    string classid; //课程号
    int credit;//学分
    int indegree;//入度
    int state;//1代表已学，0代表未学
    ArcBox *firstin;
    ArcBox *firstout;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;

int getPosition(string &el,ALGraph &G)
{
    int i;
    for (i = 1; i <= G.vexnum; i++)
    {
        if (G.vertices[i].classid==el)
            return i;
    }
    return -1;
}

void CreateGraph(ALGraph &G)//构建图
{
    int i,p1,p2;
    string m,n;
    ArcNode *enode;
    cout<<"请输入需要编排课程总数:"<<endl;
    cin>>G.vexnum;
    for( i=1;i<=G.vexnum;i++)
    {
        cout<<"请输入课程号:"<<endl;
        cin>>G.vertices[i].classid;
        cout<<"请输入该课程的学分:"<<endl;
        cin>>G.vertices[i].credit;
        G.vertices[i].indegree=0;
        G.vertices [i].state=0;//未学习
        G.vertices[i].firstin=nullptr;
        G.vertices[i].firstout=nullptr;
    }
    cout<<"请输入课程先修关系总数："<<endl;
    cin>>G.arcnum;
    cout<<"请顺序输入每个课程先修关系:"<<endl;
    for (i = 1; i <= G.arcnum; i++)//建立先修关系
    {
        cout<<"第"<<i<<"条关系："<<endl;
        cin>>n>>m;
        p1=getPosition(n, G);
        p2=getPosition(m, G);
        G.vertices[p2].indegree++;
        enode = new ArcBox(p1, p2, nullptr, nullptr);
        if (G.vertices[p1].firstout==nullptr)
            G.vertices[p1].firstout = enode;
        else
        {
            ArcBox *move = G.vertices[p1].firstout;
            while (move->taillink != nullptr)
                move = move->taillink;
            move->taillink = enode;
        }
        if (G.vertices[p2].firstin==nullptr)
            G.vertices[p2].firstin = enode;
        else
        {
            ArcBox *move = G.vertices[p2].firstin;
            while (move->headlink != nullptr)
                move = move->headlink;
            move->headlink = enode;
        }
    }
}


void TopologicalSort_1(ALGraph G,int numterm,int uplcredit)//课程尽可能集中到前几个学期
{
    struct ArcBox *p;
    stack<int> S;
    int i,j,k;
    int count; //课程编括排数目计数器
    int sumcredit;//每个学期的课程学分累加器
    count=0;
    k=0;
    while(count!=G.vexnum && k<=numterm)
    {
        sumcredit=0;
        for(i=1;i<=G.vexnum;i++)
            if((G.vertices[i].indegree==0)&&(G.vertices[i].state==0))//无先修的课程入栈
            {
                S.push(i);
                G.vertices[i].state =1;//标记已入栈
            }
        if((!S.empty())&&(sumcredit<=uplcredit))
        {
            k= k+1;
            cout<<endl;
            cout<<"第"<<k<<"个学期学得课程有:"<<endl;
            sumcredit = 0;
            for(i=1;i<=G.vexnum;i++)
                if((G.vertices[i].indegree==0)&&(G.vertices[i].state==0))//即无先修的课程入栈
                    S.push(i);
            while((!S.empty())&&(sumcredit<uplcredit))//栈非空&&学分总数小于总学分上限
            {
                j=S.top();
                S.pop();
                sumcredit = sumcredit + G.vertices[j].credit;
                if(sumcredit <= uplcredit)
                {
                    cout<<G.vertices[j].classid<<" ";
                    count++;
                    for(p=G.vertices[j].firstout;p;p=p->taillink)//对j号顶点每个邻接点的入度减一
                        G.vertices[p->headvex].indegree--;
                }
                else S.push(j);//将未输出的节点重新压入栈
            }
        }
    }
    cout<<endl;
    if(count<G.vexnum)
        cout<<"\n课程编排出错\n";
    else
    {
        cout<<endl<<"课程编排成功"<<endl;
    }
}

void TopologicalSort_2(ALGraph G,int numterm,int uplcredit)//课程尽量均匀分布
{
    struct ArcBox *p;
    stack<int> S;

    int i,j,k;
    int maxnum;
    int sumnum;
    int count; //课程编排数目计数器
    int sumcredit;//每个学期的课程学分累加器
    count=0;
    k=0;
    maxnum=G.vexnum/numterm+1;
    sumnum=0;
    while(count!=G.vexnum && k<=numterm)
    {
        sumcredit=0;
        for(i=1;i<=G.vexnum;i++)
            if((G.vertices[i].indegree==0)&&(G.vertices[i].state==0))//入度为零的节点入栈，即无先修的课程入栈
            {
                S.push(i);
                G.vertices[i].state =1;//避免入度为零节点重复入栈
            }
        if((!S.empty())&&(sumcredit<=uplcredit))
        {
            k= k+1;
            cout<<endl;
            cout<<"第"<<k<<"个学期学得课程有:"<<endl;
            sumcredit = 0;
            sumnum=0;
            for(i=1;i<=G.vexnum;i++)//入度为零的节点入栈，即无先修的课程入栈
                if((G.vertices[i].indegree==0)&&(G.vertices[i].state==0))
                    S.push(i);
            while((!S.empty())&&(sumcredit<uplcredit)&&(sumnum<maxnum))//栈非空&&学分总数小于学分上限&&不超过每学期课程上限
            {
                j=S.top();
                S.pop();
                sumcredit = sumcredit + G.vertices[j].credit;
                sumnum=sumnum+1;
                if((sumcredit<=uplcredit)&&(sumnum<=maxnum))
                {
                    cout<<G.vertices[j].classid<<" ";
                    count++;
                    for(p=G.vertices[j].firstout;p;p=p->taillink)//对j号顶点每个邻接点的入度减一
                        G.vertices[p->headvex].indegree--;
                }
                else S.push(j);//将未输出的节点重新压入栈
            }
        }
    }
    cout<<endl;
    if(count<G.vexnum)
        cout<<"\n课程编排出错\n";
    else
    {
        cout<<endl<<"课程编排成功"<<endl;
    }
}

int main()
{

    int numterm;//学期总数
    int uplcredit; //一个学期的学分上限
    int selectway;
    ALGraph G;
    cout<<"请输入学期总数:"<<endl;
    cin>>numterm;
    cout<<"请输入一个学期的学分上限:"<<endl;
    cin>>uplcredit;
    CreateGraph(G);
        cout<<"请选择编排策略:1.课程尽可能集中到前几个学期；2.课程尽量均匀分布"<<endl;
        cin>>selectway;
        if(selectway==1)
            TopologicalSort_1(G,numterm,uplcredit);
        if(selectway==2)
            TopologicalSort_2(G,numterm,uplcredit);
    return 0;
}
