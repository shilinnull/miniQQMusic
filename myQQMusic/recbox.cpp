#include "recbox.h"
#include "ui_recbox.h"
<<<<<<< HEAD

=======
#include "recboxitem.h"
>>>>>>> c765204f81f562b90e8f9ac3da79b36f5bd04213

/**
 * @brief RecBox::RecBox 构造函数
 * 初始化推荐框组件，设置默认行列数
 * @param parent 父窗口指针
 */
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

/**
 * @brief RecBox::~RecBox 析构函数
 * 释放UI资源
 */
RecBox::~RecBox()
{
    delete ui;
}

/**
 * @brief RecBox::initRecBoxUi 初始化推荐框UI
 * 根据数据和行数配置推荐框布局和内容
 * @param data 包含推荐项信息的JSON数组
 * @param row 显示行数（1或2）
 */
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

/**
 * @brief RecBox::createRecItem 创建推荐项
 * 根据当前索引创建并添加推荐项到布局中
 * 自动清理旧的推荐项，防止内存泄漏
 */
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

/**
 * @brief RecBox::on_btDown_clicked 向下翻页按钮点击事件
 * 切换到下一组推荐内容（循环翻页）
 */
void RecBox::on_btDown_clicked()
{
    currentIndex = (currentIndex + 1) % count;
    createRecItem();
}

/**
 * @brief RecBox::on_btUp_clicked 向上翻页按钮点击事件
 * 切换到上一组推荐内容（循环翻页）
 */
void RecBox::on_btUp_clicked()
{
    currentIndex = (currentIndex - 1 + count) % count;
    createRecItem();
}
