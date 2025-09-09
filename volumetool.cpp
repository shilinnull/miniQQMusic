#include "volumetool.h"
#include "ui_volumetool.h"

VolumeTool::VolumeTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeTool),
    isMuted(false),
    volumeRatio(20)
{
    ui->setupUi(this);

    // 设置点击其外部区域时，它会自动关闭, 移除窗口的边框和标题栏, 禁止窗口显示阴影效果
    // 要注意是使用setWindowFlags
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    // 设置让窗口的背景变为透明状态
    setAttribute(Qt::WA_TranslucentBackground);

    // ⾃定义阴影效果
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor("#646464");
    shadowEffect->setBlurRadius(10);
    ui->volumeWidget->setGraphicsEffect(shadowEffect);

    // 给按钮设置图标
    ui->silenceBtn->setIcon(QIcon(":/images/volumn.png"));
    // ⾳量的默认⼤⼩是20
    ui->outSlider->setGeometry(ui->outSlider->x(), 180 - 38 + 28, ui->outSlider->width(), 40);
    ui->sliderBtn->move(ui->sliderBtn->x(), ui->outSlider->y() - ui->sliderBtn->height() / 2);
    ui->volumeRatio->setText("20%");

    // 设置静音
    connect(ui->silenceBtn, &QPushButton::clicked, this, &VolumeTool::onSilenceBtnClicked);

    // 安装过滤器，过滤鼠标按下，抬起，移动
    ui->volumeWidget->installEventFilter(this);
}

VolumeTool::~VolumeTool()
{
    delete ui;
}

void VolumeTool::onSilenceBtnClicked()
{
    isMuted = !isMuted;
    if(isMuted)
    {
        ui->silenceBtn->setIcon(QIcon(":/images/silent.png"));
    }
    else
    {
        ui->silenceBtn->setIcon(QIcon(":/images/volumn.png"));
    }
    // 发送信号让myqqmusic进行处理调整音量是否静音
    emit setSilence(isMuted);
}

void VolumeTool::setVolume()
{
    // 1. 将⿏标的位置转换为sloderBox上的相对坐标，此处只要获取y坐标
    int height = ui->volumeWidget->mapFromGlobal(QCursor().pos()).y();
    // 2. ⿏标在volumeBox中可移动的y范围在[25, 205之间]
    height = height < 25 ? 25 : height;
    height = height > 205 ? 205 : height;
    // 3. 调整sloderBt的位置
    ui->sliderBtn->move(ui->sliderBtn->x(), height - ui->sliderBtn->height() / 2);
    // 4. 更新outline的位置和⼤⼩
    ui->outSlider->setGeometry(ui->outSlider->x(), height, ui->outSlider->width(), 25 + 180 - height);
    // 5. 计算⾳量⽐率
    volumeRatio = (int)((int)ui->outSlider->height() / (float)180 * 100);
    // 6. 设置显示文本
    ui->volumeRatio->setText(QString::number(volumeRatio) + "%");
}

void VolumeTool::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    // 创建绘图对象
    QPainter painter(this);

    // 设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 设置画笔
    // 没有画笔时：画出来的图形就没有边框和轮廓线
    painter.setPen(Qt::NoPen);

    // 设置画刷
    painter.setBrush(Qt::white);

    // 创建一个三角形
    QPolygon polygon;
    polygon.append(QPoint(30, 300));
    polygon.append(QPoint(70, 300));
    polygon.append(QPoint(50, 320));

    // 绘制三角形
    painter.drawPolygon(polygon);
}

bool VolumeTool::eventFilter(QObject *object, QEvent *event)
{
    // 过滤volumeBox上的事件
    if(object == ui->volumeWidget)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            // 修改sliderBtn和outLine的位置
            setVolume();
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            emit setMusicVolume(volumeRatio);
        }
        else if(event->type() == QEvent::MouseMove)
        {
            // 修改sliderBtn和outLine的位置
            setVolume();
            // 发送信号让myqqmusic修改音量大小
            emit setMusicVolume(volumeRatio);
        }
        else
        {
            return false;
        }
        return true;
    }

    return QObject::eventFilter(object, event);
}
