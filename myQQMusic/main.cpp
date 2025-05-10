#include "myqqmusic.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myQQMusic w;
    w.show();
    return a.exec();
}
