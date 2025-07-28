#ifndef RECBOX_H
#define RECBOX_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui {
class RecBox;
}

/**
 * @brief The RecBox class
 * 推荐内容展示框组件，用于显示推荐音乐或专辑内容
 * 支持横向滚动切换不同组内容，可配置单行或双行布局
 */
class RecBox : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief RecBox 构造函数
     * @param parent 父窗口指针
     */
    explicit RecBox(QWidget *parent = nullptr);

    /**
     * @brief ~RecBox 析构函数
     * 释放UI资源
     */
    ~RecBox();

    /**
     * @brief initRecBoxUi 初始化推荐框UI
     * 根据数据和行数配置推荐框布局和内容
     * @param data 包含推荐项信息的JSON数组
     * @param row 显示行数（1或2）
     */
    void initRecBoxUi(QJsonArray data, int row);

private slots:
    /**
     * @brief on_btDown_clicked 向下翻页按钮点击事件
     * 切换到下一组推荐内容
     */
    void on_btDown_clicked();

    /**
     * @brief on_btUp_clicked 向上翻页按钮点击事件
     * 切换到上一组推荐内容
     */
    void on_btUp_clicked();

private:
    /**
     * @brief createRecItem 创建推荐项
     * 根据当前索引创建并添加推荐项到布局中
     * 自动清理旧的推荐项
     */
    void createRecItem();

private:
    Ui::RecBox *ui;               ///< UI界面指针
    int row;                      ///< 显示行数
    int col;                      ///< 每行显示列数
    QJsonArray imageList;         ///< 存储推荐项数据
    int currentIndex;             ///< 当前显示组索引
    int count;                    ///< 总组数
};

#endif // RECBOX_H
