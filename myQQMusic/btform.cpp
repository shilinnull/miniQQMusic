#include "btform.h"
#include "ui_btform.h"

BtForm::BtForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BtForm)
{
    ui->setupUi(this);
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

void BtForm::mousePressEvent(QMouseEvent *event)
{
    (void)event;

    // 鼠标点击后，设置样式
    // 背景变成绿色，文字变成白色
    ui->btStyle->setStyleSheet("#btStyle{ background:rgb(170, 170, 255);} #btText{ color:#F6F6F6;}");

    // 给myQQMusic发送信号
    emit click(this->pageId);
}
