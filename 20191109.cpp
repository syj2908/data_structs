#include<iostream>
#include<vector>//容器库
#include<algorithm>//sort函数所在库
using namespace std;

struct Character//角色类，用来保存人物的名字、国家、武力、智力
{
    string name;
    string kindom;
    int force;
    int intelligence;
};

bool cmp(Character A,Character B)//重新定义排序规则
{
        return A.intelligence>B.intelligence;// >是从大到小 <是从小到大
}

int main()
{
    vector<Character>con;//声明一个叫con的容器，里面装的数据类型是Character
    vector<Character>::iterator it;//it是一个迭代器，专门用来遍历vector
    int n;

    cin>>n;

    for(int i=0;i<n;i++)
    {
        Character character;
        cin>>character.name>>character.kindom>>character.force>>character.intelligence;
        con.push_back(character);//向容器最后面追加一个元素
    }

    string name;
    cin>>name;


    sort(con.begin(),con.end(),cmp);//最后一个参数是用来自定义排序规则的 不写的话默认是升序排列(从小到大)
    
    
    for(it=con.begin();it!=con.end();++it)//迭代器遍历数组的规范 注意是++it
    {
        cout<<(*it).name<<" "<<(*it).kindom<<" "<<(*it).force<<" "<<(*it).intelligence<<endl;
        //这里的（*it）要加括号 不然会错（为什么呢）
    }


    for(it=con.begin();it!=con.end();++it)//容器删除操作 固定格式
    {
        if((*it).name==name)
        {
            con.erase(it);
        }
    }


    for(it=con.begin();it!=con.end();++it)
    {
        cout<<(*it).name<<" "<<(*it).kindom<<" "<<(*it).force<<" "<<(*it).intelligence<<endl;
    }


    return 0;

}