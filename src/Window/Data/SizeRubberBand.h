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

    void start();

    void stop();

    void updateGeometry(const QRect & newGeometry);

protected:
    void paintEvent(QPaintEvent * event) override;

private:
    QWidget * m_sizingWindow = nullptr;
    bool m_resizeStarted = false;
    bool m_rubberResize = false;
};

} // namespace ads
