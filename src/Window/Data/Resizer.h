#pragma once

#include <QWidget>

namespace ads
{

class SizeRubberBand;

class Resizer : public QWidget
{
    Q_OBJECT
public:
    Resizer(Qt::Edges edges, SizeRubberBand* sizeRubberBand);

    virtual void updateGeometry(const QRect& geometry, int gripSize) = 0;

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    SizeRubberBand* m_sizeRubberBand = nullptr;
    Qt::Edges m_edges;
};

class NResizer : public Resizer
{
public:
    NResizer(SizeRubberBand* sizeRubberBand)
        : Resizer(Qt::TopEdge, sizeRubberBand)
    {}

    void updateGeometry(const QRect& geometry, int gripSize) override;

protected:
};

class SResizer : public Resizer
{
public:
    SResizer(SizeRubberBand* sizeRubberBand)
        : Resizer(Qt::BottomEdge, sizeRubberBand)
    {}

    void updateGeometry(const QRect& geometry, int gripSize) override;

protected:
};

class WResizer : public Resizer
{
public:
    WResizer(SizeRubberBand* sizeRubberBand)
        : Resizer(Qt::LeftEdge, sizeRubberBand)
    {}

    void updateGeometry(const QRect& geometry, int gripSize) override;

protected:
};

class EResizer : public Resizer
{
public:
    EResizer(SizeRubberBand* sizeRubberBand)
        : Resizer(Qt::RightEdge, sizeRubberBand)
    {}

    void updateGeometry(const QRect& geometry, int gripSize) override;

protected:
};

class NWResizer : public Resizer
{
public:
    NWResizer(SizeRubberBand* sizeRubberBand)
        : Resizer(Qt::TopEdge | Qt::LeftEdge, sizeRubberBand)
    {}

    void updateGeometry(const QRect& geometry, int gripSize) override;

protected:
};

class NEResizer : public Resizer
{
public:
    NEResizer(SizeRubberBand* sizeRubberBand)
        : Resizer(Qt::TopEdge | Qt::RightEdge, sizeRubberBand)
    {}

    void updateGeometry(const QRect& geometry, int gripSize) override;

protected:
};

class SWResizer : public Resizer
{
public:
    SWResizer(SizeRubberBand* sizeRubberBand)
        : Resizer(Qt::BottomEdge | Qt::LeftEdge, sizeRubberBand)
    {}

    void updateGeometry(const QRect& geometry, int gripSize) override;

protected:
};

class SEResizer : public Resizer
{
public:
    SEResizer(SizeRubberBand* sizeRubberBand)
        : Resizer(Qt::BottomEdge | Qt::RightEdge, sizeRubberBand)
    {}

    void updateGeometry(const QRect& geometry, int gripSize) override;

protected:
};

}  // namespace ads
