#include "Window/Data/WindowData.h"

#include <QEvent>
#include <QMoveEvent>
#include <QVBoxLayout>
#include <QWindow>

#include "Window/Data/Resizer.h"
#include "Window/Data/SizeRubberBand.h"
#include "Window/Data/TripleShadow.h"
#include "Window/Data/WindowBackground.h"

namespace ads
{

WindowData::WindowData(QWidget* sizingWindow, WindowHeaderButtons buttons)
    : QWidget(sizingWindow), m_sizingWindow(sizingWindow)
{
    // this widget is a widget only because we need to set it properties from qss
    // we set its size to zero to hide it because widget must be visible to get
    // properties values from qss
    setFixedSize(0, 0);

    sizingWindow->setWindowFlag(Qt::FramelessWindowHint);
    sizingWindow->setWindowFlag(Qt::X11BypassWindowManagerHint);
    // sizingWindow->setAttribute(Qt::WA_TranslucentBackground);

    m_background = new WindowBackground(this, buttons);

    m_shadow = new TripleShadow(m_sizingWindow->parentWidget());
    m_shadow->setGeometry({TripleShadow::mapToShadow(m_sizingWindow->pos()),
                           TripleShadow::mapToShadow(m_sizingWindow->size())});
    m_shadow->stackUnder(m_sizingWindow);

    m_sizeRubberBand = new SizeRubberBand(m_sizingWindow);

    m_resizerList.push_back(new NWResizer(m_sizeRubberBand));
    m_resizerList.push_back(new NEResizer(m_sizeRubberBand));
    m_resizerList.push_back(new SWResizer(m_sizeRubberBand));
    m_resizerList.push_back(new SEResizer(m_sizeRubberBand));
    m_resizerList.push_back(new NResizer(m_sizeRubberBand));
    m_resizerList.push_back(new SResizer(m_sizeRubberBand));
    m_resizerList.push_back(new WResizer(m_sizeRubberBand));
    m_resizerList.push_back(new EResizer(m_sizeRubberBand));

    auto* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_background);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    m_sizingWindow->setLayout(mainLayout);

    m_sizingWindow->installEventFilter(this);
    m_sizingWindow->raise();
}

WindowData::~WindowData()
{
    delete m_shadow;
    delete m_sizeRubberBand;
}

void WindowData::setGripSize(int gripSize)
{
    if (gripSize < c_defaultGripSize)
    {
        qDebug() << "Grip size too small" << gripSize;
        return;
    }
    if (gripSize != m_gripSize)
    {
        m_gripSize = gripSize;
        updateResizers();
    }
}

bool WindowData::isResizeEnabled() const
{
    return (!m_resizerList.isEmpty() && m_resizerList.front()->isVisible());
}

void WindowData::setResizeEnabled(bool enabled)
{
    for (auto resizer : m_resizerList)
    {
        resizer->setVisible(enabled);
    }
}

QColor WindowData::shadowColor() const
{
    return m_shadow->shadowColor();
}

void WindowData::setShadowColor(const QColor& shadowColor)
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
    if (m_shadow->shadowStyle() != ShadowStyle::None)
    {
        m_shadow->setVisible(m_sizingWindow->isVisible());
        m_sizingWindow->raise();
    }
    else
    {
        m_shadow->hide();
    }
}

bool WindowData::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_sizingWindow)
    {
        switch (event->type())
        {
        case QEvent::Resize:
            m_shadow->resize(TripleShadow::mapToShadow(m_sizingWindow->size()));
            updateResizers();
            break;
        case QEvent::Move:
            m_shadow->move(TripleShadow::mapToShadow(
                static_cast<QMoveEvent*>(event)->pos()));
            break;
        case QEvent::Show:
            if (m_shadow->shadowStyle() != ShadowStyle::None)
            {
                m_shadow->show();
                m_shadow->stackUnder(m_sizingWindow);
            }
            break;
        case QEvent::Hide: m_shadow->hide(); break;
        case QEvent::ParentChange:
            m_shadow->setParent(m_sizingWindow->parentWidget());
            m_sizingWindow->raise();
            break;
        case QEvent::WindowStateChange: updateResizers(); break;
        }
    }
    return QObject::eventFilter(watched, event);
}

void WindowData::hideShadow()
{
    if (m_shadow->shadowStyle() != ShadowStyle::None)
    {
        m_shadow->hide();
    }
}

void WindowData::showShadow()
{
    if (m_shadow->shadowStyle() != ShadowStyle::None)
    {
        m_shadow->show();
        m_sizingWindow->raise();
    }
}

void WindowData::updateResizers()
{
    const bool visible = !m_sizingWindow->isMinimized();
    auto& g = m_background->geometry();
    for (auto* resizer : m_resizerList)
    {
        resizer->setVisible(visible);
        if (visible)
        {
            resizer->updateGeometry(g, m_gripSize);
            resizer->raise();
        }
    }
}

}  // namespace ads
