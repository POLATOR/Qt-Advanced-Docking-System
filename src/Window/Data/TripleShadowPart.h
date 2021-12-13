#pragma once

#include <QFrame>

class QGraphicsDropShadowEffect;

namespace ads {

class TripleShadowPart : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(Placement placement READ placement)
public:
    enum class Placement
    {
        Left = 1,
        Right,
        Bottom,
    };
    Q_ENUM(Placement)

    TripleShadowPart(Placement state, const QColor & shadowColor, QWidget * parent);

    Placement placement() const noexcept
    {
        return m_placement;
    }

private:
    Placement m_placement = Placement::Left;
};

} // namespace ads
