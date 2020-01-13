#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QDialog>
#include<QLineEdit>
#include<QPainter>
#include<drawgraph.h>
#include"graph.h"
#include"drawkruskal.h"

extern void Delay_MSec(unsigned int msec);

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void InputGraph();
    void Check1();

    void DefaultGraph();
    void InitGraph();

    void Process();
    void DIJ();
    void Floyd();

private:
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* label4;
    QLabel* label5;
    QLabel* label6;
    QLabel* label7;


    QPushButton* button1;
    QPushButton* button2;
    QPushButton* button3;
    QPushButton* button4;
    QPushButton* button5;
    QPushButton* button6;

    QDialog* d1;
    QDialog* d2;
    QDialog* d3;
    QDialog* d4;
    QDialog* d5;
    QDialog* d6;

    QLineEdit* edit1;
    QLineEdit* edit2;
    QLineEdit* edit3;

    //输入边
    QLabel* PointLabel1[MAX_VERTEX_NUM];
    QLabel* PointLabel2[MAX_VERTEX_NUM];
    QLabel* PointLabel3[MAX_VERTEX_NUM];
    QLineEdit* SideEdit1[MAX_VERTEX_NUM];
    QLineEdit* SideEdit2[MAX_VERTEX_NUM];
    QLineEdit* SideEdit3[MAX_VERTEX_NUM];

    Graph* G;
    arc* arcstruct;

    DrawGraph *draw1;
    drawKruskal *draw2;

    int vexnum;
    int arcnum;

};

#endif // WIDGET_H
