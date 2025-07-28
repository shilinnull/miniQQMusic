#ifndef RECBOXITEM_H
#define RECBOXITEM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QDebug>

namespace Ui {
class RecBoxItem;
}

/**
 * @brief The RecBoxItem class
 * 推荐项组件，用于在推荐框中显示单个推荐内容
 * 支持鼠标悬停动画效果，显示文本和图片信息
 */
class RecBoxItem : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief RecBoxItem 构造函数
     * 初始化推荐项组件，安装事件过滤器
     * @param parent 父窗口指针
     */
    explicit RecBoxItem(QWidget *parent = nullptr);

    /**
     * @brief ~RecBoxItem 析构函数
     * 释放UI资源
     */
    ~RecBoxItem();

    /**
     * @brief eventFilter 事件过滤器
     * 拦截鼠标进入和离开事件，实现悬停动画效果
     * @param watched 被监视的对象
     * @param event 事件对象
     * @return 如果事件被处理则返回true，否则返回false
     */
    bool eventFilter(QObject *watched, QEvent *event) override;

    /**
     * @brief setText 设置推荐项文本
     * @param text 要显示的文本内容
     */
    void setText(const QString& text);

    /**
     * @brief setImage 设置推荐项图片
     * @param imagePath 图片资源路径
     */
    void setImage(const QString& imagePath);

private:
    Ui::RecBoxItem *ui; ///< UI界面指针
};

#endif // RECBOXITEM_H
