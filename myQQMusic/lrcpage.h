#ifndef LRCPAGE_H
#define LRCPAGE_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class LrcPage;
}

struct LrcWordLine
{
    qint64 time;
    QString text;
    LrcWordLine(qint64 qtime, QString qtext)
        :time(qtime)
        ,text(qtext)
    {}
};

class LrcPage : public QWidget
{
    Q_OBJECT

public:
    explicit LrcPage(QWidget *parent = nullptr);
    ~LrcPage();

    // 解析歌词数据
    bool parseLrc(const QString& lrcPath);
    // 获取歌词
    int getLineLrcWordIndex(qint64 pos);
    // 获取歌词行
    QString getLrcWordByIndex(qint64 index);
    // 显示歌词
    void showLrcWord(int time);

private:
    Ui::LrcPage *ui;

    // 动画
    QPropertyAnimation* Animation;

    // 管理每行的音乐
    QVector<LrcWordLine> lrcLines;
};

#endif // LRCPAGE_H
