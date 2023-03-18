#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <deque>
using namespace std;

//ջ����ջ��Ԫ������
int top = 0;
//��������
deque<int> Index_Tbale;
//���ű���Ŀ
struct SymItem
{
        string name;//����
        string type;//����
        int dimension;//ά��
        int dec_row;//������
        int ref_row;//������    
        int level;//���𣬱����ͺ���level��ȣ�Ƕ�׺���levelֵ��
};
//����Ŀ
SymItem kong = {"","",-1,-1,-1,1};
//ջʽ���ű�
class SymTable
{
    public:
        //���캯��
        SymTable();
        //����
        SymItem Find(string str);
        //����,�ɹ�����1�����򷵻�-1
        int Insert(string str, string tstr, int n, int dr, int rrs, int level);
        //��λ
        void Locate();
        //�ض�λ
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
    //����û�У����Բ���
    if(Find(str).name == "")
    {
        if(tstr != "func"){
            SymItem item = {str, tstr, n, dr, rrs, level};
            //����
            Stack.push_back(item);
            (*&top)++;
        }
        else{
            //Ƕ�׺���ֱ�Ӷ�λ
            if(level > Stack.back().level)
            {
                //������Ҫ��λ
                Locate();
            }
            //ͬ�ȼ��������ض�λ
            else{
                Relocate();
            }
        }
        
    }
    else{//�������У�����ʧ��
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
        //���ű�ɾ������Ԫ��
        Stack.pop_back();
    }
    //ջʽ���ű�Ҳ��ջ��ɾ��
    Index_Tbale.pop_back();
 }

 int main(int argc, char const *argv[])
 {
    
    return 0;
 }
 