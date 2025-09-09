#ifndef MUSICSLIDER_H
#define MUSICSLIDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class MusicSlider;
}

class MusicSlider : public QWidget
{
    Q_OBJECT

public:
    explicit MusicSlider(QWidget *parent = nullptr);
    ~MusicSlider();

    void moveSilder();
    void setStep(float bf);

signals:
    void setMusicSliderPosition(float position);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::MusicSlider *ui;
    int currentPos;
    int maxWidth;
};

#endif // MUSICSLIDER_H
