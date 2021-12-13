#include "Window/Data/Common.h"

#include <QWidget>

namespace ads {

namespace {

const qreal DEFAULT_SHADOW_OFFSET_X = 0.0;
const qreal DEFAULT_SHADOW_OFFSET_Y = 0.5;
const qreal DEFAULT_SHADOW_RADIUS = 1.0;

const qreal SELECTED_SHADOW_OFFSET_X = 0.0;
const qreal SELECTED_SHADOW_OFFSET_Y = 1.0;
const qreal SELECTED_SHADOW_RADIUS = 2.0;

void SetShadowEffect(QWidget * widget, qreal offsetX, qreal offsetY, qreal radius)
{
    auto effect = ShadowEffect(widget);
    if (effect) {
        effect->setOffset(offsetX, offsetY);
        effect->setBlurRadius(radius);
    }
}

} // namespace

void SetDefaultButtonShadow(QWidget * button)
{
    SetShadowEffect(button, DEFAULT_SHADOW_OFFSET_X, DEFAULT_SHADOW_OFFSET_Y, DEFAULT_SHADOW_RADIUS);
}

void SetSelectedButtonShadow(QWidget * button)
{
    SetShadowEffect(button, SELECTED_SHADOW_OFFSET_X, SELECTED_SHADOW_OFFSET_Y, SELECTED_SHADOW_RADIUS);
}

} // namespace ads
