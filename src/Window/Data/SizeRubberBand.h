#pragma once

#include <QWidget>

namespace ads
{

class SizeRubberBand : public QWidget
{
    Q_OBJECT
public:
    explicit SizeRubberBand(QWidget* sizingWindow);

    QWidget* sizingWindow() const { return m_sizingWindow; }

protected:
private:
    QWidget* m_sizingWindow = nullptr;
};

}  // namespace ads
