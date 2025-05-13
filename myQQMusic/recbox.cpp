#include "recbox.h"
#include "ui_recbox.h"

#include "recboxitem.h"

RecBox::RecBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBox),
    row(1),
    col(4)
{
    ui->setupUi(this);
}

RecBox::~RecBox()
{
    delete ui;
}

void RecBox::initRecBoxUi(QJsonArray data, int row)
{
    // 初始化
    imageList = data;
    currentIndex = 0; // 默认显示第0组
    count = imageList.size() / col; // 总共行


    // 如果是两⾏，说明当前RecBox是主界⾯上的supplyMusicBox
    if(row == 2)
    {
        this->row = row;
        this->col = 8;  // 注意：这里需要是8
    }
    else
    {
        ui->recListDown->hide();
    }
    imageList = data;

    // 往RecBox中添加图⽚
    createRecItem();
}

void RecBox::createRecItem()
{
    // 删除旧元素
    QList<RecBoxItem*> recUpList = ui->recListUp->findChildren<RecBoxItem*>();
    for(auto e : recUpList)
    {
        ui->recListUpHLayout->removeWidget(e);
        delete e;
    }

    QList<RecBoxItem*> recDownList = ui->recListDown->findChildren<RecBoxItem*>();
    for(auto e : recDownList)
    {
        ui->recListDownHLayout->removeWidget(e);
        delete e;
    }

    // 创建RecBoxItem对象，往RecBox中添加
    int index = 0;
    // currentIndex * col 为当前分组乘以列-->偏移出下一组
    for(int i = currentIndex * col; i < col + col * currentIndex; i++)
    {
        RecBoxItem* item = new RecBoxItem();

        // 设置图片与对应的文本
        QJsonObject obj = imageList[i].toObject();
        item->setText(obj.value("text").toString());
        item->setImage(obj.value("path").toString());

        // recMusicBox：col为4，元素添加到ui->recListUpHLayout中
        // supplyMuscBox: col为8， ui->recListUpHLayout添加4个，ui- >recListDownHLayout添加4个
        // 即supplyMuscBox上下两⾏都要添加
        // 如果是recMusicBox：row为1，只能执⾏else，所有4个RecBoxItem都添加到ui- >recListUpHLayout中
        // 如果是supplyMuscBox：row为2，col为8，col/2结果为4，i为0 1 2 3时，元素添加到ui->recListDownHLayout中
        // i为4 5 6 7时，元素添加到ui->recListUpHLayout中
        if(index >= col / 2 && row == 2)
            ui->recListDownHLayout->addWidget(item);
        else
           ui->recListUpHLayout->addWidget(item); // 将对象设置到RecBox中
        ++index;
    }
}

void RecBox::on_btDown_clicked()
{
    currentIndex++;
    if(currentIndex >= count)
        currentIndex = 0;

    // 在创建新的时候删除旧的
    createRecItem();
}

void RecBox::on_btUp_clicked()
{
    currentIndex--;
    if(currentIndex < 0)
        currentIndex = count - 1;

    createRecItem();
}
