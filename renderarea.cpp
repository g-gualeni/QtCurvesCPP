#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{

}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400,400);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400,400);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);

    // drawing area
    painter.drawRect(this->rect());
    QPoint center = this->rect().center();

    float step = mIntervalLength / mStepCount;
    float t=0;
    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX(prevPoint.x() * mScale + center.x());
    prevPixel.setY(prevPoint.y() * mScale + center.y());

    while(t < mIntervalLength)
    {
        QPointF point = compute(t);

        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());

        // painter.drawPoint(pixel);
        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
        t+=step;
    }

    QPointF point = compute(mIntervalLength);
    QPoint pixel;
    pixel.setX(point.x() * mScale + center.x());
    pixel.setY(point.y() * mScale + center.y());
}

QPointF RenderArea::compute_astroid(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 2*cos_t*cos_t*cos_t;
    float y = 2*sin_t*sin_t*sin_t;
    return QPointF(x,y);
}

QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF(
        1.5*(1-cos(t)), // X
        1.5*(t-sin(t))  // Y
        );

}

QPointF RenderArea::compute_huygens(float t)
{
    return QPointF(
        4 * (3 * cos(t) - cos(3 * t)), // X
        4 * (3 * sin(t) - sin(3 * t))  // Y
        );
}

QPointF RenderArea::compute_hypo(float t)
{
    return QPointF(
        1.5 * (2 * cos(t) + cos(2*t)), // X
        1.5 * (2 * sin(t) - sin(2*t))  // Y
        );
}

QPointF RenderArea::compute_line(float t)
{
    return QPointF(1-t,
            1-t);

}

QPointF RenderArea::compute_circle(float t)
{
    return QPointF(
        cos(t),
        sin(t)
        );
}

QPointF RenderArea::compute_ellipse(float t)
{
    return QPointF(
        2.0 * cos(t),
        1.1 * sin(t)
        );
}

QPointF RenderArea::compute_fancy(float t)
{
    return QPointF(
        11*cos(t) - 6*cos(t*11.0/6.0), // X
        11*sin(t) - 6*sin(t*11.0/6.0)  // Y
        );
}

QPointF RenderArea::compute_starfish(float t)
{
    float R = 5.0;
    float r = 3.0;
    float d = 5.0;
    return QPointF(
        (R-r)*cos(t) + d*cos(t*(R-r)/r),
        (R-r)*sin(t) - d*sin(t*(R-r)/r)
        );
}

void RenderArea::on_shape_changed()
{
    switch (mShape) {

    case Astroid:
        mScale = 40;
        mIntervalLength = 2*M_PI;
        mStepCount = 256;
        break;

    case Cycloid:
        mScale = 4;
        mIntervalLength = 6 * M_PI;
        mStepCount = 128;
        break;

    case HuygensCycloid:
        mScale = 4;
        mIntervalLength = 4*M_PI;
        mStepCount = 256;
        break;

    case HypoCycloid:
        mScale = 15;
        mIntervalLength = 2*M_PI;
        mStepCount = 256;
        break;

    case Line:
        mIntervalLength = 1;
        mScale = 50;
        mStepCount = 128;
        break;

    case Circle:
        mIntervalLength = 2*M_PI;
        mScale = 100;
        mStepCount = 512;
        break;

    case Ellipse:
        mIntervalLength = 2*M_PI;
        mScale = 75;
        mStepCount = 128;
        break;

    case Fancy:
        mIntervalLength = 12*M_PI;
        mScale = 10;
        mStepCount = 512;
        break;

    case Starfish:
        mIntervalLength = 6*M_PI;
        mScale = 25;
        mStepCount = 256;
        break;

    default:
        break;
    }
}

QPointF RenderArea::compute(float t)
{
    switch (mShape) {

    case Astroid:
        return compute_astroid(t);
        break;

    case Cycloid:
        return compute_cycloid(t);
        break;

    case HuygensCycloid:
        return compute_huygens(t);
        break;

    case HypoCycloid:
        return compute_hypo(t);
        break;

    case Line:
        return compute_line(t);
        break;

    case Circle:
        return compute_circle(t);
        break;
    case Ellipse:
        return compute_ellipse(t);
        break;

    case Fancy:
        return compute_fancy(t);
        break;

    case Starfish:
        return compute_starfish(t);
        break;

    default:
        break;
    }
    return QPointF();
}








