#include "recboxitem.h"
#include "ui_recboxitem.h"

RecBoxItem::RecBoxItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBoxItem)
{
    ui->setupUi(this);
    // 安转事件过滤器
    ui->musicImageBox->installEventFilter(this);
}

RecBoxItem::~RecBoxItem()
{
    delete ui;
}

bool RecBoxItem::eventFilter(QObject *watched, QEvent *event)
{
    // 注意：recItem上有⼀个按钮，当⿏标放在按钮上时在开启动画
    if(watched == ui->musicImageBox)
    {
        int ImgWidget = ui->musicImageBox->width();
        int ImgHeight = ui->musicImageBox->height();

        // 拦截鼠标进入时间
        if(event->type() == QEvent::Enter)
        {
            QPropertyAnimation* animation = new QPropertyAnimation(ui->musicImageBox, "geometry");
            animation->setDuration(150);
            animation->setStartValue(QRect(9, 9,ImgWidget, ImgHeight));
            animation->setEndValue(QRect(9, 0, ImgWidget, ImgHeight));
            animation->start();

            //注意：动画结束的时候会触发finished信号，拦截到该信号，销毁animatiom
            connect(animation, &QPropertyAnimation::finished, this, [=](){
                delete animation;
            });
            return true;
        }
        else if(event->type() == QEvent::Leave)
        {
            // 拦截⿏标离开事件
            QPropertyAnimation* animation = new QPropertyAnimation(ui->musicImageBox, "geometry");
            animation->setDuration(150);
            animation->setStartValue(QRect(9,0,ImgWidget,ImgHeight));
            animation->setEndValue(QRect(9, 9, ImgWidget, ImgHeight));
            animation->start();
            // 注意：动画结束的时候会触发finished信号，拦截到该信号，销毁animation
            connect(animation, &QPropertyAnimation::finished, this, [=](){
                delete animation;
            });
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}

void RecBoxItem::setText(const QString &text)
{
    ui->recBoxItemText->setText(text);
}

void RecBoxItem::setImage(const QString &imagePath)
{
    // 设置图片路径
    QString imgStyle = "border-image:url(" + imagePath + ");";
    ui->recMusicImage->setStyleSheet(imgStyle);
}
