#include "todolist.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TodoList w;
    w.setFixedSize(711,546);
    w.show();
    return a.exec();
}
