#include "myqqmusic.h"
#include "ui_myqqmusic.h"

myQQMusic::myQQMusic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myQQMusic)
{
    ui->setupUi(this);

    // 初始化Ui
    InitUi();
    // 初始化信号
    connectSignalAndSlot();
}

myQQMusic::~myQQMusic()
{
    delete ui;
}
void myQQMusic::InitUi()
{
    // 将主窗口的标题栏隐藏
    this->setWindowFlag(Qt::FramelessWindowHint);

    // 设置窗口透明度
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 给窗口设置透明度
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);// 设置阴影偏移
    shadowEffect->setColor("#000000");// 设置阴影颜⾊：⿊⾊
    shadowEffect->setBlurRadius(10); // 设置阴影的模糊半径
    this->setGraphicsEffect(shadowEffect);

    // 设置BodyLeft中6个btForm的信息
    setBtForm_IconTextPageId();
}

void myQQMusic::setBtForm_IconTextPageId() const
{
    ui->rec->setIconTextId(":/images/rec.png", "推荐", 0);
    ui->music->setIconTextId(":/images/music.png", "音乐馆", 1);
    ui->radio->setIconTextId(":/images/radio.png", "电台", 2);
    ui->like->setIconTextId(":/images/like.png", "我喜欢", 3);
    ui->local->setIconTextId(":/images/local.png", "本地下载", 4);
    ui->recent->setIconTextId(":/images/recent.png", "最近播放", 5);
}

void myQQMusic::connectSignalAndSlot() const
{
    // 处理btForm按钮点击的信号，切换对应的页面，同时把按钮的上一个颜色恢复到原来的颜色
    connect(ui->rec, &BtForm::click, this, &myQQMusic::onBtFormClick);
    connect(ui->music, &BtForm::click, this, &myQQMusic::onBtFormClick);
    connect(ui->radio, &BtForm::click, this, &myQQMusic::onBtFormClick);
    connect(ui->like, &BtForm::click, this, &myQQMusic::onBtFormClick);
    connect(ui->local, &BtForm::click, this, &myQQMusic::onBtFormClick);
    connect(ui->recent, &BtForm::click, this, &myQQMusic::onBtFormClick);

}

void myQQMusic::onBtFormClick(int pageid) const
{
    // 清除当前页面所有btFrom按钮背景颜色
    // 1.获取当前⻚⾯所有btFrom按钮类型的对象
    QList<BtForm*> buttonList = this->findChildren<BtForm*>();
    // 2.遍历所有对象, 如果不是当前id的按钮,则把之前设置的背景颜⾊清除掉
    foreach (BtForm* btitem, buttonList)
    {
        if(pageid != btitem->getId())
        {
            btitem->clearBg();
        }
    }
    // 3.显⽰⻚⾯
    ui->stackedWidget->setCurrentIndex(pageid);
}

void myQQMusic::mousePressEvent(QMouseEvent *event)
{
    // 按下鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        // 记录位置，获取⿏标相对于屏幕左上⻆的全局坐标
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        return;
    }
    QWidget::mousePressEvent(event);
}

void myQQMusic::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        this->move(event->globalPos() - dragPosition);
        return;
    }
    QWidget::mouseMoveEvent(event);
}


void myQQMusic::on_quit_clicked()
{
    this->close();
}

