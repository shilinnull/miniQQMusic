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

    // 设置滑杆
    void moveSilder();
    // 设置滑杆每次走的长度
    void setStep(float bf);

signals:
    void setMusicSliderPosition(float);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::MusicSlider *ui;

    // 当前位置
    int currentPos;
    // 最大宽度
    int maxWidth;
};

#endif // MUSICSLIDER_H
