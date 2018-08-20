#include "iostream"  
#include "string"  
using namespace std;  
  
class SqStack    //ʹ������ʵ��ջ��  
{  
private:  
    struct Node  
    {  
        int content;  
        char word;  
        Node *next;  
    }   ;  
    Node *top,*base;  
public:  
    SqStack();  
    virtual ~SqStack();  
    bool push(char e);  
    bool pop(char &e);  
    bool StackEmpty();  
};  
  
//ջ�Ļ�������  
SqStack::SqStack()  
{  
    top=base=new Node;  
}  
  
SqStack::~SqStack()  
{  
  
}  
  
bool SqStack::push(char e)    //ѹջ����  
{  
    Node *p=new Node;  
    if(p==NULL)  
    {  
        cout<<"Stack is overflow"<<endl;  
        return false;  
    }  
    else  
    {  
        p->word=e;  
        p->next=top;  
        top=p;  
        return true;  
    }  
}  
  
bool SqStack::pop(char &e)    //��ջ����  
{     
    if(top==NULL)  
    {  
        cout<<"Stack is empty"<<endl;  
        return false;  
    }  
    else  
    {  
        if(top==base)  
            return false;  
        Node *p=top;  
        top=top->next;  
        e=p->word;  
        delete p;  
        return true;  
    }  
}  
  
bool SqStack::StackEmpty()  //�ж��Ƿ�Ϊ��ջ  
{  
    return top==base;  
}  
  
class SqQueue    //ʹ������ʵ�ֶ�����  
{  
private:  
    struct Node  
    {  
        int content;  
        char word;  
        Node *next;  
    }   ;  
    Node *head,*last;  
public:  
    SqQueue();  
    virtual ~SqQueue();  
    bool EnQueue(char e);  
    bool DeQueue(char &e);  
    bool QueueEmpty();  
    void OutQueue();  
    void EnQueue_A();  
    void EnQueue_B();  
};  
  
//���еĻ�������  
SqQueue::SqQueue()  
{  
    head=last=new Node;  
}  
  
SqQueue::~SqQueue()  
{  
  
}  
  
bool SqQueue::EnQueue(char e)    //�����  
{  
    Node *p=new Node;  
    if(p==NULL)  
    {  
        cout<<"Queue is overflow"<<endl;  
        return false;   
    }  
    else  
    {  
        p->word=e;  
        last->next=p;  
        last=p;  
        p->next=NULL;  
        return true;  
    }  
}  
bool SqQueue::DeQueue(char &e)    //������  
{  
    if(head==NULL)  
    {  
        cout<<"Queue is empty"<<endl;  
        return false;  
    }  
    else  
    {  
        Node *p=head;  
        head=head->next;  
        e=p->word;  
        delete p;  
        return true;  
    }  
}  
  
void SqQueue::OutQueue()    //��������е�����  
{  
    for(Node *p=head->next;p!=NULL;p=p->next)  
        cout<<p->word;  
    cout<<endl;  
}  
  
bool SqQueue::QueueEmpty()  
{  
    return head==last;  
}  
  
void SqQueue::EnQueue_A()  
{  
    EnQueue('s');  
    EnQueue('a');  
    EnQueue('e');  
}  
  
void SqQueue::EnQueue_B()  
{  
    EnQueue('t');  
    EnQueue_A();  
    EnQueue('d');  
    EnQueue_A();  
}  
  
bool read_language(SqStack &S)        //��ħ�����Ե���ѹ��ջ��  
{  
    int i,n,left=0,right=0;  
    string m;   
    cout<<"������ħ������:"<<endl;  
    cin>>m;  
    n=m.length();      //���ַ�������  
    for(i=0;i<n;i++)  
    {  
        if(m[i]=='(')  
            left++;  
        else if(m[i]==')')  
            right++;  
    }  
    if(left!=right)  
        return false;  
    for(i=n-1;i>=0;i--)  
    {  
        S.push(m[i]);  
    }  
    return true;  
}  
  
void push_and_pop(SqStack &S1,SqStack &S2)      //�������2  
{  
    char e,e1;  
    SqStack S3;    //ջS3��Ϊ����ת�����м����  
    SqStack();  
    while(!S1.StackEmpty())  
    {  
        S1.pop(e);  
        if(e=='(')  
        {  
            S1.pop(e);  
            e1=e;       //e1�б���ľ���ħ�������У��ұߵĵ�һ����ĸ�����ǵڶ��ֹ����еĦ�  
            if(e!=')')  
                S1.pop(e);  
            while(e!=')')  
            {  
                S3.push(e);        
                S1.pop(e);  
            }   
            while(!S3.StackEmpty())  
            {  
                S2.push(e1);    //���ݵڶ��ֽ��͹��򣬽��Ƚ��ж��ѹջ����  
                S3.pop(e);  
                S2.push(e);  
            }  
            S2.push(e1);  
        }  
    }  
}  
  
  
int main(void)  
{  
    char e;  
    bool flag;  
    SqStack S,S1,S2;  
    SqQueue Q;  
    SqStack();  
    SqQueue();  
    flag=read_language(S);     //����ħ������  
    if(!flag)  
    {  
        cout<<"���Ų�ƥ�䣬�޷����ͣ�"<<endl;  
        system("pause");  
        return 0;  
    }  
    while(!S.StackEmpty())  
    {  
        S.pop(e);  
        if(e==')')  
        {  
            S1.push(e);  
            S2.pop(e);  
            while(e!='(')  
            {  
                S1.push(e);  
                S2.pop(e);  
            }  
            if(e=='(')  
                S1.push(e);  
            push_and_pop(S1,S2);  
        }  
        else  
            S2.push(e);  
    }  
   //ħ�����Ե�ǰ�沿����ջS2�ĵײ������沿����ջS2�Ķ�������Ҫת��һ��  
    while(!S2.StackEmpty())  
    {  
        S2.pop(e);  
        S.push(e);    //ħ�����Եĺ��沿����ջS�ĵײ���ǰ�沿����ջS�Ķ���  
    }  
  
    //����Ĳ������е��ǵڶ��ֽ��͹���  
    //����Ĳ������е��ǵ�һ�ֽ��͹���  
    while(!S.StackEmpty())  
    {  
        S.pop(e);  
        if(e=='A')  
            Q.EnQueue_A();  
        if(e=='B')  
            Q.EnQueue_B();  
        else  
            Q.EnQueue(e);  
    }  
    cout<<"ħ�����Կ��Խ���Ϊ:"<<endl;  
    Q.OutQueue();  
    system("pause");  
    return 0;  
} 
