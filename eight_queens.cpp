#include <iostream>
#include<fstream>
using namespace std;

int c[20];//c[i]=j记录的是棋盘中第i行的皇后摆放在第j列
int n=8;
int count=0;//记录所有方案数
ofstream fout;

void print()//画图函数
{
    fout<<"方案"<<count+1<<":"<<endl;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(j == c[i]) fout<<"1 ";
            else fout<<"0 ";
        }
        fout<<endl;
    }
    fout<<endl;
}

void search(int r)
{
    if(r == n)//此时表明八个皇后已经放满了 因此这时的棋盘就是最终的解决方案
    {
        print();
        ++count;
        return;//回溯到前一个函数中，继续寻找可能的解决方案
    }

    for(int i=0; i<n; ++i)//此时八个皇后还没放满
    {
        c[r] = i;//假设第r个皇后放在第i列
        int flag = 1;//判断标志
        for(int j=0; j<r; ++j)//遍历判断如果放在这个位置是否会和前面的皇后冲突
            if(c[r]==c[j] || r-j==c[r]-c[j] || r-j==c[j]-c[r])//分别检验的情况是：r与j摆在了同一列 r与j在同一主对角线 r与j在同一副对角线
            {
                flag = 0;
                break;
            }
        if(flag) 
            search(r+1);//如果这个位置合理，递归求解下一个皇后的位置
    }
}
int main(){
    fout.open("output.txt");
    search(0);//从0开始放皇后
    fout<<"八皇后问题一共有"<<count<<"种解决方案"<<endl;
    return 0;
}
