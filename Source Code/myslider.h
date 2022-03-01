#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>

class MySlider : public QSlider
{
    Q_OBJECT
public:
    explicit MySlider(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event); //键盘按下事件
    void keyReleaseEvent(QKeyEvent *event); //键盘松开事件

signals:

};

#endif // MYSLIDER_H
