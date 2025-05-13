#ifndef RECBOX_H
#define RECBOX_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui {
class RecBox;
}

class RecBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecBox(QWidget *parent = nullptr);
    ~RecBox();

public:
    // 初始化
    void initRecBoxUi(QJsonArray data, int row);

private slots:
    void on_btDown_clicked();

    void on_btUp_clicked();

private:
    // 添加图片
    void createRecItem();
private:
    int row;
    int col;
    QJsonArray imageList;

    int currentIndex; // 标记当前显示第几组
    int count;        // 记录总的信息组数

private:
    Ui::RecBox *ui;
};

#endif // RECBOX_H
