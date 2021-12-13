#include "Window/Data/WindowHeader.h"

#include <QAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QToolButton>

#include "Window/Data/WindowData.h"

namespace ads {

WindowHeader::WindowHeader(WindowData * windowData, QWidget * parent)
    : QFrame(parent)
    , m_windowData(windowData)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_label = new QLabel(this);
    m_label->setObjectName("HeaderText");

    auto mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_label);

    m_minimize = createButton("MinimizeButton", tr("Minimize"), "icons:Common/Minimize.svg");
    connect(m_minimize, &QToolButton::clicked, m_windowData->sizingWindow(), &QWidget::showMinimized);
    mainLayout->addWidget(m_minimize);

    m_maximize = createButton("MaximizeButton", tr("Maximize"), "icons:Common/Maximize.svg");
    connect(m_maximize, &QToolButton::clicked, this, &WindowHeader::switchMaximized);
    mainLayout->addWidget(m_maximize);

    m_close = createButton("CloseButton", tr("Close"), "icons:Common/Close.svg");
    connect(m_close, &QToolButton::clicked, m_windowData->sizingWindow(), &QWidget::close);
    mainLayout->addWidget(m_close);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

bool WindowHeader::hasButton(WindowHeaderButton button) const
{
    switch (button) {
    case WindowHeaderButton::Close:
        return m_close->isVisible();
    case WindowHeaderButton::Maximize:
        return m_maximize->isVisible();
    case WindowHeaderButton::Minimize:
        return m_minimize->isVisible();
    case WindowHeaderButton::All:
        return (m_close->isVisible() && m_minimize->isVisible() && m_maximize->isVisible());
    case WindowHeaderButton::None:
        return !(m_close->isVisible() && m_minimize->isVisible() && m_maximize->isVisible());
    }
    return false;
}

void WindowHeader::setButton(WindowHeaderButton button, bool visible)
{
    switch (button) {
    case WindowHeaderButton::Close:
        m_close->setVisible(visible);
        break;
    case WindowHeaderButton::Maximize:
        m_maximize->setVisible(visible);
        break;
    case WindowHeaderButton::Minimize:
        m_minimize->setVisible(visible);
        break;
    case WindowHeaderButton::All:
        m_close->setVisible(visible);
        m_minimize->setVisible(visible);
        m_maximize->setVisible(visible);
        break;
    default:
        break;
    }
}

void WindowHeader::setButtons(WindowHeaderButtons buttons)
{
    m_minimize->setVisible(buttons.testFlag(WindowHeaderButton::Minimize));
    m_maximize->setVisible(buttons.testFlag(WindowHeaderButton::Maximize));
    m_close->setVisible(buttons.testFlag(WindowHeaderButton::Close));
}

void WindowHeader::setText(const QString & text)
{
    m_label->setText(text);
}

void WindowHeader::mouseDoubleClickEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        switchMaximized();
    }
}

void WindowHeader::mouseMoveEvent(QMouseEvent * event)
{
    if (m_moveMode) {
        auto point = event->globalPosition().toPoint();
        auto delta = point - m_lastMovePosition;
        if (!delta.isNull()) {
            if (m_windowData->sizingWindow()->isMaximized()) {
                auto oldW = m_windowData->sizingWindow()->width();
                auto screenPos = event->globalPosition().toPoint();
                auto dw = (static_cast<double>(screenPos.x()) - m_windowData->sizingWindow()->pos().x()) / oldW;
                m_windowData->sizingWindow()->showNormal();
                m_windowData->showShadow();
                auto normalSize = m_windowData->sizingWindow()->normalGeometry().size();
                auto newPos = screenPos - QPoint(normalSize.width() * dw, size().height() / 2) /* + delta*/;
                m_windowData->sizingWindow()->move(newPos);
            }
            else {
                m_windowData->sizingWindow()->move(m_windowData->sizingWindow()->pos() + delta);
            }
            Q_EMIT moving();
        }
        m_lastMovePosition = point;
    }
    QFrame::mouseMoveEvent(event);
}

void WindowHeader::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        m_moveMode = true;
        m_lastMovePosition = event->globalPosition().toPoint();
        Q_EMIT startMoving();
    }
    QFrame::mousePressEvent(event);
}

void WindowHeader::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        m_moveMode = false;
        Q_EMIT endMoving();
    }
    QFrame::mouseReleaseEvent(event);
}

QToolButton * WindowHeader::createButton(const QString & name, const QString & tooltip, const QString & iconName)
{
    auto button = new QToolButton(this);
    button->setAutoRaise(true);
    button->setFocusPolicy(Qt::NoFocus);
    button->setIcon(QIcon(iconName));
    button->setObjectName(name);
    button->setToolTip(tooltip);
    return button;
}

void WindowHeader::switchMaximized()
{
    if (m_windowData->sizingWindow()->isMaximized()) {

        m_windowData->sizingWindow()->showNormal();
        m_windowData->showShadow();
        m_maximize->setToolTip(tr("Maximize"));
    }
    else {
        m_windowData->hideShadow();
        m_windowData->sizingWindow()->showMaximized();
        m_maximize->setToolTip(tr("Restore"));
    }
}

} // namespace ads
