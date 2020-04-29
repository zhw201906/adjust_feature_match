#include "MyDisplayLabel.h"

MyDisplayLabel::MyDisplayLabel(QWidget *parent)
    : QLabel(parent)
{
    x_ = 0;
    y_ = 0;
}

MyDisplayLabel::~MyDisplayLabel()
{
}

int MyDisplayLabel::x() const
{
    return this->x_;
}

int MyDisplayLabel::y() const
{
    return this->y_;
}

void MyDisplayLabel::mousePressEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton)
    {
        x_ = e->x();
        y_ = e->y();
        emit mousePress();
    }
}

void MyDisplayLabel::mouseMoveEvent(QMouseEvent * e)
{
	x_ = e->x();
	y_ = e->y();
	emit mouseMove();
}

void MyDisplayLabel::mouseReleaseEvent(QMouseEvent * e)
{
	x_ = e->x();
	y_ = e->y();
	emit mouseRelease();
}

void MyDisplayLabel::paintEvent(QPaintEvent * ev)
{
    QLabel::paintEvent(ev);
}
