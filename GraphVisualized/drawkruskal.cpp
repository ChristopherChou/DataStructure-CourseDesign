#include "drawkruskal.h"

drawKruskal::drawKruskal(QWidget *parent)
{
    mark=1;
    this->startTimer(2000);

}

int drawKruskal::CaculateX(int number)
{
    return (500+400*cos(3.14*2*number/vexnumber));
}

int drawKruskal::CaculateY(int number)
{
    return (500+400*sin(3.14*2*number/vexnumber));
}

void drawKruskal::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter paint(this);
    QFont font;
    font.setPointSize(15);
    paint.setFont(font);
    paint.drawText(50,50,"2.2 用Kruskal算法构造最小生成树");
    for(int i=0;i<vexnumber;i++)
        paint.drawText(CaculateX(i),CaculateY(i),QString('A'+i));

    paint.setPen(QColor(0, 160, 230));

    for(int i=0;i<mark;i++)
    {
        paint.drawLine(CaculateX(KruskalResults[i][0]),CaculateY(KruskalResults[i][0]),CaculateX(KruskalResults[i][1]),CaculateY(KruskalResults[i][1]));

    }


}

void drawKruskal::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    mark++;
    if(mark<=vexnumber)
    this->update();
}
