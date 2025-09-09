#ifndef RECBOX_H
#define RECBOX_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>

#include "recboxitem.h"

namespace Ui {
class RecBox;
}

class RecBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecBox(QWidget *parent = nullptr);
    ~RecBox();

    void initRecBoxUi(QJsonArray data, int row);

private slots:
    void on_btDown_clicked();
    void on_btUp_clicked();

private:
    void createRecItem();

private:
    Ui::RecBox *ui;
    int row;
    int col;
    QJsonArray imageList;
    int currentIndex;
    int count;
};

#endif // RECBOX_H
