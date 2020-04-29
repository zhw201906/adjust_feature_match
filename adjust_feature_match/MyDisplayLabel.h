#pragma once

#include <QLabel>
#include <QMouseEvent>

class MyDisplayLabel : public QLabel
{
    Q_OBJECT

public:
    MyDisplayLabel(QWidget *parent);
    ~MyDisplayLabel();

    int x() const;
    int y() const;

    void mousePressEvent(QMouseEvent *e);    //鼠标按下事件
	void mouseMoveEvent(QMouseEvent *e);     //鼠标移动事件
	void mouseReleaseEvent(QMouseEvent *e);  //鼠标释放事件
    void paintEvent(QPaintEvent *ev);

signals:
    void mousePress();
	void mouseMove();
	void mouseRelease();

private:
    int x_;
    int y_;


};
