#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QFont font;
    font.setPointSize(25);
    setMinimumSize(1000,500);
    setWindowTitle("Install Process");
    label1=new QLabel(this);
    label1->setText("产品维修教学系统");
    label1->setGeometry(200,50,600,100);
    label1->setFont(font);
    label1->show();

    font.setPointSize(15);
    button1=new QPushButton(this);
    button1->setText("点击进入");
    button1->setGeometry(400,250,200,50);
    button1->setFont(font);
    button1->show();

    connect(button1,&QPushButton::clicked,this,&Widget::inputNumber);


}

Widget::~Widget()
{

}

void Widget::inputNumber()
{
    this->hide();
    QFont font;
    font.setPointSize(15);
    d1=new QDialog(this);
    d1->setMinimumSize(1000,500);
    d1->setFont(font);
    d1->show();

    label2=new QLabel(d1);
    label2->setGeometry(50,150,550,50);
    label2->setText("请输入产品需要装配的零件数目");
    label2->show();

    edit1=new QLineEdit(d1);
    edit1->setGeometry(650,150,200,50);
    edit1->show();

    button2=new QPushButton(d1);
    button2->setText("确定");
    button2->setGeometry(400,350,200,50);
    button2->show();
    connect(button2,&QPushButton::clicked,this,&Widget::definePath);



}

void Widget::definePath()
{
    QString number=edit1->text();
    num=number.toInt();
    if(num==0)
    {
        label3=new QLabel(d1);
        label3->setText("输入错误，请重新输入");
        label3->setGeometry(100,300,600,40);
        label3->show();
        edit1->setText("");
    }
    else {
        QFont font;
        font.setPointSize(15);
        d1->hide();
        d2=new QDialog(this);
        d2->setFont(font);
        d2->setMinimumSize(1000,1000);
        d2->show();

        label4=new QLabel(d2);
        label4->setGeometry(50,20,800,50);
        label4->setText("Input the names of the componemt");
        label4->show();
        names=new QLineEdit*[num];

        for(int i=0;i<num;i++)
        {
            names[i]=new QLineEdit(d2);
            names[i]->setGeometry(50,100+i*50,400,40);
            names[i]->show();
        }
        button3=new QPushButton(d2);
        button3->setText("确定");
        button3->setGeometry(800,20,150,50);
        button3->show();
        connect(button3,&QPushButton::clicked,this,&Widget::selectName);
    }


}

void Widget::selectName()
{
    stack1=new Stack;
    stack2=new Stack;
    QString str;
    for(int i=0;i<num;i++)
    {
        str=names[i]->text();
        stack1->Push(str);
    }
    d2->hide();

    d3=new QDialog(this);
    QFont font;
    font.setPointSize(15);
    d3->setMinimumSize(1000,500);
    d3->setFont(font);
    d3->show();

    label5=new QLabel(d3);
    label5->setGeometry(50,150,550,50);
    label5->setText("请输入需要更换的零件名称");
    label5->show();

    edit2=new QLineEdit(d3);
    edit2->setGeometry(650,150,200,50);
    edit2->show();

    button4=new QPushButton(d3);
    button4->setText("确定");
    button4->setGeometry(400,350,200,50);
    button4->show();
    connect(button4,&QPushButton::clicked,this,&Widget::Process);

}

void Widget::Process()
{
    QString str1;
    QString str2;
    QString find;
    QString temp;
    find=edit2->text();

    do{

        stack1->Pop(temp);
        str1+=temp;
        str1+="->";
        stack2->Push(temp);
        if(find==temp)
            break;
    }while(true);


    while(!stack2->StackEmpty())
    {
        stack2->Pop(temp);
        str2+=temp;
        str2+="->";
    }


    QFont font;
    font.setPointSize(15);
    d3->hide();
    d4=new QDialog(this);
    d4->setFont(font);
    d4->setMinimumSize(1000,1000);

    label6=new QLabel(d4);
    label6->setText("Disassemble Path:");
    label6->setGeometry(50,20,500,50);
    label6->show();
    label7=new QLabel(d4);
    label7->setText("Install Path:");
    label7->setGeometry(50,520,500,50);
    label7->show();

    p1=new QPlainTextEdit(d4);
    p1->setGeometry(50,100,900,400);
    p1->appendPlainText(str1);
    p1->show();

    p2=new QPlainTextEdit(d4);
    p2->setGeometry(50,600,900,400);
    p2->appendPlainText(str2);
    p2->show();

    d4->show();


}
