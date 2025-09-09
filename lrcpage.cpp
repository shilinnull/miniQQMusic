#include "lrcpage.h"
#include "ui_lrcpage.h"

LrcPage::LrcPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LrcPage)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);

    ui->hideBtn->setIcon(QIcon(":/images/xiala.png"));

    // 设置动画
    Animation = new QPropertyAnimation(this, "geometry", this);
    Animation->setDuration(500);
    Animation->setStartValue(QRect(10, 10, width(), height()));
    Animation->setEndValue(QRect(10, 10 + height(), width(), height()));

    // 点击下拉按钮开启动画
    connect(ui->hideBtn, &QPushButton::clicked, this, [=](){

       Animation->start();
    });

    // 动画结束的时候，窗口隐藏
    connect(Animation, &QPropertyAnimation::finished, this, [=](){
        hide();
    });
}

LrcPage::~LrcPage()
{
    delete ui;
}

bool LrcPage::parseLrc(const QString &lrcPath)
{
    // 1. 打开文件
    QFile file(lrcPath);
    if(!file.open(QIODevice::ReadOnly))
    {

        return false;
    }

    // 将上一首歌的lrc歌词清空
    lrcLines.clear();

    // 一次性读取一行lrc歌词
    while(!file.atEnd())
    {
        QString lrclineWord =  file.readLine(1024);

        // 解析歌词
        // [0:17.94]那些失眠的人啊 你现在还好吗
        // [0:33.600.00]比2002年来的更晚一些
        // 1. 先解析出时间和 歌词的字符串文本--->按照]分割
        int start = 0, end = 0;
        end = lrclineWord.indexOf(']', start);
        QString lrcTime = lrclineWord.mid(start, end-start+1);
        QString lrcWord = lrclineWord.mid(end + 1, lrclineWord.size() - end - 1 - 1 - 1);

        // 2. 在时间中解析出分:秒.毫秒
        // [0:17.94]  [0:33.600.00]
        // 解析分
        qint64 lineTime = 0;
        start = 1;
        end = lrcTime.indexOf(':', start);
        lineTime += lrcTime.mid(start, end - start).toInt()*60*1000;  // 解析分并将其转化为毫秒

        // 解析秒
        start = end+1;
        end = lrcTime.indexOf('.', start);
        lineTime += lrcTime.mid(start, end - start).toInt()*1000;    // 解析秒并将其转换为毫秒

        // 解析毫秒
        start = end+1;
        end = lrcTime.indexOf('.', start);
        lineTime += lrcTime.mid(start, end - start).toInt();   // 解析毫秒

        // 3. 将该行给次保存
        lrcLines.push_back(LrcWordLine(lineTime, lrcWord));
    }
    return true;
}

int LrcPage::getLineLrcWordIndex(qint64 pos)
{
    // 将time和QVector中保存的LrcWordLine中的time进行对比
    // 当前歌曲没有lrc歌词文件
    if(lrcLines.empty())
        return -1;

    if(lrcLines[0].time >= pos)
        return 0;

    for (int i = 1; i < lrcLines.size(); i++)
    {
        // 需要比较
        if(pos >= lrcLines[i - 1].time && pos < lrcLines[i].time)
            return i - 1;
    }
    return lrcLines.size() - 1;
}

QString LrcPage::getLrcWordByIndex(qint64 index)
{
    if(index < 0 || index >= lrcLines.size())
    {
        return "";
    }
    return lrcLines[index].text;
}

void LrcPage::showLrcWord(int time)
{
    int index = getLineLrcWordIndex(time);
    if(-1 == index)
    {
        ui->line1->setText("");
        ui->line2->setText("");
        ui->line3->setText("");
        ui->lineCenter->setText("当前歌曲暂无歌词");
        ui->line4->setText("");
        ui->line5->setText("");
        ui->line6->setText("");
    }
    else
    {
        ui->line1->setText(getLrcWordByIndex(index-3));
        ui->line2->setText(getLrcWordByIndex(index-2));
        ui->line3->setText(getLrcWordByIndex(index-1));
        ui->lineCenter->setText(getLrcWordByIndex(index));
        ui->line4->setText(getLrcWordByIndex(index+1));
        ui->line5->setText(getLrcWordByIndex(index+2));
        ui->line6->setText(getLrcWordByIndex(index+3));
    }
}
