#include "btform.h"
#include "ui_btform.h"

BtForm::BtForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BtForm)
{
    ui->setupUi(this);
    ui->lineBox->hide();
    setline1Animal();       // 设置lineBox动画效果
}

BtForm::~BtForm()
{
    delete ui;
}

void BtForm::setIconTextId(const QString &btIcon, const QString &text, int pageid)
{
    ui->btIcon->setPixmap(QPixmap(btIcon)); // 设置图片
    ui->btText->setText(text);              // 设置文本
    this->pageId = pageid;                  // 设置页面ID
}

int BtForm::getId()
{
    return pageId;
}

void BtForm::clearBg()
{
    // 恢复默认样式
    ui->btStyle->setStyleSheet("#btStyle{ background:rgb(240,240,240);} "
                               "#btStyle:hover{ background:rgb(233,233,233);} "
                               "#btText{ color:black;}");
}

void BtForm::setline1Animal()
{
    // 设置line1的动画效果
    animationLine1 = new QPropertyAnimation(ui->line1, "geometry", this);
    animationLine1->setDuration(1500);
    animationLine1->setKeyValueAt(0, QRect(0, 15, 2, 0)); // 设置关键帧
    animationLine1->setKeyValueAt(0.5, QRect(0, 0, 2, 15));
    animationLine1->setKeyValueAt(1, QRect(0, 15, 2, 0));
    animationLine1->setLoopCount(-1); // 无限次
    animationLine1->start();

    // 设置line2的动画效果
    animationLine2 = new QPropertyAnimation(ui->line2, "geometry", this);
    animationLine2->setDuration(1650);
    animationLine2->setKeyValueAt(0, QRect(7, 15, 2, 0));
    animationLine2->setKeyValueAt(0.5, QRect(7, 0, 2, 15));
    animationLine2->setKeyValueAt(1, QRect(7, 15, 2, 0));
    animationLine2->setLoopCount(-1);
    animationLine2->start();

    // 设置line3的动画效果
    animationLine3 = new QPropertyAnimation(ui->line3, "geometry", this);
    animationLine3->setDuration(1750);
    animationLine3->setKeyValueAt(0, QRect(14, 15, 2, 0));
    animationLine3->setKeyValueAt(0.5, QRect(14, 0, 2, 15));
    animationLine3->setKeyValueAt(1, QRect(14, 15, 2, 0));
    animationLine3->setLoopCount(-1);
    animationLine3->start();

    // 设置line4的动画效果
    animationLine4 = new QPropertyAnimation(ui->line4, "geometry", this);
    animationLine4->setDuration(1850);
    animationLine4->setKeyValueAt(0, QRect(21, 15, 2, 0));
    animationLine4->setKeyValueAt(0.5, QRect(21, 0, 2, 15));
    animationLine4->setKeyValueAt(1, QRect(21, 15, 2, 0));
    animationLine4->setLoopCount(-1);
    animationLine4->start();
}

void BtForm::showAnimal(bool isShow)
{
    if(isShow)
    {
        ui->lineBox->show();
    }
    else
    {
        ui->lineBox->hide();
    }
}

void BtForm::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    // 鼠标点击后设置选中样式
    ui->btStyle->setStyleSheet("#btStyle{ background:rgb(216,216,216);} \
                                #btText{ color:black; font-weight: bold;}");

    // 发送点击信号
    emit click(this->pageId);
}
