#ifndef MYQQMUSIC_H
#define MYQQMUSIC_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class myQQMusic; }
QT_END_NAMESPACE

class myQQMusic : public QWidget
{
    Q_OBJECT

public:
    myQQMusic(QWidget *parent = nullptr);
    ~myQQMusic();
    // 初始化UI
    void InitUi();

    // 初始化bodyLeft中6个btForm的信息
    void setBtForm_IconTextPageId() const ;

    // btForm点击槽函数
    void onBtFormClick(int pageid) const;

    void connectSignalAndSlot() const;

protected:
    // 重写QWidget类的⿏标单击和⿏标滚轮事件
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void on_quit_clicked();

private:
    Ui::myQQMusic *ui;

    // 记录光标相对于窗口标题栏的相对距离
    QPoint dragPosition;
};
#endif // MYQQMUSIC_H
