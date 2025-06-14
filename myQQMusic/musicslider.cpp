#include "musicslider.h"
#include "ui_musicslider.h"

#include <QDebug>

MusicSlider::MusicSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicSlider)
{
    ui->setupUi(this);

    currentPos = 0;
    maxWidth = width();

    moveSilder();
}

MusicSlider::~MusicSlider()
{
    delete ui;
}

void MusicSlider::moveSilder()
{
    ui->outLine->setMaximumWidth(currentPos);
    ui->outLine->setGeometry(ui->outLine->x(), ui->outLine->y(), currentPos, ui->outLine->height());
}

void MusicSlider::setStep(float bf)
{
    currentPos = maxWidth * bf;
    moveSilder();
}

void MusicSlider::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";
    currentPos = event->pos().x();
    moveSilder();
}

void MusicSlider::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mouseMoveEvent";
    // 鼠标要在矩形内
    QRect rect = QRect(0, 0, width(), height());
    QPoint pos = event->pos();
    if(!rect.contains(pos))
    {
        qDebug() << "!rect.contains(pos)";
        return;
    }
    // 根据⿏标滑动的位置更新outLine的宽度
    if(event->buttons() == Qt::LeftButton)
    {
        currentPos = event->pos().x();
        if(currentPos < 0)
        {
            currentPos = 0;
        }
        if(currentPos > maxWidth)
        {
            currentPos = maxWidth;
        }
        qDebug() << currentPos;
        moveSilder();
    }
}

void MusicSlider::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouseReleaseEvent";
    currentPos = event->pos().x();
    moveSilder();
    // 发射信号告诉 QQMusic
    emit setMusicSliderPosition((float)currentPos / maxWidth);
}
