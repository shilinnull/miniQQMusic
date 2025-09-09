#ifndef BTFORM_H
#define BTFORM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QMouseEvent>

namespace Ui {
class BtForm;
}

class BtForm : public QWidget
{
    Q_OBJECT

public:
    explicit BtForm(QWidget *parent = nullptr);
    ~BtForm();
    void setIconTextId(const QString& btIcon, const QString& text, int pageid);
    int getId();
    void clearBg();
    void setline1Animal();
    void showAnimal(bool isShow);
signals:
    void click(int id);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::BtForm *ui;
    int pageId = 0;
    QPropertyAnimation *animationLine1;
    QPropertyAnimation *animationLine2;
    QPropertyAnimation *animationLine3;
    QPropertyAnimation *animationLine4;
};

#endif // BTFORM_H
