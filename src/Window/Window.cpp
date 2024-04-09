#include "Window/Window.h"

#include <QWindow>

#include "Data/WindowBackground.h"
#include "Data/WindowData.h"
#include "Data/WindowHeader.h"

namespace ads
{

Window::Window(QWidget* parent) : QWidget(parent)
{
    setWindowFlags(Qt::Window);
    m_data = new WindowData(this, WindowHeaderButton::All);
    connect(m_data->background()->header(), &WindowHeader::startMoving,
            [this]() { windowHandle()->startSystemMove(); });
}

Window::~Window() = default;

QWidget* Window::centralWidget() const
{
    return m_data->background()->centralWidget();
}

}  // namespace ads
