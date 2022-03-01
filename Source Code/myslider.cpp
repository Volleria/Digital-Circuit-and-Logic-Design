#include "myslider.h"
#include <QKeyEvent>

MySlider::MySlider(QWidget *parent) : QSlider(parent)
{

}
//键盘按下事件
void MySlider::keyPressEvent(QKeyEvent * event)
{
    switch (event->key())
    {

        case Qt::Key_Up:
    {
        int a = this->value();
        a=a+1;
        this->setValue(a);
    }
        break;

        case Qt::Key_Down:
    {
        int b = this->value();
        b=b-1;
        this->setValue(b);
    }
        break;
    }


}

//键盘释放事件
void MySlider::keyReleaseEvent(QKeyEvent *event)
{

}
