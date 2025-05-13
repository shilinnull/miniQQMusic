#ifndef BTFORM_H
#define BTFORM_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class BtForm;
}

class BtForm : public QWidget
{
    Q_OBJECT

public:
    explicit BtForm(QWidget *parent = nullptr);
    ~BtForm();

    // 设置图标 文字 id
    void setIconTextId(const QString& btIcon, const QString& text, int pageid);
    // 获取id
    int getId();
    // 清除背景颜色
    void clearBg();

    // 设置linebox动画起伏效果
    QPropertyAnimation *animationLine1;
    QPropertyAnimation *animationLine2;
    QPropertyAnimation *animationLine3;
    QPropertyAnimation *animationLine4;
    void setline1Animal();

    // 显示动画
    void showAnimal();

signals:
    void click(int id);
protected:
    // 重写鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::BtForm *ui;
    int pageId = 0;
};

#endif // BTFORM_H
