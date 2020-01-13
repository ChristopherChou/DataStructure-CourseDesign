#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H
#include <QWidget>
#include<QPainter>
#include <QtMath>
#include <QDebug>

class DrawGraph :public QWidget
{
public:
    DrawGraph(QWidget *parent = 0);

    int CaculateX(int number);
    int CaculateY(int number);

    bool over;

protected:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);

    int mark;


};

#endif // DRAWGRAPH_H
