#include "listitembox.h"
#include "ui_listitembox.h"

ListItemBox::ListItemBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItemBox),
    isLike(false)
{
    ui->setupUi(this);
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
    if(isLike)
    {
        ui->likeBtn->setIcon(QIcon(":/images/like_2.png"));
    }
    else
    {
        ui->likeBtn->setIcon(QIcon(":/images/like_3.png"));
    }
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
