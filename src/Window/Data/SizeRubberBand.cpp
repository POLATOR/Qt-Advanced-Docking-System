#include "Window/Data/SizeRubberBand.h"

#include <QDebug>
#include <QLayout>
#include <QPainter>

namespace ads {

SizeRubberBand::SizeRubberBand(QWidget * sizingWindow)
    : QWidget(nullptr, Qt::Window)
    , m_sizingWindow(sizingWindow)
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
        m_sizingWindow->setGeometry(geometry());
    }
    m_resizeStarted = false;
}

void SizeRubberBand::updateGeometry(const QRect & newGeometry)
{
    QWidget * widgetToResize = isRubberResize() ? this : m_sizingWindow;

    auto & oldGeometry = widgetToResize->geometry();
    auto deltaPos = newGeometry.topLeft() - oldGeometry.topLeft();
    auto deltaSize = newGeometry.size() - oldGeometry.size();
    auto positivePos = (deltaPos.x() > 0 || deltaPos.y() > 0);
    auto negativeSize = (deltaSize.width() < 0 || deltaSize.height() < 0);
    auto sizeBefore = (positivePos || negativeSize);

    if (sizeBefore && !deltaSize.isNull()) {
        widgetToResize->resize(newGeometry.size());
    }
    if (!deltaPos.isNull()) {
        widgetToResize->move(newGeometry.topLeft());
    }
    if (!sizeBefore && !deltaSize.isNull()) {
        widgetToResize->resize(newGeometry.size());
    }
}

void SizeRubberBand::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QColor Color = palette().color(QPalette::Active, QPalette::Highlight);

    QPen Pen = painter.pen();
    Pen.setColor(Color.darker(120));
    Pen.setStyle(Qt::SolidLine);
    Pen.setWidth(4);
    Pen.setCosmetic(true);
    painter.setPen(Pen);

    Color = Color.lighter(130);
    Color.setAlphaF(0.10);
    painter.setBrush(Color);

    painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 8.0, 8.0);
}

} // namespace ads
