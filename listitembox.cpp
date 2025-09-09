#include "listitembox.h"
#include "ui_listitembox.h"
#include <QMouseEvent>

ListItemBox::ListItemBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItemBox),
    isLike(false)
{
    ui->setupUi(this);

    // 连接喜欢按钮点击信号到槽函数
    connect(ui->likeBtn, &QPushButton::clicked, this, &ListItemBox::onLikeBtnClicked);
}

ListItemBox::~ListItemBox()
{
    delete ui;
}

void ListItemBox::setMusicName(const QString &name)
{
    ui->musicNameLabel->setText(name);
}

void ListItemBox::setSingerName(const QString &singer)
{
    ui->musicSingerLabel->setText(singer);
}

void ListItemBox::setAlbumName(const QString &albumName)
{
    ui->albumNameLabel->setText(albumName);
}

void ListItemBox::setLikeIcon(bool like)
{
    isLike = like;
    ui->likeBtn->setIcon(QIcon(isLike ? ":/images/like_2.png" : ":/images/like_3.png"));
}

void ListItemBox::onLikeBtnClicked()
{
    isLike = !isLike;
    setLikeIcon(isLike);
    emit setIsLike(isLike);
}

void ListItemBox::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("background-color:#EFEFEF");
}

void ListItemBox::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("");
}
