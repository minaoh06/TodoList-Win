#include "maintodolist.h"
#include "ui_maintodolist.h"

MainTodoList::MainTodoList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainTodoList)
{
    ui->setupUi(this);
    todo = new TodoList(ui->centralwidget);
    setEvent();

}

MainTodoList::~MainTodoList()
{
    delete ui;
}

void MainTodoList::setEvent() {
    QObject::connect(ui->actionEnregistrer, &QAction::triggered, todo, &TodoList::enregistrement);
    QObject::connect(ui->actionFermer, &QAction::triggered, this, &QApplication::quit);
    QObject::connect(ui->actionOpen, &QAction::triggered, todo, &TodoList::importation);
}
