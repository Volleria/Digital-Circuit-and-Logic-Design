#include "myslider2.h"
#include <QKeyEvent>
#include <QDebug>
MySlider2::MySlider2(QWidget *parent) : QSlider(parent)
{

}
//键盘按下事件
void MySlider2::keyPressEvent(QKeyEvent * event1)
{
    switch (event1->key())
    {

        case Qt::Key_Right:
    {
        int a = this->value();
        a=a+1;
        this->setValue(a);
    }
        break;

        case Qt::Key_Left:
    {
        int b = this->value();
        b=b-1;
        this->setValue(b);
    }
        break;
    }
}

//键盘释放事件
void MySlider2::keyReleaseEvent(QKeyEvent *event1)
{

}
