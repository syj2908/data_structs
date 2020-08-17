#include<iostream>
using namespace std;
struct Character//角色类，用来保存人物的名字、国家、武力、智力
{
    string name;
    string kindom;
    int force;
    int intelligence;
};
class List//顺序表
{
    private:
        int maxSize;//最大长度
        int listSize;//表长
        int curr;//当前数据下标
        Character* listArray;//一个character类数组，每个元素里存放着人物信息
    public:
        List(int size)
        {
            maxSize = size; listSize = curr = 0;
            listArray = new Character[maxSize];//listArray指针指向了这块内存的第一个单元，此时指针可以当成数组用
        }
        void append(Character it);//加入元素
        void remove(string it);//删除元素
        void display();//展示所有元素
};
void List::append(Character it)
{
    listArray[listSize++] = it;
}
void List::remove(string it)
{
    for(int i=0;i<listSize;i++)
        if(listArray[i].name==it)
            curr=i;
    for (int i = curr; i < listSize - 1; i++)
        listArray[i] = listArray[i + 1];
    listSize--;
}
void List::display()
{
    for (int i = 0; i < listSize; i++)
        cout << listArray[i].name<<" "<<listArray[i].kindom<<" "<<listArray[i].force<<" "<<listArray[i].intelligence<<endl;
}
int main()
{
    int n;//创建线性表长度
    cin >> n;
    List list(n) ;
    for (int i = 0; i < n; i++)//循环加入元素
    {
        Character character;
        cin>>character.name>>character.kindom>>character.force>>character.intelligence;
        list.append(character);
    }
    string name;//要删除的人物名字
    cin>>name;
    list.display();//展示所有人物
    list.remove(name);
    list.display();//展示删除人物后的剩余人物
    return 0;
}