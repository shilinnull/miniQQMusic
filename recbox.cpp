#include "recbox.h"
#include "ui_recbox.h"

RecBox::RecBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBox),
    row(1),       // 默认行数：1行
    col(4),       // 默认列数：4列
    currentIndex(0),
    count(0)
{
    ui->setupUi(this);
}

RecBox::~RecBox()
{
    delete ui;
}

void RecBox::initRecBoxUi(QJsonArray data, int row)
{
    imageList = data;

    // 配置布局：单行或双行
    if(row == 2)
    {
        this->row = row;
        col = 8;  // 双行布局时显示8列（每行4列）
    }
    else
    {
        ui->recListDown->hide(); // 单行布局时隐藏下行
    }

    // 初始化分页控制
    currentIndex = 0;          // 从第0组开始显示
    count = imageList.size() / col + (imageList.size() % col > 0 ? 1 : 0); // 计算总组数

    createRecItem();           // 创建推荐项
}

void RecBox::createRecItem()
{
    // 清理上行旧项
    QList<RecBoxItem*> recUpList = ui->recListUp->findChildren<RecBoxItem*>();
    for(auto item : recUpList)
    {
        ui->recListUpHLayout->removeWidget(item);
        delete item;
    }

    // 清理下行旧项
    QList<RecBoxItem*> recDownList = ui->recListDown->findChildren<RecBoxItem*>();
    for(auto item : recDownList)
    {
        ui->recListDownHLayout->removeWidget(item);
        delete item;
    }

    // 创建新推荐项
    int index = 0;
    const int start = currentIndex * col;
    const int end = qMin(start + col, imageList.size());

    for(int i = start; i < end; i++)
    {
        RecBoxItem* item = new RecBoxItem();
        QJsonObject obj = imageList[i].toObject();

        item->setText(obj.value("text").toString());
        item->setImage(obj.value("path").toString());

        // 根据索引决定添加到上行还是下行布局
        if(row == 2 && index >= col / 2)
            ui->recListDownHLayout->addWidget(item);
        else
            ui->recListUpHLayout->addWidget(item);

        ++index;
    }
}

void RecBox::on_btDown_clicked()
{
    currentIndex = (currentIndex + 1) % count;
    createRecItem();
}

void RecBox::on_btUp_clicked()
{
    currentIndex = (currentIndex - 1 + count) % count;
    createRecItem();
}
