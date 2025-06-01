#include "listitembox.h"
#include "ui_listitembox.h"
#include <QDebug>

ListItemBox::ListItemBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItemBox),
    isLike(false)
{
    ui->setupUi(this);

    // 链接槽函数
    connect(ui->likeBtn, &QPushButton::clicked, this, &ListItemBox::onLikeBtnClicked);
}

ListItemBox::~ListItemBox()
{
    qDebug() << "ListItemBox delete";
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
    if(isLike)
    {
        ui->likeBtn->setIcon(QIcon(":/images/like_2.png"));
    }
    else
    {
        ui->likeBtn->setIcon(QIcon(":/images/like_3.png"));
    }
}

void ListItemBox::onLikeBtnClicked()
{
    isLike = !isLike;
    setIsLike(isLike);
    emit setIsLike(isLike);
}

void ListItemBox::enterEvent(QEvent *event)
{
    (void)event;
    setStyleSheet("background-color:#EFEFEF");
}

void ListItemBox::leaveEvent(QEvent *event)
{
    (void)event;
    setStyleSheet("");
}
