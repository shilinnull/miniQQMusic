#include "commonpage.h"
#include "ui_commonpage.h"

CommonPage::CommonPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonPage)
{
    ui->setupUi(this);
}

CommonPage::~CommonPage()
{
    delete ui;
}

void CommonPage::setCommonPageUi(const QString &title, const QString &imagePath)
{
    // 设置标题
    ui->pageTittle->setText(title);
    // 设置封面
    ui->musicImageLabel->setPixmap(QPixmap(imagePath));
    ui->musicImageLabel->setScaledContents(true); // 自动拉伸

    // 测试
    ListItemBox* listItemBox = new ListItemBox(this);
    QListWidgetItem* listWidgetItem = new QListWidgetItem(ui->pageMusicList);
    listWidgetItem->setSizeHint(QSize(ui->pageMusicList->width(), ui->pageMusicList->height()));
    ui->pageMusicList->setItemWidget(listWidgetItem, listItemBox);

}
