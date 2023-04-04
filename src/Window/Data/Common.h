#pragma once

#include "ads_globals.h"

#include <QGraphicsDropShadowEffect>
#include <QFlags>
#include <QWidget>

namespace ads {

enum class WindowHeaderButton
{
    None = 0,
    Close = 0x01,
    Maximize = 0x02,
    Minimize = 0x04,
    All = Close | Maximize | Minimize,
};
Q_DECLARE_FLAGS(WindowHeaderButtons, WindowHeaderButton)
Q_DECLARE_OPERATORS_FOR_FLAGS(WindowHeaderButtons)

void SetDefaultButtonShadow(QWidget * button);

void SetSelectedButtonShadow(QWidget * button);

inline QGraphicsDropShadowEffect * ShadowEffect(const QWidget * widget)
{
    return qobject_cast<QGraphicsDropShadowEffect *>(widget->graphicsEffect());
}

} // namespace ads
