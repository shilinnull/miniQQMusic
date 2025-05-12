#include "recbox.h"
#include "ui_recbox.h"

#include "recboxitem.h"


RecBox::RecBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBox)
{
    ui->setupUi(this);
    RecBoxItem* item = new RecBoxItem();
    RecBoxItem* item2 = new RecBoxItem();
    ui->recListUpHLayout->addWidget(item);
    ui->recListDownHLayout->addWidget(item2);

}

RecBox::~RecBox()
{
    delete ui;
}
