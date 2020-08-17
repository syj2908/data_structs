#include<iostream>  
#include<fstream>                                                                                                                            
using namespace std;
ofstream fout;
ifstream fin;
struct MyNode

{
    MyNode(int a_data):m_data(a_data),m_pNext(NULL){}
    int m_data;
    MyNode *m_pNext;
};

class Josephus
{
    public:
        Josephus(int a_N,int b[],int a_M){
            m_N=a_N;
            m_M=a_M;
            for(int i=0;i<a_N;i++)
                a[i]=b[i];
            createList();
            outputList();
        }
        void createList();
        void outputList();
    private:
        MyNode *m_pHead;   //循环链表的头节点
        int m_N;  //链表节点个数
        int m_M;  // 报数出局的数
        int a[20]={0};//每个人的data
};
void Josephus::createList()
{
    MyNode *pre = NULL;
    MyNode *cur = NULL;
    MyNode *p = new MyNode(a[0]);//新建第一个节点
    m_pHead = p;
    cur = p;
    for(int i=2; i<=m_N;i++)
    {
        p = new MyNode(a[i-1]);
        pre = cur;
        cur = p;
        pre->m_pNext = p;
    }
    cur->m_pNext = m_pHead;
    int n = m_N;
    p = m_pHead;
}
void Josephus::outputList()
{
    MyNode *pStart = m_pHead;  
    MyNode *pTemp = pStart;
    MyNode *pPre = NULL;
    MyNode *tobeDeleted = NULL;
    fout << "出局的序列为:" << endl;
    while(pTemp->m_pNext!=pTemp) // 当表中还有大于一个节点存在
    {
        int count = 1; 
        while(count < m_M){
            pPre = pTemp;
            pTemp = pTemp->m_pNext;
            count++;
        }
        tobeDeleted = pTemp;
        pTemp = pTemp->m_pNext;
        pPre->m_pNext = pTemp;
        fout << tobeDeleted->m_data << " ";
    }
    fout << pTemp->m_data << endl;
}

int main()
{
    int n;
    int a[20]={0};
    int m;
    fin.open("input.txt");
    fout.open("output.txt");
    fin >> n;
    for(int i=0;i<n;i++)
        fin>>a[i];
    fin >> m;
    Josephus josephus(n,a,m);
    return 0;
}

/*
    7
    3 1 7 2 4 8 4
    20
*/