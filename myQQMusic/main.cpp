#include "myqqmusic.h"

#include <QApplication>
#include <QMessageBox>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建共享内存
    QSharedMemory sharedMem("QQMusic");

    // 如果共享内存已经被占⽤，说明已经有实例在运⾏
    if(sharedMem.attach())
    {
        QMessageBox::information(nullptr, "QQMusic", "QQMusic已经在运⾏...");
        return 0;
    }
    sharedMem.create(1);

    myQQMusic w;
    w.show();
    return a.exec();
}
