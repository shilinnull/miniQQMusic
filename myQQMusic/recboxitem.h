#ifndef RECBOXITEM_H
#define RECBOXITEM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QDebug>

namespace Ui {
class RecBoxItem;
}

class RecBoxItem : public QWidget
{
    Q_OBJECT

public:
    explicit RecBoxItem(QWidget *parent = nullptr);
    ~RecBoxItem();

    bool eventFilter(QObject *watched, QEvent *event) override;

    // 设置文本
    void setText(const QString& text);

    // 设置图片
    void setImage(const QString& imagePath);

private:
    Ui::RecBoxItem *ui;
    QPropertyAnimation* animation;
};

#endif // RECBOXITEM_H
