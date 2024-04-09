#pragma once

#include "Window/Data/Common.h"

namespace ads
{

class Resizer;
class SizeRubberBand;
class TripleShadow;
class WindowBackground;

constexpr int c_defaultGripSize = 8;

class WindowData : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor shadowColor READ shadowColor WRITE setShadowColor)
    Q_PROPERTY(ShadowStyle shadowStyle READ shadowStyle WRITE setShadowStyle)
    Q_PROPERTY(int gripSize READ gripSize WRITE setGripSize)
public:
    WindowData(QWidget* controlledWindow, WindowHeaderButtons buttons);

    ~WindowData() override;

    WindowBackground* background() const { return m_background; }

    int gripSize() const noexcept { return m_gripSize; }
    void setGripSize(int gripSize);

    bool isResizeEnabled() const;
    void setResizeEnabled(bool enabled);

    QColor shadowColor() const;
    void setShadowColor(const QColor& shadowColor);

    ShadowStyle shadowStyle() const;
    void setShadowStyle(ShadowStyle shadowStyle);

    QWidget* sizingWindow() const { return m_sizingWindow; }

    void hideShadow();
    void showShadow();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    QWidget* m_sizingWindow = nullptr;
    TripleShadow* m_shadow = nullptr;
    WindowBackground* m_background = nullptr;
    QList<Resizer*> m_resizerList;
    SizeRubberBand* m_sizeRubberBand = nullptr;
    int m_gripSize = c_defaultGripSize;

    void updateResizers();
};

}  // namespace ads
