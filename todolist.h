#ifndef TODOLIST_H
#define TODOLIST_H

#include <QWidget>
#include <QApplication>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class TodoList; }
QT_END_NAMESPACE

class TodoList : public QWidget
{
    Q_OBJECT

public:
    // Construsteur et destructeur
    TodoList(QWidget *parent = nullptr);
    ~TodoList();

    // Fenetre
    void setEvent();

public slots:
    // Structures de données
    void ajoutItemListPrincipale();
    void ajoutItemListSecondaire();

    void suppressionItemsListPrincipale();
    void suppressionItemsListSecondaire();


    // XML code example
    void enregistrement();
    void importation();


private:
    Ui::TodoList *ui;
    QDir dir;
};
#endif // TODOLIST_H
