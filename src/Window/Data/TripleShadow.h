#pragma once

#include "Window/Data/Common.h"

namespace ads
{

class TripleShadowPart;

class TripleShadow : public QWidget
{
    Q_OBJECT
public:
    static QPoint mapToShadow(const QPoint& pos);
    static QSize mapToShadow(const QSize& size);

    TripleShadow(QWidget* parent);

    QColor shadowColor() const noexcept { return m_shadowColor; }
    void setShadowColor(const QColor& shadowColor);

    ShadowStyle shadowStyle() const { return m_shadowStyle; }
    void setShadowStyle(ShadowStyle shadowStyle);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QColor m_shadowColor;
    ShadowStyle m_shadowStyle = ShadowStyle::None;
    TripleShadowPart* m_leftPart = nullptr;
    TripleShadowPart* m_rightPart = nullptr;
    TripleShadowPart* m_bottomPart = nullptr;

    void resizeParts(const QSize& newSize);
};

}  // namespace ads
