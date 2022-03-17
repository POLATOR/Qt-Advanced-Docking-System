#pragma once

#include <QFlags>
#include <QFrame>

class QLabel;
class QToolButton;

#include "Window/Data/Common.h"

namespace ads {

class WindowData;

class WindowHeader : public QFrame
{
    Q_OBJECT
public:
    WindowHeader(WindowData * windowData, QWidget * parent);

    WindowHeaderButtons buttons() const
    {
        return m_buttons;
    }

    bool hasButton(WindowHeaderButton button) const;
    void setButton(WindowHeaderButton button, bool visible);

    void setButtons(WindowHeaderButtons buttons);

    void setText(const QString & text);

Q_SIGNALS:
    void startMoving();
    void moving();
    void endMoving();

protected:
    void changeEvent(QEvent * event) override;

    void mouseDoubleClickEvent(QMouseEvent * event) override;

    void mouseMoveEvent(QMouseEvent * event) override;

    void mousePressEvent(QMouseEvent * event) override;

    void mouseReleaseEvent(QMouseEvent * event) override;

private:
    WindowData * m_windowData = nullptr;
    WindowHeaderButtons m_buttons = WindowHeaderButton::None;
    QLabel * m_label = nullptr;
    bool m_moveMode = false;
    QPoint m_lastMovePosition;
    QToolButton * m_minimize = nullptr;
    QToolButton * m_maximize = nullptr;
    QToolButton * m_close = nullptr;

    QToolButton * createButton(const QString & name);

    void reloadTr();

    void switchMaximized();
};

} // namespace ads
