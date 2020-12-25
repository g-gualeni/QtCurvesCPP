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

    enum ShapesType {Astroid, Cycloid, HuygensCycloid, HypoCycloid};

    QColor backgroundColor() const {return mBackgroundColor;}
    void setBackgroundColor(const QColor &backgroundColor) {mBackgroundColor = backgroundColor;}

    ShapesType shape() const {return mShape;}
    void setShape(const ShapesType &shape) {mShape = shape;}

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

private:
    QColor mBackgroundColor = qRgb(160,160,160);
    QColor mShapeColor = qRgb(255,255,255);
    ShapesType mShape = Astroid;
};

#endif // RENDERAREA_H
