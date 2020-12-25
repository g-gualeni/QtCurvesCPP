#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{

}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100,100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400,400);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setBrush(mBackgroundColor);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(mShapeColor);

    // drawing area
    painter.drawRect(this->rect());
    painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
    
}








