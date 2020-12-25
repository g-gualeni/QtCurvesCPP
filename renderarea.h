#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    enum ShapesType {Astroid, Cycloid, HuygensCycloid, HypoCycloid, FutureCurve};

    QColor backgroundColor() const {return mBackgroundColor;}
    void setBackgroundColor(const QColor &backgroundColor) {mBackgroundColor = backgroundColor;}

    ShapesType shape() const {return mShape;}
    void setShape(const ShapesType &shape) {mShape = shape; on_shape_changed();}

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
private:
    void on_shape_changed();
    QPointF compute(float t);
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens(float t);
    QPointF compute_hypo(float t);
    QPointF compute_futureCurve(float t);

private:
    QColor mBackgroundColor = qRgb(160,160,160);
    QColor mShapeColor = qRgb(255,255,255);
    ShapesType mShape = Astroid;
    float mIntervalLength = 2*M_PI;
    float mScale = 1;
    int mStepCount = 64;

};

#endif // RENDERAREA_H
