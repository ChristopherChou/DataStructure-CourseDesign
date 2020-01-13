#include "stack.h"

Stack::Stack()
{
    base = new QString[STACK_INIT_SIZE];
    top = base;  //栈顶指针指向栈底，表示栈空
    stacksize = STACK_INIT_SIZE;
}

Stack::~Stack()
{
    if(base)
        delete[] base;
}

int Stack::StackEmpty()
{
    if(top==base)
        return true;
    else
        return false;

}

int Stack::StackFull()
{
    if(top-base>=stacksize)
        return true;
    else
        return false;
}

int Stack::GetTop(QString &str)
{
    if(top==base)
        return false;
    str=*(top-1);
    return true;
}

int Stack::Push(QString &str)
{
    if(top-base>=stacksize){
        QString*temp=new QString[stacksize+STACKINCREMENT];
        for(int i=0;i<stacksize;i++)
            temp[i]=base[i];
        delete [] base;
        base=temp;
        stacksize+=STACKINCREMENT;
    }
    *top++=str;
    return true;
}

int Stack::Pop(QString &str)
{
    if(top==base)
        return false;
    else {
        str=*--top;
        return true;
    }
}

