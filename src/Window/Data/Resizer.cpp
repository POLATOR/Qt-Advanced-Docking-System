#include "Window/Data/Resizer.h"

#include <QLayout>
#include <QMouseEvent>

#include "Window/Data/SizeRubberBand.h"

namespace ads {

namespace {

int AdjustValue(int value, int minValue, int maxValue)
{
    value = qMax(value, minValue);
    value = qMin(value, maxValue);
    value = qMax(value, 0);
    value = qMin(value, QWIDGETSIZE_MAX);
    // +1 because after applying the min width or height, the widget somehow adds 1 to the width or height
    return ++value;
}

} // namespace

Resizer::Resizer(Qt::CursorShape cursorShape, SizeRubberBand * sizeRubberBand)
    : QWidget(sizeRubberBand->sizingWindow())
    , m_sizeRubberBand(sizeRubberBand)
{
    setCursor(cursorShape);
    setMouseTracking(true);
}

int Resizer::adjustHeight(int height) const
{
    QSize minSize, maxSize;
    sizes(minSize, maxSize);
    return AdjustValue(height, minSize.height(), maxSize.height());
}

int Resizer::adjustWidth(int width) const
{
    QSize minSize, maxSize;
    sizes(minSize, maxSize);
    return AdjustValue(width, minSize.width(), maxSize.width());
}

void Resizer::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton && m_sizeRubberBand->isResized()) {
        auto pos = event->globalPosition().toPoint();
        auto oldGeometry = m_sizeRubberBand->oldGeometry();
        auto newGeometry = calcNewSize(oldGeometry, pos);
        m_sizeRubberBand->updateGeometry(newGeometry);
    }
    QWidget::mouseMoveEvent(event);
}

void Resizer::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        m_sizeRubberBand->start();
    }
    QWidget::mousePressEvent(event);
}

void Resizer::mouseReleaseEvent(QMouseEvent * event)
{
    if (m_sizeRubberBand->isResized()) {
        m_sizeRubberBand->stop();
    }
    QWidget::mouseReleaseEvent(event);
}

void Resizer::sizes(QSize & minSize, QSize & maxSize) const
{
    minSize = m_sizeRubberBand->layoutMinimumSize();
    maxSize = m_sizeRubberBand->layoutMaximumSize();
}

void NResizer::updateGeometry(const QRect & geometry, int gripSize)
{
    QRect g{geometry.topLeft() + QPoint(gripSize, 0), QSize{geometry.width() - gripSize * 2, gripSize}};
    setGeometry(g);
}

QRect NResizer::calcNewSize(QRect geometry, const QPoint & pos) const
{
    auto bottom = geometry.bottom();
    auto newHeight = adjustHeight(bottom - pos.y() + 1);
    geometry.setY(bottom - newHeight);
    return geometry;
}

void SResizer::updateGeometry(const QRect & geometry, int gripSize)
{
    QRect g{geometry.bottomLeft() + QPoint(gripSize, -gripSize), QSize{geometry.width() - gripSize * 2, gripSize}};
    setGeometry(g);
}

QRect SResizer::calcNewSize(QRect geometry, const QPoint & pos) const
{
    auto top = geometry.top();
    auto newHeight = adjustHeight(pos.y() - top);
    geometry.setHeight(newHeight);
    return geometry;
}

void WResizer::updateGeometry(const QRect & geometry, int gripSize)
{
    QRect g{geometry.topLeft() + QPoint(0, gripSize), QSize{gripSize, geometry.height() - gripSize * 2}};
    setGeometry(g);
}

QRect WResizer::calcNewSize(QRect geometry, const QPoint & pos) const
{
    auto right = geometry.right();
    auto newWidth = adjustWidth(right - pos.x());
    geometry.setX(right - newWidth);
    return geometry;
}

void EResizer::updateGeometry(const QRect & geometry, int gripSize)
{
    QRect g{geometry.topRight() + QPoint(-gripSize, gripSize), QSize{gripSize, geometry.height() - gripSize * 2}};
    setGeometry(g);
}

QRect EResizer::calcNewSize(QRect geometry, const QPoint & pos) const
{
    auto left = geometry.left();
    auto newWidth = adjustWidth(pos.x() - left);
    geometry.setWidth(newWidth);
    return geometry;
}

void NWResizer::updateGeometry(const QRect & geometry, int gripSize)
{
    QRect g{geometry.topLeft(), QSize{gripSize, gripSize}};
    setGeometry(g);
}

QRect NWResizer::calcNewSize(QRect geometry, const QPoint & pos) const
{
    auto bottomRight = geometry.bottomRight();
    auto newWidth = adjustWidth(bottomRight.x() - pos.x());
    auto newHeight = adjustHeight(bottomRight.y() - pos.y());
    geometry.setX(bottomRight.x() - newWidth);
    geometry.setY(bottomRight.y() - newHeight);
    return geometry;
}

void NEResizer::updateGeometry(const QRect & geometry, int gripSize)
{
    QRect g{geometry.topRight() + QPoint(-gripSize, 0), QSize{gripSize, gripSize}};
    setGeometry(g);
}

QRect NEResizer::calcNewSize(QRect geometry, const QPoint & pos) const
{
    auto bottomLeft = geometry.bottomLeft();
    auto newWidth = adjustWidth(pos.x() - bottomLeft.x());
    auto newHeight = adjustHeight(bottomLeft.y() - pos.y());
    geometry.setWidth(newWidth);
    geometry.setY(bottomLeft.y() - newHeight);
    return geometry;
}

void SWResizer::updateGeometry(const QRect & geometry, int gripSize)
{
    QRect g{geometry.bottomLeft() + QPoint(0, -gripSize), QSize{gripSize, gripSize}};
    setGeometry(g);
}

QRect SWResizer::calcNewSize(QRect geometry, const QPoint & pos) const
{
    auto topRight = geometry.topRight();
    auto newWidth = adjustWidth(topRight.x() - pos.x());
    auto newHeight = adjustHeight(pos.y() - topRight.y());
    geometry.setX(topRight.x() - newWidth);
    geometry.setHeight(newHeight);
    return geometry;
}

void SEResizer::updateGeometry(const QRect & geometry, int gripSize)
{
    QRect g{geometry.bottomRight() + QPoint(-gripSize, -gripSize), QSize{gripSize, gripSize}};
    setGeometry(g);
}

QRect SEResizer::calcNewSize(QRect geometry, const QPoint & pos) const
{
    auto topLeft = geometry.topLeft();
    auto newWidth = adjustWidth(pos.x() - topLeft.x());
    auto newHeight = adjustHeight(pos.y() - topLeft.y());
    geometry.setWidth(newWidth);
    geometry.setHeight(newHeight);
    return geometry;
}

} // namespace ads
