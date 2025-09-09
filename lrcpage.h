#ifndef LRCPAGE_H
#define LRCPAGE_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QVector>

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

    bool parseLrc(const QString& lrcPath);
    int getLineLrcWordIndex(qint64 pos);
    QString getLrcWordByIndex(qint64 index);
    void showLrcWord(int time);

private:
    Ui::LrcPage *ui;
    QPropertyAnimation* Animation;
    QVector<LrcWordLine> lrcLines;
};

#endif // LRCPAGE_H
