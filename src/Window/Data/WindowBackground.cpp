#include "Window/Data/WindowBackground.h"

#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>

#include "Window/Data/WindowCentralWidget.h"
#include "Window/Data/WindowData.h"
#include "Window/Data/WindowHeader.h"

namespace ads
{

WindowBackground::WindowBackground(WindowData* windowData,
                                   WindowHeaderButtons buttons)
    : QFrame(windowData)
{
    m_header = new WindowHeader(windowData, this);
    m_header->setButtons(buttons);
    m_centralWidget = new WindowCentralWidget(this);

    auto* centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_centralWidget);
    centralLayout->setContentsMargins(0, 0, 0, 0);

    connect(m_centralWidget, &QWidget::windowTitleChanged, m_header,
            &WindowHeader::setText);
    connect(windowData->sizingWindow(), &QWidget::windowTitleChanged, m_header,
            &WindowHeader::setText);

    auto* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_header);
    mainLayout->addLayout(centralLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

}  // namespace ads
