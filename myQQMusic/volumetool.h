#ifndef VOLUMETOOL_H
#define VOLUMETOOL_H

#include <QWidget>
#include <QPainter>


namespace Ui {
class VolumeTool;
}

class VolumeTool : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeTool(QWidget *parent = nullptr);
    ~VolumeTool();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::VolumeTool *ui;
};

#endif // VOLUMETOOL_H
