#pragma once

#include <QWidget>

#include "ads_globals.h"

namespace ads {

class WindowData;

class ADS_EXPORT Window : public QWidget
{
    Q_OBJECT
public:
    Window(QWidget * parent = nullptr);

    ~Window();

    QWidget * centralWidget() const;

protected:
    virtual void onStartMoving();

    virtual void onMoving();

    virtual void onEndMoving();

private:
    WindowData * m_data = nullptr;
};

} // namespace ads
