#include "Window/Data/SizeRubberBand.h"

#include <QCoreApplication>
#include <QDebug>
#include <QLayout>
#include <QPainter>
#include <QTimer>

#include "Window/Data/TripleShadow.h"

namespace ads {

const int NO_MORE_MS = 50;

SizeRubberBand::SizeRubberBand(QWidget * sizingWindow, QWidget * shadow)
    : QWidget(nullptr, Qt::Window)
    , m_sizingWindow(sizingWindow)
    , m_shadow(shadow)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_WState_ExplicitShowHide);
    setWindowFlag(Qt::FramelessWindowHint);

    hide();
    setMinimumSize(m_sizingWindow->minimumSize());
    setMaximumSize(m_sizingWindow->maximumSize());
}

QSize SizeRubberBand::layoutMinimumSize() const
{
    const QWidget * widgetToResize = isRubberResize() ? this : m_sizingWindow;
    auto size = widgetToResize->minimumSize();
    if (size.isNull()) {
        auto layout = widgetToResize->layout();
        if (layout) {
            size = layout->minimumSize();
        }
    }
    return size;
}

QSize SizeRubberBand::layoutMaximumSize() const
{
    const QWidget * widgetToResize = isRubberResize() ? this : m_sizingWindow;
    auto size = widgetToResize->maximumSize();
    if (size == QSize{QWIDGETSIZE_MAX, QWIDGETSIZE_MAX}) {
        auto layout = widgetToResize->layout();
        if (layout) {
            size = layout->maximumSize();
        }
    }
    return size;
}

const QRect & SizeRubberBand::oldGeometry() const
{
    if (isRubberResize()) {
        return geometry();
    }
    return m_sizingWindow->geometry();
}

void SizeRubberBand::start()
{
    m_resizeStarted = true;
    if (isRubberResize()) {
        setGeometry(m_sizingWindow->geometry());
        show();
    }
}

void SizeRubberBand::stop()
{
    if (isRubberResize()) {
        hide();
        resizeWidget(m_sizingWindow, geometry());
    }
    m_resizeStarted = false;
}

void SizeRubberBand::updateGeometry(const QRect & newGeometry)
{
    if (isRubberResize()) {
        setGeometry(newGeometry);
    }
    else {
        resizeWidget(m_sizingWindow, newGeometry);
    }
}

void SizeRubberBand::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    auto pen = painter.pen();
    pen.setColor(m_borderColor);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(m_borderWidth);
    pen.setCosmetic(true);
    painter.setPen(pen);
    painter.setBrush(m_backgroundColor);
    painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), m_borderRadius, m_borderRadius);
}

void SizeRubberBand::resizeWidget(QWidget * widget, const QRect & newGeometry)
{
    auto & oldGeometry = widget->geometry();
    auto oldPos = oldGeometry.topLeft();
    auto oldSize = oldGeometry.size();
    auto deltaPos = newGeometry.topLeft() - oldGeometry.topLeft();
    auto deltaSize = newGeometry.size() - oldGeometry.size();

    auto beforeSize = newGeometry.size();
    if (deltaSize.width() > 0) {
        beforeSize.setWidth(oldSize.width());
    }
    if (deltaSize.height() > 0) {
        beforeSize.setHeight(oldSize.height());
    }
    auto middlePos = newGeometry.topLeft();
    if (deltaPos.x() < 0) {
        middlePos.setX(oldPos.x());
    }
    if (deltaPos.y() < 0) {
        middlePos.setY(oldPos.y());
    }
    if (beforeSize != oldSize) {
        m_shadow->resize(TripleShadow::mapToShadow(beforeSize));
        QCoreApplication::processEvents(QEventLoop::ExcludeSocketNotifiers | QEventLoop::ExcludeUserInputEvents, NO_MORE_MS);
    }
    if (middlePos != oldPos) {
        m_shadow->move(TripleShadow::mapToShadow(middlePos));
    }
    widget->setGeometry(newGeometry);
}

} // namespace ads
