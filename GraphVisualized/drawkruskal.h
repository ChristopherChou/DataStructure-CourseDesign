#ifndef DRAWKRUSKAL_H
#define DRAWKRUSKAL_H
#include <QWidget>
#include<QPainter>
#include <QtMath>
#include <QDebug>
#define MAX_VERTEX_NUM 40

extern int vexnumber;
extern int PrimResults[MAX_VERTEX_NUM][2];
extern int KruskalResults[MAX_VERTEX_NUM][2];

class drawKruskal:public QWidget
{
public:
    drawKruskal(QWidget *parent = 0);
    int CaculateX(int number);
    int CaculateY(int number);

protected:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);

    int mark;

};

#endif // DRAWKRUSKAL_H
