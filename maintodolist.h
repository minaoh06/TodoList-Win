#ifndef MAINTODOLIST_H
#define MAINTODOLIST_H

#include <QMainWindow>
#include <QDir>
#include <QInputDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QListWidgetItem>

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

public slots:
    void ajoutItemListPrincipale();
    void suppressionItemsListPrincipale();

    void enregistrement();
    void importation();

private:
    Ui::MainTodoList *ui;
    QDir dir;
};

#endif // MAINTODOLIST_H
