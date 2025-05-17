#include "volumetool.h"
#include "ui_volumetool.h"

#include <QGraphicsDropShadowEffect>

VolumeTool::VolumeTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeTool)
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
    setGraphicsEffect(shadowEffect);

    // 给按钮设置图标
    ui->silenceBtn->setIcon(QIcon(":/images/volumn.png"));
    // ⾳量的默认⼤⼩是20
    ui->outSlider->setGeometry(ui->outSlider->x(), 180 - 38 + 28, ui->outSlider->width(), 40);
    ui->sliderBtn->move(ui->sliderBtn->x(), ui->outSlider->y() - ui->sliderBtn->height() / 2);
    ui->volumeRatio->setText("20%");

}

VolumeTool::~VolumeTool()
{
    delete ui;
}

void VolumeTool::paintEvent(QPaintEvent *event)
{
    (void)event;
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
