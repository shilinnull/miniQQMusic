#include "miniqqmusic.h"
#include "ui_miniqqmusic.h"

miniQQMusic::miniQQMusic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::miniQQMusic)
    , isDrag(false)
    , currentIndex(-1)
    , totalDuration(0)
{
    ui->setupUi(this);

    // 初始化Ui
    InitUi();

    // 初始化数据库
    initSqlite();

    // 初始化MusicList
    initMusicList();

    // 初始化媒体
    initPlayer();

    // 初始化信号
    connectSignalAndSlot();
}

miniQQMusic::~miniQQMusic()
{
    delete ui;
}

void miniQQMusic::InitUi()
{
    // 将主窗口的标题栏隐藏
    this->setWindowFlag(Qt::FramelessWindowHint);

    // 设置窗口边界阴影偏移
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 设置窗口图标
    this->setWindowIcon(QIcon(":/images/tubiao.png"));

    this->setWindowTitle("miniQQMusic");

    // 给窗口设置透明度
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);// 设置阴影偏移
    shadowEffect->setColor("#000000");// 设置阴影颜⾊：⿊⾊
    shadowEffect->setBlurRadius(5); // 设置阴影的模糊半径
    // this->setGraphicsEffect(shadowEffect); // 不能这样设置，否则会报参数错误
    ui->background->setGraphicsEffect(shadowEffect); // 应该设置到背景上

    // 添加托盘图标
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/tubiao.png"));

    // 创建托盘菜单
    QMenu *trayMenu = new QMenu(this);
    trayMenu->addAction("还原", this, &QWidget::showNormal);
    trayMenu->addSeparator();
    trayMenu->addAction("退出", this, &miniQQMusic::quitQQMusic);
    trayIcon->setContextMenu(trayMenu); // 将托盘菜单添加到托盘图标
    trayIcon->show(); // 显示

    // 设置BodyLeft中6个btForm的信息
    setBtForm_IconTextPageId();

    // 设置默认显示页面
    ui->stackedWidget->setCurrentIndex(4);

    // 将localPage设置为当前⻚⾯
    curPage = ui->localPage;
    updateBtformAnimal();

    // 本地下载BtForm动画默认显⽰
    ui->local->showAnimal(true);

    // 添加RecBox图片以及文本
    srand(time(NULL)); // 设置随机种子，让每次推荐的页面不一样
    ui->recMusicBox->initRecBoxUi(RandPicutre(), 1); // 行1
    ui->supplyMusicBox->initRecBoxUi(RandPicutre(), 2); // 行2

    // 设置我喜欢、本地⾳乐、最近播放⻚⾯、设置commonPage的信息
    ui->likePage->setCommonPageUi("我喜欢", ":/images/ilikebg.png");
    ui->localPage->setCommonPageUi("本地音乐", ":/images/localbg.png");
    ui->recentPage->setCommonPageUi("最近播放", ":/images/recentbg.png");

    // 播放控制区
    // 创建⾳量调节窗口对象并挂到对象树
    volumeTool = new VolumeTool(this);
    ui->play->setIcon(QIcon(":/images/play_2.png"));
    ui->playMode->setToolTip("单曲循环");
    ui->playMode->setIcon(QIcon(":/images/list_play.png"));

    // 创建lrc歌词窗口
    lrcPage = new LrcPage(this);
    lrcPage->setGeometry(10, 10, lrcPage->width(), lrcPage->height());
    lrcPage->hide(); // 默认隐藏

    // lrc添加动画效果
    lrcAnimation = new QPropertyAnimation(lrcPage, "geometry", this);
    lrcAnimation->setDuration(500);
    lrcAnimation->setStartValue(QRect(10, 10 + lrcPage->height(), lrcPage->width(), lrcPage->height()));
    lrcAnimation->setEndValue(QRect(10, 10, lrcPage->width(), lrcPage->height()));
}

void miniQQMusic::initSqlite()
{
    // 1. 初始化数据库
    sqlite = QSqlDatabase::addDatabase("QSQLITE");

    // 2. 设置数据库名称
    sqlite.setDatabaseName("miniQQMusic.db");

    // 3. 打开数据库
    if(!sqlite.open())
    {
        QMessageBox::critical(this, "打开QQMusicDB失败", sqlite.lastError().text());
        return;
    }

    qDebug()<<"SQLite连接成功，并创建 [myQQMusic.db] 数据库!!!";
    // 4. 创建数据库表
    QString sql = ("CREATE TABLE IF NOT EXISTS musicInfo(\
                    id INTEGER PRIMARY KEY AUTOINCREMENT,\
                    musicId varchar(200) UNIQUE,\
                    musicName varchar(50),\
                    musicSinger varchar(50),\
                    albumName varchar(50),\
                    duration BIGINT,\
                    musicUrl varchar(256),\
                    isLike INTEGER,\
                    isHistory INTEGER)");
    QSqlQuery query;
    if(!query.exec(sql))
    {
        QMessageBox::critical(this, "插入QQMusicDB失败", sqlite.lastError().text());
        return;
    }
    qDebug() << "创建 [musicInfo] 表成功!!!";

}

void miniQQMusic::initMusicList()
{
    // 1. 从数据库中读
    musiclist.readFromDB();
    // 2. 更新commpage页面
    ui->likePage->setMusicListType(PageType::LIKE_PAGE);
    ui->likePage->reFresh(musiclist);
    ui->localPage->setMusicListType(PageType::LOCAL_PAGE);
    ui->localPage->reFresh(musiclist);
    ui->recentPage->setMusicListType(PageType::HISTORY_PAGE);
    ui->recentPage->reFresh(musiclist);
}

void miniQQMusic::initPlayer()
{
    // 初始化播放器
    player = new QMediaPlayer(this);
    // 初始化播放列表
    playList = new QMediaPlaylist(this);

    // 设置播放模式：默认为列表中⽂件循环播放
    playList->setPlaybackMode(QMediaPlaylist::Loop);

    // 讲播放列表设置到播放器
    player->setPlaylist(playList);

    // 默认音量大小
    player->setVolume(20);


    // 在播放和暂停中切换
    connect(player, &QMediaPlayer::stateChanged, this, &miniQQMusic::onPlayStateChanged);
    // 设置播放器模式
    connect(ui->playMode, &QPushButton::clicked, this, &miniQQMusic::onPlaybackModeClicked);
    // 设置点击播放器模式后图片切换
    connect(playList, &QMediaPlaylist::playbackModeChanged, this, &miniQQMusic::onPlaybackModeChanged);
    // 播放列表项发⽣改变，此时将播放⾳乐收藏到历史记录中
    connect(playList, &QMediaPlaylist::currentIndexChanged, this, &miniQQMusic::onCurrentIndexChanged);
    // 媒体总时长更新
    connect(player, &QMediaPlayer::durationChanged, this, &miniQQMusic::onDurationChanged);
    // 媒体持续时⻓更新
    connect(player, &QMediaPlayer::positionChanged, this, &miniQQMusic::onPositionChanged);
    // 媒体数据发生变化
    connect(player, &QMediaPlayer::metaDataAvailableChanged, this, &miniQQMusic::onMetaDataAvailableChanged);

    // 媒体播放器错误处理
    connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            this, &miniQQMusic::onPlayerError);
}

void miniQQMusic::setBtForm_IconTextPageId() const
{
    ui->rec->setIconTextId(":/images/rec.png", "推荐", 0);
    ui->music->setIconTextId(":/images/music.png", "音乐馆", 1);
    ui->radio->setIconTextId(":/images/radio.png", "电台", 2);
    ui->like->setIconTextId(":/images/like.png", "我喜欢", 3);
    ui->local->setIconTextId(":/images/local.png", "本地下载", 4);
    ui->recent->setIconTextId(":/images/recent.png", "最近播放", 5);
}

void miniQQMusic::connectSignalAndSlot() const
{
    // 处理btForm按钮点击的信号，切换对应的页面，同时把按钮的上一个颜色恢复到原来的颜色
    connect(ui->rec, &BtForm::click, this, &miniQQMusic::onBtFormClick);
    connect(ui->music, &BtForm::click, this, &miniQQMusic::onBtFormClick);
    connect(ui->radio, &BtForm::click, this, &miniQQMusic::onBtFormClick);
    connect(ui->like, &BtForm::click, this, &miniQQMusic::onBtFormClick);
    connect(ui->local, &BtForm::click, this, &miniQQMusic::onBtFormClick);
    connect(ui->recent, &BtForm::click, this, &miniQQMusic::onBtFormClick);

    // 关联commonpage发射的updateLikeMusic信号
    connect(ui->likePage, &CommonPage::updataLikeMusic, this, &miniQQMusic::onUpdateLikeMusic);
    connect(ui->localPage, &CommonPage::updataLikeMusic, this, &miniQQMusic::onUpdateLikeMusic);
    connect(ui->recentPage, &CommonPage::updataLikeMusic, this, &miniQQMusic::onUpdateLikeMusic);

    // 连接播放器，按下按钮进行播放
    connect(ui->play, &QPushButton::clicked, this, &miniQQMusic::onPlayClicked);
    connect(ui->playUp, &QPushButton::clicked, this, &miniQQMusic::onPlayUpCliked);
    connect(ui->playDown, &QPushButton::clicked, this, &miniQQMusic::onPlayDownCliked);

    // 关联播放所有
    connect(ui->likePage, &CommonPage::playAll, this, &miniQQMusic::onPlayAll);
    connect(ui->localPage, &CommonPage::playAll, this, &miniQQMusic::onPlayAll);
    connect(ui->recentPage, &CommonPage::playAll, this, &miniQQMusic::onPlayAll);

    // 处理likePage、localPage、recentPage中ListItemBox双击
    connect(ui->likePage, &CommonPage::playMusicByIndex, this, &miniQQMusic::playMusicByIndex);
    connect(ui->localPage, &CommonPage::playMusicByIndex, this, &miniQQMusic::playMusicByIndex);
    connect(ui->recentPage, &CommonPage::playMusicByIndex, this, &miniQQMusic::playMusicByIndex);

    // 音量是否静音
    connect(volumeTool, &VolumeTool::setSilence, this, &miniQQMusic::setMusicSilence);
    // 设置音量大小
    connect(volumeTool, &VolumeTool::setMusicVolume, this, &miniQQMusic::setPlayerVolume);
    // 设置进度条变化
    connect(ui->prosessBar, &MusicSlider::setMusicSliderPosition, this, &miniQQMusic::onMusicSliderChanged);

    // 显示歌词窗口
    connect(ui->lrcword, &QPushButton::clicked, this, &miniQQMusic::onLrcWordClicked);
}

QJsonArray miniQQMusic::RandPicutre()
{
    // 保存图片文件名
    QVector<QString> vecImageName;
    vecImageName<<"001.png"<<"003.png"<<"004.png"<<"005.png"<<"006.png"<<"007.png"
                <<"008.png"<<"009.png"<<"010.png"<<"011.png"<<"012.png"<<"013.png"<<"014.png"
                <<"015.png"<<"016.png"<<"017.png"<<"018.png"<<"019.png"<<"020.png"<<"021.png"
                <<"022.png"<<"023.png"<<"024.png"<<"025.png"<<"026.png"<<"027.png"<<"028.png"
                <<"029.png"<<"030.png"<<"031.png"<<"032.png"<<"033.png"<<"034.png"<<"035.png"
                <<"036.png"<<"037.png"<<"038.png"<<"039.png"<<"040.png";
    // 随机打散
    std::random_shuffle(vecImageName.begin(), vecImageName.end());

    // 设置图片以及名字
    QJsonArray objArray;
    for(int i = 0; i < vecImageName.size(); ++i)
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

void miniQQMusic::onUpdateLikeMusic(bool isLike, const QString &musicId)
{
    // 1. 找到这首歌曲
    auto it = musiclist.findMusicByMusicid(musicId);
    if(it != musiclist.end())
    {
        it->setIsLike(isLike);
    }
    // 2. 通知三个页面进行更新数据
    ui->likePage->reFresh(musiclist);
    ui->localPage->reFresh(musiclist);
    ui->recentPage->reFresh(musiclist);
}

void miniQQMusic::onBtFormClick(int pageid)
{
    // 清除当前页面所有btFrom按钮背景颜色
    // 1. 获取当前⻚⾯所有btFrom按钮类型的对象
    QList<BtForm*> buttonList = this->findChildren<BtForm*>();
    // 2. 遍历所有对象, 如果不是当前id的按钮,则把之前设置的背景颜⾊清除掉
    for(auto &btitem : buttonList)
    {
        if(pageid != btitem->getId())
        {
            btitem->clearBg();
        }
    }

    // 3. 显⽰⻚⾯
    ui->stackedWidget->setCurrentIndex(pageid);
    qDebug() << "切换页面到: " << pageid;
    isDrag = false;
}

void miniQQMusic::mousePressEvent(QMouseEvent *event)
{
    // 按下鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        isDrag = true;
        // 记录位置，获取⿏标相对于屏幕左上⻆的全局坐标
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        return;
    }

    return QWidget::mousePressEvent(event);
}

void miniQQMusic::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton && isDrag)
    {
        this->move(event->globalPos() - dragPosition);
        return;
    }
    return QWidget::mouseMoveEvent(event);
}

void miniQQMusic::on_quit_clicked()
{
    // 写入数据库
    musiclist.writeToDB();

    // 关闭数据库连接
    sqlite.close();

    // 隐藏窗口到托盘
    hide();
}

void miniQQMusic::on_volume_clicked()
{
    // 先要调整窗⼝的显⽰位置，否则该窗⼝在主窗⼝的左上⻆
    // 1. 获取该按钮左上⻆的图标
    QPoint point = ui->volume->mapToGlobal(QPoint(0, 0));
    // 2. 计算volume窗⼝的左上⻆位置
    // 让该窗⼝显⽰在⿏标点击的正上⽅
    // ⿏标位置：减去窗⼝宽度的⼀半，以及⾼度恰巧就是窗⼝的左上⻆
    QPoint volumeLeftTop = point - QPoint(volumeTool->width() / 2, volumeTool->height());
    // 微调窗⼝位置
    volumeLeftTop.setY(volumeLeftTop.y() + 30);
    volumeLeftTop.setX(volumeLeftTop.x() + 15);
    // 3. 移动窗⼝位置
    volumeTool->move(volumeLeftTop);
    // 4. 将窗⼝显⽰出来
    volumeTool->show();
}

void miniQQMusic::setMusicSilence(bool isMuted)
{
    player->setMuted(isMuted);
}

void miniQQMusic::on_addLocal_clicked()
{
    // 1. 创建一个文件对话框
    QFileDialog fileDialog(this);
    fileDialog.setWindowTitle("添加本地音乐");

    // 2. 创建一个打开格式的文件对话框
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);

    // 3. 设置对话框模式
    // 能选择文件，并且一次性可以选择多个存在的文件
    fileDialog.setFileMode(QFileDialog::ExistingFiles);

    // 4. 设置对话框的MIME过滤器
    QStringList mimeList;
    mimeList << "application/octet-stream"; // 表⽰通⽤的⼆进制数据流的MIME类型
    fileDialog.setMimeTypeFilters(mimeList);

    // 5. 设置对话框默认的打开路径，设置目录当前工程所在目录
    QDir dir(QDir::currentPath());
    dir.cdUp();
    QString musicPath = dir.path() + "/myQQMusic/musics/";
    fileDialog.setDirectory(musicPath); // 设置路径

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

        // 将歌曲信息更新到commonpage页面中的listwidget中(本地页面)
        ui->localPage->reFresh(musiclist);

        // 将localPage页面的歌曲添加到音乐播放器列表中
        ui->localPage->addMusictoPlayer(musiclist, playList);
    }
}

///////////////////////////////////////////////////////
void miniQQMusic::onPlayClicked()
{
    if(player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
    }
    else if(player->state() == QMediaPlayer::PausedState)
    {
        player->play();
    }
    else if(player->state() == QMediaPlayer::StoppedState)
    {
        playAllOfCommonPage(ui->localPage, 0);
    }
    else
    {
        QMessageBox::critical(nullptr, "播放错误", "播放错误");
        qDebug() << "onPlayClicked failed!";
    }
}

void miniQQMusic::onPlayStateChanged()
{
    if(player->state() == QMediaPlayer::PlayingState)
    {
        // 播放
        ui->play->setIcon(QIcon(":/images/play_on.png"));
    }
    else
    {
        // 暂停
        ui->play->setIcon(QIcon(":/images/play3.png"));
    }
}

void miniQQMusic::onPlayUpCliked()
{
    playList->previous();
}

void miniQQMusic::onPlayDownCliked()
{
    playList->next();
}

void miniQQMusic::onPlaybackModeClicked()
{

    if(playList->playbackMode() == QMediaPlaylist::Loop)
    {
        ui->playMode->setToolTip("随机播放");
        playList->setPlaybackMode(QMediaPlaylist::Random);
    }
    else if(playList->playbackMode() == QMediaPlaylist::Random)
    {
        ui->playMode->setToolTip("单曲循环");
        playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else if(playList->playbackMode() == QMediaPlaylist::CurrentItemInLoop)
    {
        ui->playMode->setToolTip("列表循环");
        playList->setPlaybackMode(QMediaPlaylist::Loop);
    }
    else
    {
        qDebug() << "点击出现错误! ";
        return ;
    }
}

void miniQQMusic::onPlaybackModeChanged(QMediaPlaylist::PlaybackMode playbackMode)
{
    if(playbackMode == QMediaPlaylist::Loop)
    {
        ui->playMode->setIcon(QIcon(":/images/list_play.png"));
    }
    else if(playbackMode == QMediaPlaylist::Random)
    {
        ui->playMode->setIcon(QIcon(":/images/shuffle_2.png"));
    }
    else if(playbackMode == QMediaPlaylist::CurrentItemInLoop)
    {
        ui->playMode->setIcon(QIcon(":/images/single_play.png"));
    }
    else
    {
        qDebug() << "图片出现错误! ";
        return ;
    }
}

void miniQQMusic::onPlayAll(PageType pagetype)
{
    CommonPage* page = nullptr;
    switch(pagetype)
    {
    case PageType::LIKE_PAGE:
        page = ui->likePage;
        break;
    case PageType::LOCAL_PAGE:
        page = ui->localPage;
        break;
    case PageType::HISTORY_PAGE:
        page = ui->recentPage;
        break;
    default:
        break;
    }
    // 从0开始播放
    playAllOfCommonPage(page, 0);
}

void miniQQMusic::onCurrentIndexChanged(int index)
{
    // 当前下标
    currentIndex = index;
    // 音乐的id在commonPage中的musicListOfPage存放
    const QString& musicId = curPage->getMisicIdByIndex(index);
    auto it = musiclist.findMusicByMusicid(musicId);
    if(it != musiclist.end())
    {
        it->setIsHistory(true);
    }
    ui->recentPage->reFresh(musiclist);
}

void miniQQMusic::setPlayerVolume(int volume)
{
    player->setVolume(volume);
}

void miniQQMusic::onDurationChanged(qint64 duration)
{
    totalDuration = duration;
    ui->totalTime->setText(QString("%1:%2").arg(duration / 1000 / 60, 2, 10, QChar('0'))
                           .arg(duration/1000 % 60, 2, 10, QChar('0')));
}

void miniQQMusic::onPositionChanged(qint64 duration)
{
    // 1. 更新当前时间
    ui->currentTime->setText(QString("%1:%2").arg(duration/1000/60, 2, 10, QChar('0'))
                             .arg(duration/1000%60, 2, 10, QChar('0')));
    // 2. 进度条也要发送改变
    ui->prosessBar->setStep((float)duration / totalDuration);

    // 3. 同步歌词
    if(playList->currentIndex() >= 0)
    {
        lrcPage->showLrcWord(duration);
    }
}

void miniQQMusic::onMusicSliderChanged(float value)
{
    // 1. 计算seek位置的时长
    qint64 duration = (qint64)(totalDuration * value);

    // 2. 转换
    ui->currentTime->setText(QString("%1:%2").arg(duration/1000/60, 2, 10, QChar('0'))
                           .arg(duration/1000%60, 2, 10, QChar('0')));
    // 3. 设置当前位置
    player->setPosition(duration);
}

void miniQQMusic::onMetaDataAvailableChanged(bool available)
{
    Q_UNUSED(available);

    // 1. 从player播放歌曲的元数据中获取歌曲信息
    QString musicId = curPage->getMisicIdByIndex(currentIndex);
    auto it = musiclist.findMusicByMusicid(musicId);
    QString musicName("未知歌曲");
    QString musicSinger("歌手位置");
    if(it != musiclist.end())
    {
        musicName = it->getMusicName();
        musicSinger = it->getSingerName();
    }
    ui->musicName->setText(musicName);
    ui->musicSinger->setText(musicSinger);

    // 获取封面图，通过元数据来获取
    QVariant coverimage = player->metaData("ThumbnailImage");
    if(coverimage.isValid())
    {
        const QImage image = coverimage.value<QImage>();
        ui->musicCover->setPixmap(QPixmap::fromImage(image));
        curPage->setMusicImage(QPixmap::fromImage(image));
    }
    else
    {
        QString path = ":/images/rec/001.png";
        ui->musicCover->setPixmap(path);
        curPage->setMusicImage(path);
    }

    // 加载lrc歌词
    if(it != musiclist.end())
    {
        lrcPage->parseLrc(it->getLrcFilePath());
    }
}

void miniQQMusic::onLrcWordClicked()
{
    lrcPage->show();
    lrcAnimation->start();
}

void miniQQMusic::playMusicByIndex(CommonPage *page, int index)
{
    playAllOfCommonPage(page, index);
}

void miniQQMusic::playAllOfCommonPage(CommonPage *page, int index)
{
    // 当前页面
    curPage = page;
    updateBtformAnimal();

    // 先清空播放列表
    playList->clear();
    // 再添加当前页面到播放列表
    page->addMusictoPlayer(musiclist, playList);

    // 检查播放列表是否为空
    if (playList->isEmpty()) {
        QMessageBox::warning(nullptr, "播放列表为空", "设置为0");
        return;
    }

    // 检查索引是否有效
    if (index < 0 || index >= playList->mediaCount()) {
        qDebug() << "索引无效，设置为0";
        index = 0;
    }

    // 设置当前播放列表索引
    playList->setCurrentIndex(index);

    // 检查播放器状态并播放
    if (player->state() == QMediaPlayer::StoppedState || player->state() == QMediaPlayer::PausedState) {
        player->play();
        // 检查是否有错误发生
        if (player->error() != QMediaPlayer::NoError) {
            qDebug() << "播放失败，可能是媒体文件无法访问";
            qDebug() << "错误信息: " << player->errorString();
        } else {
            qDebug() << "开始播放音乐，索引: " << index;
        }
    }
}

void miniQQMusic::updateBtformAnimal()
{
    // 获取currentPage在stackedWidget中的索引
    int index = ui->stackedWidget->indexOf(curPage);
    if(-1 == index)
    {
        qDebug() << "页面不存在";
        return;
    }

    // 获取界⾯上所有的btForm
    QList<BtForm*> btForms = this->findChildren<BtForm*>();
    for(auto& btform : btForms)
    {
        if(btform->getId() == index)
        {
            btform->showAnimal(true);
        }
        else
        {
            btform->showAnimal(false);
        }
    }
}

void miniQQMusic::quitQQMusic()
{
    this->close();
}

void miniQQMusic::on_skin_clicked()
{
    QMessageBox::information(this, "温馨提⽰", "还没开发呢！！！");
}

void miniQQMusic::on_min_clicked()
{
    showMinimized();
}

void miniQQMusic::on_max_clicked()
{
    // 临时移除阴影效果
    this->setGraphicsEffect(nullptr);
    showMaximized();

    // 重新添加阴影效果
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor("#000000");
    shadowEffect->setBlurRadius(5);
    ui->background->setGraphicsEffect(shadowEffect);
}

void miniQQMusic::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // 确保阴影效果正确应用
    if(this->graphicsEffect())
    {
        this->graphicsEffect()->update();
    }
}

void miniQQMusic::onPlayerError(QMediaPlayer::Error error)
{
    Q_UNUSED(error);
    // 获取错误信息
    QString errorString = player->errorString();

    // 特定处理0x80040266错误（DirectShow格式不支持）
    if (errorString.contains("0x80040266"))
    {
        qDebug() << "检测到DirectShow格式不支持错误: 0x80040266";
        QMessageBox::warning(this, "播放错误", "无法播放当前媒体文件，格式可能不受支持。\n错误码: 0x80040266");

        // 尝试跳转到下一首
        if (playList->mediaCount() > playList->currentIndex() + 1)
        {
            playList->next();
            player->play();
        }
        else
        {
            player->stop();
        }
    }
    else
    {
        // 其他错误处理
        QMessageBox::warning(this, "播放错误", "播放媒体时发生其他错误: " + errorString);
    }
}
