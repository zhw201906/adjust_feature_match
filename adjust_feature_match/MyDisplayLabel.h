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

    void mousePressEvent(QMouseEvent *e);    //��갴���¼�
	void mouseMoveEvent(QMouseEvent *e);     //����ƶ��¼�
	void mouseReleaseEvent(QMouseEvent *e);  //����ͷ��¼�
    void paintEvent(QPaintEvent *ev);

signals:
    void mousePress();
	void mouseMove();
	void mouseRelease();

private:
    int x_;
    int y_;


};
