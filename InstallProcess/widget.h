#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QDialog>
#include<QLineEdit>
#include<QPlainTextEdit>
#include"stack.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void inputNumber();
    void definePath();
    void selectName();
    void Process();

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


    QDialog *d1;
    QDialog *d2;
    QDialog *d3;
    QDialog *d4;

    QLineEdit *edit1;
    QLineEdit* edit2;

    QLineEdit** names;

    Stack* stack1;
    Stack* stack2;

    QPlainTextEdit* p1;
    QPlainTextEdit* p2;

   // QString find;
    int num;

};

#endif // WIDGET_H
