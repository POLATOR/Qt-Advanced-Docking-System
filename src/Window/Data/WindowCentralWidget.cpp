#include "Window/Data/WindowCentralWidget.h"

namespace ads {

WindowCentralWidget::WindowCentralWidget(QWidget * parent)
    : QFrame(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

} // namespace ads
