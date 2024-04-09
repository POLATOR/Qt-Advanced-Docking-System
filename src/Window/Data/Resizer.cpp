#include "Window/Data/Resizer.h"

#include <QLayout>
#include <QMouseEvent>
#include <QWindow>

#include "Window/Data/SizeRubberBand.h"

namespace ads
{

Resizer::Resizer(Qt::Edges edges, SizeRubberBand* sizeRubberBand)
    : QWidget(sizeRubberBand->sizingWindow()),
      m_sizeRubberBand(sizeRubberBand),
      m_edges(edges)
{
    // clang-format off
    switch (m_edges.toInt())
    {
    case Qt::TopEdge:
    case Qt::BottomEdge:
        setCursor(Qt::SizeVerCursor);
        break;
    case Qt::LeftEdge:
    case Qt::RightEdge:
        setCursor(Qt::SizeHorCursor);
        break;
    case Qt::TopEdge | Qt::LeftEdge:
    case Qt::BottomEdge | Qt::RightEdge:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case Qt::TopEdge | Qt::RightEdge:
    case Qt::BottomEdge | Qt::LeftEdge:
        setCursor(Qt::SizeBDiagCursor);
        break;
    }
    // clang-format on
    setMouseTracking(true);
}

void Resizer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_sizeRubberBand->sizingWindow()->windowHandle()->startSystemResize(
            m_edges);
    }
    QWidget::mousePressEvent(event);
}

void NResizer::updateGeometry(const QRect& geometry, int gripSize)
{
    QRect g{geometry.topLeft() + QPoint(gripSize, 0),
            QSize{geometry.width() - gripSize * 2, gripSize}};
    setGeometry(g);
}

void SResizer::updateGeometry(const QRect& geometry, int gripSize)
{
    QRect g{geometry.bottomLeft() + QPoint(gripSize, -gripSize),
            QSize{geometry.width() - gripSize * 2, gripSize}};
    setGeometry(g);
}

void WResizer::updateGeometry(const QRect& geometry, int gripSize)
{
    QRect g{geometry.topLeft() + QPoint(0, gripSize),
            QSize{gripSize, geometry.height() - gripSize * 2}};
    setGeometry(g);
}

void EResizer::updateGeometry(const QRect& geometry, int gripSize)
{
    QRect g{geometry.topRight() + QPoint(-gripSize, gripSize),
            QSize{gripSize, geometry.height() - gripSize * 2}};
    setGeometry(g);
}

void NWResizer::updateGeometry(const QRect& geometry, int gripSize)
{
    QRect g{geometry.topLeft(), QSize{gripSize, gripSize}};
    setGeometry(g);
}

void NEResizer::updateGeometry(const QRect& geometry, int gripSize)
{
    QRect g{geometry.topRight() + QPoint(-gripSize, 0),
            QSize{gripSize, gripSize}};
    setGeometry(g);
}

void SWResizer::updateGeometry(const QRect& geometry, int gripSize)
{
    QRect g{geometry.bottomLeft() + QPoint(0, -gripSize),
            QSize{gripSize, gripSize}};
    setGeometry(g);
}

void SEResizer::updateGeometry(const QRect& geometry, int gripSize)
{
    QRect g{geometry.bottomRight() + QPoint(-gripSize, -gripSize),
            QSize{gripSize, gripSize}};
    setGeometry(g);
}

}  // namespace ads
