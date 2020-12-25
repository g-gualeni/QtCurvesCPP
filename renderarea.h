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

    enum ShapesType {Astroid, Cycloid, HuygensCycloid, HypoCycloid, Line};

    QColor backgroundColor() const {return mBackgroundColor;}
    void setBackgroundColor(const QColor &backgroundColor) {mBackgroundColor = backgroundColor; repaint();}

    QColor shapeColor() const{return mShapeColor;}
    void setShapeColor(const QColor &shapeColor) {mShapeColor = shapeColor; repaint();}

    ShapesType shape() const {return mShape;}
    void setShape(const ShapesType &shape) {mShape = shape; on_shape_changed();}

    void setScale(float scale) {mScale = scale; repaint();}
    float scale() const {return mScale;}

    float intervalLength() const {return mIntervalLength;}
    void setIntervalLength(float intervalLength) {mIntervalLength = intervalLength; repaint();}

    int stepCount() const {return mStepCount;}
    void setStepCount(int stepCount) {mStepCount = stepCount; repaint();}


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
    QPointF compute_line(float t);

private:
    QColor mBackgroundColor = qRgb(160,160,160);
    QColor mShapeColor = qRgb(255,255,255);
    ShapesType mShape = Astroid;
    float mIntervalLength = 2*M_PI;
    float mScale = 1;
    int mStepCount = 64;

};

#endif // RENDERAREA_H
