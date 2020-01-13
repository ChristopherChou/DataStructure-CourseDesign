#include "drawgraph.h"
#include<math.h>
#include<QTime>
#include<QTimer>
#include<QApplication>
#include<QEventLoop>


#define MAX_VERTEX_NUM 40
int vexnumber;
int PrimResults[MAX_VERTEX_NUM][2];
int KruskalResults[MAX_VERTEX_NUM][2];

void Delay_MSec(unsigned int msec)
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}

DrawGraph::DrawGraph(QWidget *parent)
    : QWidget(parent)
{
    over=false;
    mark=1;
    this->startTimer(2000);
    if(mark>vexnumber)
        over=true;

}

int DrawGraph::CaculateX(int number)
{
    return (500+400*cos(3.14*2*number/vexnumber));
}

int DrawGraph::CaculateY(int number)
{
    return (500+400*sin(3.14*2*number/vexnumber));
}

void DrawGraph::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);
    QPainter paint(this);
    QFont font;
    font.setPointSize(15);
    paint.setFont(font);
    paint.drawText(50,50,"2.1 用Prim算法构造最小生成树");
    for(int i=0;i<vexnumber;i++)
        paint.drawText(CaculateX(i),CaculateY(i),QString('A'+i));

    paint.setPen(QColor(0, 160, 230));

    for(int i=1;i<mark;i++)
    {
        paint.drawLine(CaculateX(PrimResults[i][0]),CaculateY(PrimResults[i][0]),CaculateX(PrimResults[i][1]),CaculateY(PrimResults[i][1]));

    }


}

void DrawGraph::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    mark++;
    if(mark<=vexnumber)
        this->update();

}
