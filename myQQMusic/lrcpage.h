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

/**
 * @brief 歌词单行数据结构
 * 存储单句歌词的时间戳和文本内容
 */
struct LrcWordLine
{
    qint64 time;   //!< 时间戳(毫秒)
    QString text;  //!< 歌词文本
    LrcWordLine(qint64 qtime, QString qtext)
        :time(qtime)
        ,text(qtext)
    {}
};

/**
 * @brief 歌词显示页面类
 * 负责歌词解析、显示和动画效果控制
 */
class LrcPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit LrcPage(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~LrcPage();

    /**
     * @brief 解析歌词数据
     * @param lrcPath 歌词文件路径
     * @return 解析成功返回true，否则返回false
     */
    bool parseLrc(const QString& lrcPath);
    
    /**
     * @brief 获取指定时间对应的歌词行索引
     * @param pos 当前播放位置(毫秒)
     * @return 歌词行索引
     */
    int getLineLrcWordIndex(qint64 pos);
    
    /**
     * @brief 通过索引获取歌词文本
     * @param index 歌词行索引
     * @return 歌词文本
     */
    QString getLrcWordByIndex(qint64 index);
    
    /**
     * @brief 根据时间显示对应的歌词
     * @param time 当前播放时间(毫秒)
     */
    void showLrcWord(int time);

private:
    Ui::LrcPage *ui;               //!< UI对象指针
    QPropertyAnimation* Animation; //!< 动画对象
    QVector<LrcWordLine> lrcLines; //!< 歌词行数据
};

#endif // LRCPAGE_H
