#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <deque>
using namespace std;

//栈顶（栈中元素数）
int top = 0;
//块索引表
deque<int> Index_Tbale;
//符号表条目
struct SymItem
{
        string name;//名字
        string type;//类型
        int dimension;//维度
        int dec_row;//声明行
        int ref_row;//引用行    
        int level;//级别，变量和函数level相等，嵌套函数level值高
};
//空条目
SymItem kong = {"","",-1,-1,-1,1};
//栈式符号表
class SymTable
{
    public:
        //构造函数
        SymTable();
        //检索
        SymItem Find(string str);
        //插入,成功返回1，否则返回-1
        int Insert(string str, string tstr, int n, int dr, int rrs, int level);
        //定位
        void Locate();
        //重定位
        void Relocate();
    private:
        deque<SymItem> Stack;
};

SymItem SymTable::Find(string str)
{
    for (auto item = Stack.rend()-1; item >= Stack.rbegin(); item--) 
    {
        if(item->name == str)
        {
            return *item;
        }
    }
    return kong;
}

int SymTable::Insert(string str, string tstr, int n, int dr, int rrs, int level)
{
    //表中没有，可以插入
    if(Find(str).name == "")
    {
        if(tstr != "func"){
            SymItem item = {str, tstr, n, dr, rrs, level};
            //插入
            Stack.push_back(item);
            (*&top)++;
        }
        else{
            //嵌套函数直接定位
            if(level > Stack.back().level)
            {
                //函数需要定位
                Locate();
            }
            //同等级函数先重定位
            else{
                Relocate();
            }
        }
        
    }
    else{//表中已有，插入失败
        return -1;
    }
}

 void SymTable::Locate()
 {
    (*&top)++;
    Index_Tbale.push_back(top);
 }

 void SymTable::Relocate()
 {
    for (int i = top-1; i >= Index_Tbale.back(); i--) 
    {
        //符号表删除以上元素
        Stack.pop_back();
    }
    //栈式符号表也把栈顶删了
    Index_Tbale.pop_back();
 }

 int main(int argc, char const *argv[])
 {
    
    return 0;
 }
 