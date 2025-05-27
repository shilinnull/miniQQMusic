#include "myqqmusic.h"
#include "ui_myqqmusic.h"

#include <QFileDialog>
#include <QDebug>

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

    // 设置窗口边界阴影偏移
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 给窗口设置透明度
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);// 设置阴影偏移
    shadowEffect->setColor("#000000");// 设置阴影颜⾊：⿊⾊
    shadowEffect->setBlurRadius(10); // 设置阴影的模糊半径
    this->setGraphicsEffect(shadowEffect);

    // 设置BodyLeft中6个btForm的信息
    setBtForm_IconTextPageId();

    // 本地下载BtForm动画默认显⽰
    ui->local->showAnimal();


    // 设置默认显示页面
    ui->stackedWidget->setCurrentIndex(0);

    // 添加RecBox图片以及文本
    srand(time(NULL)); // 设置随机种子，让每次推荐的页面不一样
    ui->recMusicBox->initRecBoxUi(RandPicutre(), 1); // 行1
    ui->supplyMusicBox->initRecBoxUi(RandPicutre(), 2); // 行2

    // 设置我喜欢、本地⾳乐、最近播放⻚⾯、设置commonPage的信息
    ui->likePage->setCommonPageUi("我喜欢", ":/images/ilikebg.png");
    ui->localPage->setCommonPageUi("本地音乐", ":/images/localbg.png");
    ui->recentPage->setCommonPageUi("最近播放", ":/images/recentbg.png");
    ui->likePage->setMusicListType(PageType::LIKE_PAGE);
    ui->localPage->setMusicListType(PageType::LOCAL_PAGE);
    ui->recentPage->setMusicListType(PageType::HISTORY_PAGE);

    // 创建⾳量调节窗口对象并挂到对象树
    volumeTool = new VolumeTool(this);
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

QJsonArray myQQMusic::RandPicutre()
{
    // 保存图片文件名
    QVector<QString> vecImageName;
    vecImageName<<"001.png"<<"003.png"<<"004.png"<<"005.png"<<"006.png"<<"007.png"
                <<"008.png"<<"009.png"<<"010.png"<<"011.png"<<"012.png"<<"013.png"
                <<"014.png"<<"015.png"<<"016.png"<<"017.png"<<"018.png"<<"019.png"
                <<"020.png"<<"021.png"<<"022.png"<<"023.png"<<"024.png"<<"025.png"
                <<"026.png"<<"027.png"<<"028.png"<<"029.png"<<"030.png"<<"031.png"
                <<"032.png"<<"033.png"<<"034.png"<<"035.png"<<"036.png"<<"037.png"
                <<"038.png"<<"039.png"<<"040.png";
    // 随机打散
    std::random_shuffle(vecImageName.begin(), vecImageName.end());

    // 设置图片以及名字
    QJsonArray objArray;
    for(int i = 0;i < vecImageName.size(); ++i)
    {
        // 构造路径
        QJsonObject obj;
        obj.insert("path", ":/images/rec/" + vecImageName[i]);

        // 构造文本
        // arg(i, 3, 10, QCchar('0'))
        // i：要放⼊%1位置的数据
        // 3: 三位数
        // 10：表⽰⼗进制数
        // QChar('0')：数字不够三位，前⾯⽤字符'0'填充
        QString strText = QString("推荐-%1").arg(i + 1, 3, 10, QChar('0'));
        obj.insert("text", strText);

        // 构造完路径后，添加到objArray
        objArray.append(obj);
    }

    return objArray;
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


void myQQMusic::on_volume_clicked()
{
    // 先要调整窗⼝的显⽰位置，否则该窗⼝在主窗⼝的左上⻆
    // 1. 获取该按钮左上⻆的图标
    QPoint point = ui->volume->mapToGlobal(QPoint(0, 0));
    // 2. 计算volume窗⼝的左上⻆位置
    // 让该窗⼝显⽰在⿏标点击的正上⽅
    // ⿏标位置：减去窗⼝宽度的⼀半，以及⾼度恰巧就是窗⼝的左上⻆
    QPoint volumeLeftTop = point - QPoint(volumeTool->width()/2, volumeTool->height());
    // 微调窗⼝位置
    volumeLeftTop.setY(volumeLeftTop.y()+30);
    volumeLeftTop.setX(volumeLeftTop.x()+15);
    // 3. 移动窗⼝位置
    volumeTool->move(volumeLeftTop);
    // 4. 将窗⼝显⽰出来
    volumeTool->show();
}

void myQQMusic::on_addLocal_clicked()
{
    qDebug() << "on_addLocal_clicked";
    // 1. 创建一个文件对话框
    QFileDialog fileDialog(this);
    fileDialog.setWindowTitle("添加本地音乐");

    // 2. 创建一个打开格式的文件对话框
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);

    // 3. 设置对话框模式
    // 能选择文件，并且一次性可以选择多个存在的文件
    fileDialog.setFileMode(QFileDialog::ExistingFiles);

    // 4. 设置对话框的MIME过滤器
    /*
        MIME类型(Multipurpose Internet Mail Extensions)是⼀种互联⽹标准，
        ⽤于表⽰⽂档、⽂件或字节流的性质和格式。
    */
    QStringList mimeList;
    mimeList << "application/octet-stream"; // 表⽰通⽤的⼆进制数据流的MIME类型
    fileDialog.setMimeTypeFilters(mimeList);

    // 5. 设置对话框默认的打开路径，设置目录当前工程所在目录
    QDir dir(QDir::currentPath());
    dir.cdUp();
    QString musicPath = dir.path() + "/myQQMusic/musics/";
    fileDialog.setDirectory(musicPath); // 设置路径

     qDebug() << "on_addLocal_clicked";
    // 6. 显示对话框
    if(fileDialog.exec() == QFileDialog::Accepted)
    {
        // 切换到本地音乐界面，准备添加音乐
        ui->stackedWidget->setCurrentIndex(4);

        // 获取对话框选中的url
        QList<QUrl> urls = fileDialog.selectedUrls();

        // 将歌曲文件交给musicList进行管理
        // 管理的是解析music对象
        musiclist.addMusicByUrl(urls);

        qDebug() << musiclist.musicList.size();
        // 将歌曲信息更新到commonpage页面中的listwidget中(本地页面)
        ui->localPage->reFresh(musiclist);
    }
}


void myQQMusic::on_min_clicked()
{
//    this->hide();
}
