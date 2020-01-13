#ifndef STACK_H
#define STACK_H
#define STACK_INIT_SIZE	100	//初始大小定义为100（可按需修改）
#define STACKINCREMENT	50	//若空间不够，每次增长10（可按需修改）

#include<QString>

class Stack
{
private:
    QString* base;
    QString* top;
    int stacksize;

public:
    Stack();
    ~Stack();
   int StackEmpty();
   int StackFull();
   int GetTop(QString&str);
   int Push(QString&str);
   int Pop(QString&str);


};

#endif // STACK_H
