#ifndef VOLUMETOOL_H
#define VOLUMETOOL_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

namespace Ui {
class VolumeTool;
}

class VolumeTool : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeTool(QWidget *parent = nullptr);
    ~VolumeTool();
    // 设置是否静音
    void onSilenceBtnClicked();
    // 设置音量大小
    void setVolume();

signals:
    void setSilence(bool);
    // 设置音量大小
    void setMusicVolume(int);
protected:
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject* object, QEvent* event)override;

private:
    Ui::VolumeTool *ui;

    // 设置静音
    bool isMuted;
    // 设置音量大小
    int volumeRatio;
};

#endif // VOLUMETOOL_H
