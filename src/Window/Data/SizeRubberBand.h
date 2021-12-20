#pragma once

#include <QRubberBand>

namespace ads {

class SizeRubberBand : public QWidget
{
    Q_OBJECT
public:
    SizeRubberBand(QWidget * sizingWindow);

    bool isResized() const noexcept
    {
        return m_resizeStarted;
    }

    bool isRubberResize() const
    {
        return m_rubberResize;
    }
    void setRubberResize(bool rubberResize)
    {
        m_rubberResize = rubberResize;
    }

    QSize layoutMinimumSize() const;

    QSize layoutMaximumSize() const;

    QWidget * sizingWindow() const
    {
        return m_sizingWindow;
    }

    const QRect & oldGeometry() const;

    int borderRadius() const
    {
        return m_borderRadius;
    }
    void setBorderRadius(int borderRadius)
    {
        m_borderRadius = borderRadius;
    }
    int borderWidth() const
    {
        return m_borderWidth;
    }
    void setBorderWidth(int borderWidth)
    {
        m_borderWidth = borderWidth;
    }
    QColor borderColor() const
    {
        return m_borderColor;
    }
    void setBorderColor(const QColor & borderColor)
    {
        m_borderColor = borderColor;
    }
    QBrush backgroundColor() const
    {
        return m_backgroundColor;
    }
    void setBackgroundColor(const QBrush & backgroundColor)
    {
        m_backgroundColor = backgroundColor;
    }

    void start();

    void stop();

    void updateGeometry(const QRect & newGeometry);

protected:
    void paintEvent(QPaintEvent * event) override;

private:
    QWidget * m_sizingWindow = nullptr;
    bool m_resizeStarted = false;
    bool m_rubberResize = false;
    int m_borderRadius = 0;
    int m_borderWidth = 1;
    QColor m_borderColor{0, 120, 215, 255};
    QBrush m_backgroundColor{QColor{0, 25, 153, 25}};
};

} // namespace ads
