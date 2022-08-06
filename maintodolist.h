#ifndef MAINTODOLIST_H
#define MAINTODOLIST_H

#include "todolist.h"
#include <QMainWindow>

namespace Ui {
class MainTodoList;
}

class MainTodoList : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainTodoList(QWidget *parent = nullptr);
    ~MainTodoList();
    void setEvent();

private:
    Ui::MainTodoList *ui;
    TodoList *todo;
};

#endif // MAINTODOLIST_H
