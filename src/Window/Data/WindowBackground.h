#pragma once

#include <QFrame>

#include "Window/Data/Common.h"

namespace ads
{

class WindowData;
class WindowHeader;

class WindowBackground : public QFrame
{
    Q_OBJECT
public:
    WindowBackground(WindowData* windowData, WindowHeaderButtons buttons);

    QWidget* centralWidget() const { return m_centralWidget; }

    WindowHeader* header() const { return m_header; }

private:
    WindowHeader* m_header = nullptr;
    QWidget* m_centralWidget = nullptr;
};

}  // namespace ads
