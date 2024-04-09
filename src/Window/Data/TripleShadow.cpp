#include "Window/Data/TripleShadow.h"

#include <QGraphicsDropShadowEffect>
#include <QResizeEvent>

#include "Window/Data/TripleShadowPart.h"

namespace ads
{

namespace
{

constexpr int c_shadowMargin = 96;
constexpr QSize c_shadowMarginSize{c_shadowMargin * 2, c_shadowMargin * 2};
constexpr QPoint c_shadowMarginOffset{c_shadowMargin, c_shadowMargin};

TripleShadowPart* CreateTripleShadowPart(TripleShadow* parent,
                                         TripleShadowPart::Placement placement,
                                         const QColor& shadowColor)
{
    auto* shadowPart = new TripleShadowPart(placement, shadowColor, parent);
    shadowPart->move(c_shadowMarginOffset);
    shadowPart->setVisible(false);
    return shadowPart;
}

void SetEffectColor(const QWidget* widget, const QColor& shadowColor)
{
    auto* effect =
        qobject_cast<QGraphicsDropShadowEffect*>(widget->graphicsEffect());
    if (effect)
    {
        effect->setColor(shadowColor);
    }
}

}  // namespace

QPoint TripleShadow::mapToShadow(const QPoint& pos)
{
    return pos - c_shadowMarginOffset;
}

QSize TripleShadow::mapToShadow(const QSize& size)
{
    return size + c_shadowMarginSize;
}

TripleShadow::TripleShadow(QWidget* parent) : QWidget(parent, Qt::Window)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::X11BypassWindowManagerHint);
    setWindowFlag(Qt::WindowTransparentForInput);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    m_leftPart = CreateTripleShadowPart(this, TripleShadowPart::Placement::Left,
                                        m_shadowColor);
    m_rightPart = CreateTripleShadowPart(this, TripleShadowPart::Placement::Right,
                                         m_shadowColor);
    m_bottomPart = CreateTripleShadowPart(
        this, TripleShadowPart::Placement::Bottom, m_shadowColor);

    hide();
}

void TripleShadow::setShadowColor(const QColor& shadowColor)
{
    SetEffectColor(m_leftPart, shadowColor);
    SetEffectColor(m_rightPart, shadowColor);
    SetEffectColor(m_bottomPart, shadowColor);
    m_shadowColor = shadowColor;
}

void TripleShadow::setShadowStyle(ShadowStyle shadowStyle)
{
    if (shadowStyle == m_shadowStyle)
    {
        return;
    }
    switch (shadowStyle)
    {
    case ShadowStyle::None:
        m_leftPart->hide();
        m_rightPart->hide();
        m_bottomPart->hide();
        break;
    case ShadowStyle::Single:
        m_leftPart->hide();
        m_rightPart->hide();
        m_bottomPart->show();
        break;
    case ShadowStyle::Triple:
        m_leftPart->show();
        m_rightPart->show();
        m_bottomPart->show();
        break;
    }
    m_shadowStyle = shadowStyle;
}

void TripleShadow::resizeEvent(QResizeEvent* event)
{
    resizeParts(event->size());
}

void TripleShadow::resizeParts(const QSize& newSize)
{
    const auto partSize = newSize - c_shadowMarginSize;
    if (m_leftPart->size() != partSize)
    {
        m_leftPart->resize(partSize);
        m_rightPart->resize(partSize);
        m_bottomPart->resize(partSize);
    }
}

}  // namespace ads
