#pragma once

#include <QPointer>
#include <QVector>
#include <QWidget>

#include "Window/Data/Common.h"

namespace ads {

class Resizer;
class SizeRubberBand;
class TripleShadow;
class WindowBackground;

class WindowData : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor shadowColor READ shadowColor WRITE setShadowColor)
    Q_PROPERTY(ShadowStyle shadowStyle READ shadowStyle WRITE setShadowStyle)
    Q_PROPERTY(int gripSize READ gripSize WRITE setGripSize)
    Q_PROPERTY(bool rubberOnResize READ rubberOnResize WRITE setRubberOnResize)
    Q_PROPERTY(int rubberBorderRadius READ rubberBorderRadius WRITE setRubberBorderRadius)
    Q_PROPERTY(int rubberBorderWidth READ rubberBorderWidth WRITE setRubberBorderWidth)
    Q_PROPERTY(QColor rubberBorderColor READ rubberBorderColor WRITE setRubberBorderColor)
    Q_PROPERTY(QBrush rubberBackgroundColor READ rubberBackgroundColor WRITE setRubberBackgroundColor)
public:
    static const int DEFAULT_GRIP_SIZE;

    WindowData(QWidget * controlledWindow, WindowHeaderButtons buttons);

    ~WindowData();

    WindowBackground * background() const
    {
        return m_background;
    }

    bool rubberOnResize() const;
    void setRubberOnResize(bool rubberOnResize);

    int gripSize() const noexcept
    {
        return m_gripSize;
    }
    void setGripSize(int gripSize);

    bool isResizeEnabled() const;
    void setResizeEnabled(bool enabled);

    int rubberBorderRadius() const;
    void setRubberBorderRadius(int borderRadius);
    int rubberBorderWidth() const;
    void setRubberBorderWidth(int borderWidth);
    QColor rubberBorderColor() const;
    void setRubberBorderColor(const QColor & borderColor);
    QBrush rubberBackgroundColor() const;
    void setRubberBackgroundColor(const QBrush & backgroundColor);

    QColor shadowColor() const;
    void setShadowColor(const QColor & shadowColor);

    ShadowStyle shadowStyle() const;
    void setShadowStyle(ShadowStyle shadowStyle);

    QWidget * sizingWindow() const
    {
        return m_sizingWindow;
    }

    void hideShadow();
    void showShadow();

protected:
    bool eventFilter(QObject * watched, QEvent * event) override;

private:
    QWidget * m_sizingWindow = nullptr;
    TripleShadow * m_shadow = nullptr;
    WindowBackground * m_background = nullptr;
    QVector<Resizer *> m_resizers;
    SizeRubberBand * m_sizeRubberBand = nullptr;
    int m_gripSize = DEFAULT_GRIP_SIZE;

    void updateResizers();
};

} // namespace ads
