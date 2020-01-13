#include "widget.h"
#include<string>
#include<windows.h>
#include<QScrollArea>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Graph visualize");
    setMinimumSize(1000,500);
    showNormal();
    QFont font;
    font.setPointSize(15);
    setFont(font);


    button1=new QPushButton(this);
    button1->setGeometry(200,100,600,100);
    button1->setText("Input a new graph");
    button1->show();

    button2=new QPushButton(this);
    button2->setGeometry(200,250,600,100);
    button2->setText("Use the default graph");
    button2->show();

    G=new Graph;
    connect(button1,&QPushButton::clicked,this,&Widget::InputGraph);
    connect(button2,&QPushButton::clicked,this,&Widget::DefaultGraph);


}

Widget::~Widget()
{
}

void Widget::InputGraph()
{
    this->hide();
    QFont font;
    font.setPointSize(15);
    d1=new QDialog(this);
    d1->setFont(font);
    d1->setMinimumSize(1000,800);
    d1->show();

    label1=new QLabel(d1);
    label1->setText("请输入图的顶点数");
    label1->setGeometry(100,90,400,100);
    label1->show();

    label2=new QLabel(d1);
    label2->setText("输入边数");
    label2->setGeometry(100,220,400,100);
    label2->show();

    label3=new QLabel(d1);
    label3->setText("输入错误，请重新输入");
    label3->setGeometry(110,580,641,101);
    //label3->show();


    edit1=new QLineEdit(d1);
    edit1->setGeometry(480,120,300,40);
    edit1->show();

    edit2=new QLineEdit(d1);
    edit2->setGeometry(480,250,300,40);
    edit2->show();

    button3=new QPushButton(d1);
    button3->setGeometry(500,420,270,50);
    button3->setText("确定");
    button3->show();

    connect(button3,&QPushButton::clicked,this,&Widget::Check1);



}

void Widget::Check1()
{
    QString vexnumstr=edit1->text();
    QString arcnumstr=edit2->text();
    vexnum=vexnumstr.toInt();
    arcnum=arcnumstr.toInt();
    if(vexnum==0||arcnum==0){
        label3->show();
        edit1->setText("");
        edit2->setText("");
    }
    else {
        d1->hide();

        d2=new QDialog(this);
        d2->setWindowTitle("Input Sides");
        d2->setMinimumSize(1000,1200);
        QFont font;
        font.setPointSize(15);
        d2->setFont(font);
        d2->show();

        label4=new QLabel(d2);
        label4->setText("Input the side(point and weight),point use ABC...");
        label4->setGeometry(50,20,900,40);
        label4->show();

        button4=new QPushButton(d2);
        button4->setGeometry(850,100,100,50);
        button4->setText("OK");
        button4->show();
        connect(button4,&QPushButton::clicked,this,&Widget::InitGraph);

        for (int i=0;i<arcnum;i++) {
            PointLabel1[i]=new QLabel(d2);
            PointLabel1[i]->setText("Start");
            PointLabel1[i]->setGeometry(50,140+i*50,100,40);
            PointLabel1[i]->show();

            PointLabel2[i]=new QLabel(d2);
            PointLabel2[i]->setText("End");
            PointLabel2[i]->setGeometry(300,140+i*50,100,40);
            PointLabel2[i]->show();

            PointLabel3[i]=new QLabel(d2);
            PointLabel3[i]->setText("Weight");
            PointLabel3[i]->setGeometry(550,140+i*50,100,40);
            PointLabel3[i]->show();

            SideEdit1[i]=new QLineEdit(d2);
            SideEdit1[i]->setGeometry(175,140+i*50,100,40);
            SideEdit1[i]->show();
            SideEdit2[i]=new QLineEdit(d2);
            SideEdit2[i]->setGeometry(425,140+i*50,100,40);
            SideEdit2[i]->show();
            SideEdit3[i]=new QLineEdit(d2);
            SideEdit3[i]->setGeometry(675,140+i*50,100,40);
            SideEdit3[i]->show();

        }
    }
}

void Widget::DefaultGraph()
{
    this->hide();
    G->CreateGraphDefault();
    Process();

}

void Widget::InitGraph()
{
    d2->hide();
    arcstruct=new arc[arcnum];
    for (int i=0;i<arcnum;i++) {
        QString temp;
        temp=SideEdit1[i]->text();
        std::string temp1=temp.toStdString();
        arcstruct[i].a=temp1[0];

        temp=SideEdit2[i]->text();
        temp1=temp.toStdString();
        arcstruct[i].b=temp1[0];

        temp=SideEdit3[i]->text();
        arcstruct[i].weight=temp.toInt();
    }

    G->CreateGraph(vexnum,arcnum,arcstruct);
    Process();
}


void Widget::Process()
{
    d3=new QDialog(this);
    QFont font;
    font.setPointSize(15);
    d3->setFont(font);
    d3->setMinimumSize(1500,1000);
    d3->show();
    G->ShowLinkList(d3);
    d3->exec();

    G->Prim('A');
    draw1=new DrawGraph;
    draw1->setWindowTitle("Prim");
    draw1->setMinimumSize(1000,1000);
    draw1->show();



    Delay_MSec(2000*(vexnumber+1));
    draw1->hide();

    G->Kruskal();
    draw2=new drawKruskal;
    draw2->setWindowTitle("Kruskal");
    draw2->setMinimumSize(1000,1000);
    draw2->show();

    Delay_MSec(2000*(vexnumber+1));
    draw2->hide();



    d4=new QDialog(this);
    d4->setWindowTitle("DIj");
    d4->setFont(font);
    d4->setMinimumSize(1000,500);
    d4->show();

    label5=new QLabel(d4);
    label5->setText("请输入某一顶点编号");
    label5->setGeometry(50,150,400,40);
    label5->show();
    edit3=new QLineEdit(d4);
    edit3->setGeometry(500,150,200,50);
    edit3->show();
    button5=new QPushButton(d4);
    button5->setText("OK");
    button5->setGeometry(200,300,200,50);
    button5->show();
    connect(button5,&QPushButton::clicked,this,&Widget::DIJ);



}

void Widget::DIJ()
{
    QString str=edit3->text();
    std::string temp=str.toStdString();
    int v0=temp[0]-'A';

    d4->hide();
    d5=new QDialog(this);
    QFont font;
    font.setPointSize(15);
    d5->setFont(font);
    d5->setMinimumSize(1500,1000);
    d5->show();

    label6=new QLabel(d5);
    label6->setText("3.The minDistance from the input point");
    label6->setGeometry(50,20,800,50);
    label6->show();
    G->DIJPath(v0,d5);

    button6=new QPushButton(d5);
    button6->setText("Next");
    button6->setGeometry(1000,20,200,50);
    button6->show();

    connect(button6,&QPushButton::clicked,this,&Widget::Floyd);


}

void Widget::Floyd()
{
    d5->hide();
    d6=new QDialog(this);
    d6->setWindowTitle("Floyd");
    QFont font;
    font.setPointSize(15);
    d6->setFont(font);
    d6->setMinimumSize(1500,1000);
    d6->show();

    label7=new QLabel(d6);
    label7->setText("4.The minDistance between every point");
    label7->setGeometry(50,20,800,50);
    label7->show();
    G->FLOYDPath(d6);

}


