#include "Window/Data/TripleShadowPart.h"

#include <QGraphicsDropShadowEffect>
#include <QStyleOptionFrame>

namespace ads {

namespace {

const double SHADOW_BLUR_RADIUS = 80.0;

} // namespace

TripleShadowPart::TripleShadowPart(Placement placement, const QColor & shadowColor, QWidget * parent)
    : QFrame(parent)
    , m_placement(placement)
{
    auto effect = new QGraphicsDropShadowEffect(this);
    switch (placement) {
    case Placement::Left:
        effect->setOffset({-35.0, 45.0});
        break;
    case Placement::Right:
        effect->setOffset({35.0, 45.0});
        break;
    case Placement::Bottom:
        effect->setOffset({0.0, 10.0});
        break;
    }
    effect->setBlurRadius(SHADOW_BLUR_RADIUS);
    if (shadowColor.isValid()) {
        effect->setColor(shadowColor);
    }
    setGraphicsEffect(effect);
}

} // namespace ads
