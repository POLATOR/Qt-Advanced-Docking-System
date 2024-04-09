#include "Window/Data/SizeRubberBand.h"

namespace ads
{

SizeRubberBand::SizeRubberBand(QWidget* sizingWindow)
    : QWidget(nullptr, Qt::Window), m_sizingWindow(sizingWindow)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_WState_ExplicitShowHide);
    setWindowFlag(Qt::FramelessWindowHint);

    hide();
    setMinimumSize(m_sizingWindow->minimumSize());
    setMaximumSize(m_sizingWindow->maximumSize());
}

}  // namespace ads
