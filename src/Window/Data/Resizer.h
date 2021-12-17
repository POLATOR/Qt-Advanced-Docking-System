#pragma once

#include <QWidget>

namespace ads {

class SizeRubberBand;

class Resizer : public QWidget
{
    Q_OBJECT
public:
    Resizer(Qt::CursorShape cursorShape, SizeRubberBand * sizeRubberBand);

    virtual void updateGeometry(const QRect & geometry, int gripSize) = 0;

protected:
    int adjustHeight(int height) const;

    int adjustWidth(int width) const;

    virtual QRect calcNewSize(QRect geometry, const QPoint & pos) const = 0;

    void mouseMoveEvent(QMouseEvent * event) override;

    void mousePressEvent(QMouseEvent * event) override;

    void mouseReleaseEvent(QMouseEvent * event) override;

private:
    SizeRubberBand * m_sizeRubberBand = nullptr;

    void sizes(QSize & minSize, QSize & maxSize) const;
};

class NResizer : public Resizer
{
public:
    NResizer(SizeRubberBand * sizeRubberBand)
        : Resizer(Qt::SizeVerCursor, sizeRubberBand)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class SResizer : public Resizer
{
public:
    SResizer(SizeRubberBand * sizeRubberBand)
        : Resizer(Qt::SizeVerCursor, sizeRubberBand)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class WResizer : public Resizer
{
public:
    WResizer(SizeRubberBand * sizeRubberBand)
        : Resizer(Qt::SizeHorCursor, sizeRubberBand)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class EResizer : public Resizer
{
public:
    EResizer(SizeRubberBand * sizeRubberBand)
        : Resizer(Qt::SizeHorCursor, sizeRubberBand)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class NWResizer : public Resizer
{
public:
    NWResizer(SizeRubberBand * sizeRubberBand)
        : Resizer(Qt::SizeFDiagCursor, sizeRubberBand)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class NEResizer : public Resizer
{
public:
    NEResizer(SizeRubberBand * sizeRubberBand)
        : Resizer(Qt::SizeBDiagCursor, sizeRubberBand)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class SWResizer : public Resizer
{
public:
    SWResizer(SizeRubberBand * sizeRubberBand)
        : Resizer(Qt::SizeBDiagCursor, sizeRubberBand)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class SEResizer : public Resizer
{
public:
    SEResizer(SizeRubberBand * sizeRubberBand)
        : Resizer(Qt::SizeFDiagCursor, sizeRubberBand)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

} // namespace ads
