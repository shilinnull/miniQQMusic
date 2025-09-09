#ifndef LISTITEMBOX_H
#define LISTITEMBOX_H

#include <QWidget>

namespace Ui {
class ListItemBox;
}

class ListItemBox : public QWidget
{
    Q_OBJECT

public:
    explicit ListItemBox(QWidget *parent = nullptr);

    ~ListItemBox();
    void setMusicName(const QString& name);
    void setSingerName(const QString& singer);
    void setAlbumName(const QString& albumName);
    void setLikeIcon(bool like);

private slots:
    void onLikeBtnClicked();

signals:
    void setIsLike(bool isLike);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    Ui::ListItemBox *ui;
    bool isLike;
};

#endif // LISTITEMBOX_H
