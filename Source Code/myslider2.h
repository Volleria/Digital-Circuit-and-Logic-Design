#ifndef MYSLIDER2_H
#define MYSLIDER2_H

#include <QSlider>

class MySlider2 : public QSlider
{
    Q_OBJECT
public:
    explicit MySlider2(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event); //键盘按下事件
    void keyReleaseEvent(QKeyEvent *event); //键盘松开事件

signals:

};

#endif // MYSLIDER2_H
