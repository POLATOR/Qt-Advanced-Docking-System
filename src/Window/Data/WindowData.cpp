#include "Window/Data/WindowData.h"

#include <functional>

#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include <QMoveEvent>
#include <QScreen>
#include <QVBoxLayout>

#include "Window/Data/Resizer.h"
#include "Window/Data/SizeRubberBand.h"
#include "Window/Data/TripleShadow.h"
#include "Window/Data/WindowBackground.h"
#include "Window/Data/WindowHeader.h"

namespace ads {

namespace {

QPoint MapToData(const QPoint & pos)
{
    return pos - TripleShadow::SHADOW_MARGIN_OFFSET;
}

QSize MapToData(const QSize & size)
{
    return size + TripleShadow::SHADOW_MARGIN_SIZE;
}

} // namespace

const int WindowData::DEFAULT_GRIP_SIZE = 8;

WindowData::WindowData(QWidget * sizingWindow, WindowHeaderButtons buttons)
    : QWidget(sizingWindow)
    , m_sizingWindow(sizingWindow)
{
    // this widget is a widget only because we need to set it properties from qss
    // we set its size to zero to hide it because widget must be visible to get properties values from qss
    setFixedSize(0, 0);

    sizingWindow->setWindowFlag(Qt::FramelessWindowHint);
    sizingWindow->setWindowFlag(Qt::X11BypassWindowManagerHint);
    sizingWindow->setAttribute(Qt::WA_TranslucentBackground);

    m_background = new WindowBackground(this, buttons);

    m_sizeRubberBand = new SizeRubberBand(m_sizingWindow);

    m_resizers.push_back(new NWResizer(m_sizeRubberBand));
    m_resizers.push_back(new NEResizer(m_sizeRubberBand));
    m_resizers.push_back(new SWResizer(m_sizeRubberBand));
    m_resizers.push_back(new SEResizer(m_sizeRubberBand));
    m_resizers.push_back(new NResizer(m_sizeRubberBand));
    m_resizers.push_back(new SResizer(m_sizeRubberBand));
    m_resizers.push_back(new WResizer(m_sizeRubberBand));
    m_resizers.push_back(new EResizer(m_sizeRubberBand));

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_background);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    m_sizingWindow->setLayout(mainLayout);

    m_shadow = new TripleShadow(m_sizingWindow->parentWidget());
    m_shadow->setGeometry({MapToData(m_sizingWindow->pos()), MapToData(m_sizingWindow->size())});
    m_shadow->stackUnder(m_sizingWindow);

    m_sizingWindow->installEventFilter(this);
    m_sizingWindow->raise();
}

WindowData::~WindowData()
{
    delete m_shadow;
    delete m_sizeRubberBand;
}

bool WindowData::rubberOnResize() const
{
    return m_sizeRubberBand->isRubberResize();
}

void WindowData::setRubberOnResize(bool rubberOnResize)
{
    m_sizeRubberBand->setRubberResize(rubberOnResize);
}

void WindowData::setGripSize(int gripSize)
{
    if (gripSize < DEFAULT_GRIP_SIZE) {
        qDebug() << "Grip size too small" << gripSize;
        return;
    }
    if (gripSize != m_gripSize) {
        m_gripSize = gripSize;
        updateResizers();
    }
}

bool WindowData::isResizeEnabled() const
{
    return (!m_resizers.isEmpty() && m_resizers.front()->isVisible());
}

void WindowData::setResizeEnabled(bool enabled)
{
    for (auto resizer: m_resizers) {
        resizer->setVisible(enabled);
    }
}

QColor WindowData::shadowColor() const
{
    return m_shadow->shadowColor();
}

void WindowData::setShadowColor(const QColor & shadowColor)
{
    m_shadow->setShadowColor(shadowColor);
}

ShadowStyle WindowData::shadowStyle() const
{
    return m_shadow->shadowStyle();
}

void WindowData::setShadowStyle(ShadowStyle shadowStyle)
{
    m_shadow->setShadowStyle(shadowStyle);
    if (m_shadow->shadowStyle() != ShadowStyle::None) {
        m_shadow->setVisible(m_sizingWindow->isVisible());
        m_sizingWindow->raise();
    }
    else {
        m_shadow->hide();
    }
}

bool WindowData::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == m_sizingWindow) {
        switch (event->type()) {
        case QEvent::Resize:
            m_shadow->resize(MapToData(m_sizingWindow->size()));
            updateResizers();
            break;
        case QEvent::Move:
            m_shadow->move(MapToData(static_cast<QMoveEvent *>(event)->pos()));
            break;
        case QEvent::Show:
            if (m_shadow->shadowStyle() != ShadowStyle::None) {
                m_shadow->show();
            }
            break;
        case QEvent::Hide:
            m_shadow->hide();
            break;
        case QEvent::ParentChange:
            m_shadow->setParent(m_sizingWindow->parentWidget());
            m_sizingWindow->raise();
            break;
        case QEvent::WindowStateChange:
            updateResizers();
            break;
        }
    }
    return QObject::eventFilter(watched, event);
}

void WindowData::hideShadow()
{
    if (m_shadow->shadowStyle() != ShadowStyle::None) {
        m_shadow->hide();
    }
}

void WindowData::showShadow()
{
    if (m_shadow->shadowStyle() != ShadowStyle::None) {
        m_shadow->show();
        m_sizingWindow->raise();
    }
}

void WindowData::updateResizers()
{
    bool visible = !m_sizingWindow->isMinimized();
    auto & g = m_background->geometry();
    for (auto resizer: m_resizers) {
        resizer->setVisible(visible);
        if (visible) {
            resizer->updateGeometry(g, m_gripSize);
            resizer->raise();
        }
    }
}

} // namespace ads
