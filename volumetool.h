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

    void onSilenceBtnClicked();
    void setVolume();

signals:
    void setSilence(bool muted);
    void setMusicVolume(int ratio);

protected:
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject* object, QEvent* event) override;

private:
    Ui::VolumeTool *ui;
    bool isMuted;
    int volumeRatio;
};

#endif // VOLUMETOOL_H
