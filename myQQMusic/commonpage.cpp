#include "commonpage.h"
#include "ui_commonpage.h"

#include <QDebug>

CommonPage::CommonPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonPage)
{
    ui->setupUi(this);

    // 去除水平滚动条
    ui->pageMusicList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

CommonPage::~CommonPage()
{
    delete ui;
}

void CommonPage::setMusicListType(PageType pagetype)
{
    this->pageType = pagetype;
}

void CommonPage::reFresh(MusicList& musiclist)
{
    // 将QListWidget之前已经添加的内容清空
    ui->pageMusicList->clear();

    // 添加新的歌曲
    addMusicToMusicPage(musiclist);
    qDebug() << "musicListOfPage: " << musicListOfPage.size();

    for(auto musicId : musicListOfPage)
    {
        auto it = musiclist.findMusicByMusicid(musicId);
        if(it == musiclist.end())
            continue;

        // 将Music的歌曲名称、作者、专辑名称更新到界面
        ListItemBox* listItemBox = new ListItemBox(this);
        // 设置歌曲名称、作者、专辑名称更新到界面
        listItemBox->setMusicName(it->getMusicName());
        listItemBox->setSingerName(it->getSingerName());
        listItemBox->setAlbumName(it->getAlbumName());
        listItemBox->setLikeIcon(it->getIsLike());

        // new一个item
        QListWidgetItem* item = new QListWidgetItem(ui->pageMusicList);
        item->setSizeHint(QSize(listItemBox->width(), listItemBox->height())); // 设置大小
        ui->pageMusicList->setItemWidget(item, listItemBox); // 设置到pageMusicList
    }

    // 重绘
    repaint(); // ⽴即执⾏paintEvent()
    // update()   // 将⼀个paintEvent事件添加到事件队列中，等待稍后执行，即不会立即执行 paintEvent
}

void CommonPage::setCommonPageUi(const QString &title, const QString &imagePath)
{
    // 设置标题
    ui->pageTittle->setText(title);
    // 设置封面
    ui->musicImageLabel->setPixmap(QPixmap(imagePath));
    ui->musicImageLabel->setScaledContents(true); // 自动拉伸

    // 测试
//    ListItemBox* listItemBox = new ListItemBox(this);
//    QListWidgetItem* listWidgetItem = new QListWidgetItem(ui->pageMusicList);
//    listWidgetItem->setSizeHint(QSize(ui->pageMusicList->width(), ui->pageMusicList->height()));
//    ui->pageMusicList->setItemWidget(listWidgetItem, listItemBox);

}

void CommonPage::addMusicToMusicPage(MusicList &musiclist)
{
    // 将旧内容清空
    musicListOfPage.clear();

    // 遍历musiclist进行添加
    for(auto music : musiclist)
    {
        switch(pageType)
        {
        case LIKE_PAGE:
            if(music.getIsLike())
            {
                musicListOfPage.push_back(music.getMusicId());
            }
            break;
        case LOCAL_PAGE:
            musicListOfPage.push_back(music.getMusicId());
            break;
        case HISTORY_PAGE:
            if(music.getIsHistory())
            {
                musicListOfPage.push_back(music.getMusicId());
            }
            break;
        default:
            qDebug() << "未支持页面";
            break;
        }
    }
}
