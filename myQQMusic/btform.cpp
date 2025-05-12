#include "btform.h"
#include "ui_btform.h"

BtForm::BtForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BtForm)
{
    ui->setupUi(this);

    // 设置linex动画效果
    setline1Animal();

    // 隐藏lineBox中的动画效果
//    ui->line1->hide();
//    ui->line2->hide();
//    ui->line3->hide();
//    ui->line4->hide();


}

BtForm::~BtForm()
{
    delete ui;
}

void BtForm::setIconTextId(const QString &btIcon, const QString &text, int pageid)
{
    // 设置图片
    ui->btIcon->setPixmap(QPixmap(btIcon));

    // 设置文本
    ui->btText->setText(text);

    // 设置id
    this->pageId = pageid;
}

int BtForm::getId()
{
    return pageId;
}

void BtForm::clearBg()
{
    // 清除上一个，恢复之前的
    ui->btStyle->setStyleSheet("#btStyle{ background:#D8D8D8;} "
                               "#btStyle:hover{ background:rgb(170, 170, 255);} "
                               "#btText{ color:black;}");
}

void BtForm::setline1Animal()
{
    // 设置line1的动画效果
    animationLine1 = new QPropertyAnimation(ui->line1, "geometry", this);
    animationLine1->setDuration(1500);
    animationLine1->setKeyValueAt(0, QRect(0, 15, 3, 0));
    animationLine1->setKeyValueAt(0.5, QRect(0, 0, 3, 15));
    animationLine1->setKeyValueAt(1, QRect(0, 15, 3, 0));
    animationLine1->setLoopCount(-1);
    animationLine1->start();

    // 设置line2的动画效果
    animationLine2 = new QPropertyAnimation(ui->line2, "geometry", this);
    animationLine2->setDuration(1600);
    animationLine2->setKeyValueAt(0, QRect(7, 15, 3, 0));
    animationLine2->setKeyValueAt(0.5, QRect(7, 0, 3, 15));
    animationLine2->setKeyValueAt(1, QRect(7, 15, 3, 0));
    animationLine2->setLoopCount(-1);
    animationLine2->start();

    // 设置line3的动画效果
    animationLine3 = new QPropertyAnimation(ui->line3, "geometry", this);
    animationLine3->setDuration(1700);
    animationLine3->setKeyValueAt(0, QRect(14, 15, 3, 0));
    animationLine3->setKeyValueAt(0.5, QRect(14, 0, 3, 15));
    animationLine3->setKeyValueAt(1, QRect(14, 15, 3, 0));
    animationLine3->setLoopCount(-1);
    animationLine3->start();

    // 设置line4的动画效果
    animationLine4 = new QPropertyAnimation(ui->line4, "geometry", this);
    animationLine4->setDuration(1800);
    animationLine4->setKeyValueAt(0, QRect(21, 15, 3, 0));
    animationLine4->setKeyValueAt(0.5, QRect(21, 0, 3, 15));
    animationLine4->setKeyValueAt(1, QRect(21, 15, 3, 0));
    animationLine4->setLoopCount(-1);
    animationLine4->start();
}

//void BtForm::showAnimal()
//{
//    ui->lineBox->show();
//}

void BtForm::mousePressEvent(QMouseEvent *event)
{
    (void)event;

    // 鼠标点击后，设置样式
    // 背景变成绿色，文字变成白色
    ui->btStyle->setStyleSheet("#btStyle{ background:rgb(170, 170, 255);} #btText{ color:#F6F6F6;}");


    // 给myQQMusic发送信号
    emit click(this->pageId);
}
