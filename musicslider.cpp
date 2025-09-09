#include "musicslider.h"
#include "ui_musicslider.h"


MusicSlider::MusicSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicSlider)
{
    ui->setupUi(this);

    currentPos = 0;
    maxWidth = this->width();

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
    // 确保currentPos不会为负值或超过maxWidth
    if(currentPos < 0)
    {
        currentPos = 0;
    }
    if(currentPos > maxWidth)
    {
        currentPos = maxWidth;
    }
    moveSilder();
}

void MusicSlider::mousePressEvent(QMouseEvent *event)
{
    currentPos = event->pos().x();
    moveSilder();
}

void MusicSlider::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标要在矩形内
    QRect rect = QRect(0, 0, width(), height());
    QPoint pos = event->pos();
    if(!rect.contains(pos))
        return;

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
        moveSilder();
    }
}

void MusicSlider::mouseReleaseEvent(QMouseEvent *event)
{
    currentPos = event->pos().x();
    moveSilder();
    // 发射信号告诉 QQMusic
    emit setMusicSliderPosition((float)currentPos / maxWidth);
}
