#include "Window/Window.h"

#include "Data/WindowBackground.h"
#include "Data/WindowData.h"
#include "Data/WindowHeader.h"

namespace ads {

Window::Window(QWidget * parent)
    : QWidget(parent, Qt::Window)
{
    m_data = new WindowData(this, WindowHeaderButton::All);
    connect(m_data->background()->header(), &WindowHeader::startMoving, this, &Window::onStartMoving);
    connect(m_data->background()->header(), &WindowHeader::moving, this, &Window::onMoving);
    connect(m_data->background()->header(), &WindowHeader::endMoving, this, &Window::onEndMoving);
}

Window::~Window()
{
}

QWidget * Window::centralWidget() const
{
    return m_data->background()->centralWidget();
}

void Window::onStartMoving()
{
    // do nothing by default
}

void Window::onMoving()
{
    // do nothing by default
}

void Window::onEndMoving()
{
    // do nothing by default
}

} // namespace ads
