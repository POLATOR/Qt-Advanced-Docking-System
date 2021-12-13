#pragma once

#include <QWidget>

namespace ads {

class Resizer : public QWidget
{
    Q_OBJECT
public:
    Resizer(Qt::CursorShape cursorShape, QWidget * sizingWindow);

    virtual void updateGeometry(const QRect & geometry, int gripSize) = 0;

Q_SIGNALS:
    void beforeNewGeometry(const QPoint & deltaPos, const QSize & deltaSize);

    void beginResize();

    void endResize();

protected:
    int adjustHeight(int height) const;

    int adjustWidth(int width) const;

    virtual QRect calcNewSize(QRect geometry, const QPoint & pos) const = 0;

    void mouseMoveEvent(QMouseEvent * event) override;

    void mousePressEvent(QMouseEvent * event) override;

    void mouseReleaseEvent(QMouseEvent * event) override;

private:
    bool m_resizeMode = false;
    QWidget * m_sizingWindow = nullptr;

    void sizes(QSize & minSize, QSize & maxSize) const;
};

class NResizer : public Resizer
{
public:
    NResizer(QWidget * sizingWindow)
        : Resizer(Qt::SizeVerCursor, sizingWindow)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class SResizer : public Resizer
{
public:
    SResizer(QWidget * sizingWindow)
        : Resizer(Qt::SizeVerCursor, sizingWindow)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class WResizer : public Resizer
{
public:
    WResizer(QWidget * sizingWindow)
        : Resizer(Qt::SizeHorCursor, sizingWindow)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class EResizer : public Resizer
{
public:
    EResizer(QWidget * sizingWindow)
        : Resizer(Qt::SizeHorCursor, sizingWindow)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class NWResizer : public Resizer
{
public:
    NWResizer(QWidget * sizingWindow)
        : Resizer(Qt::SizeFDiagCursor, sizingWindow)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class NEResizer : public Resizer
{
public:
    NEResizer(QWidget * sizingWindow)
        : Resizer(Qt::SizeBDiagCursor, sizingWindow)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class SWResizer : public Resizer
{
public:
    SWResizer(QWidget * sizingWindow)
        : Resizer(Qt::SizeBDiagCursor, sizingWindow)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

class SEResizer : public Resizer
{
public:
    SEResizer(QWidget * sizingWindow)
        : Resizer(Qt::SizeFDiagCursor, sizingWindow)
    {
    }

    void updateGeometry(const QRect & geometry, int gripSize) override;

protected:
    QRect calcNewSize(QRect geometry, const QPoint & pos) const override;
};

} // namespace ads
