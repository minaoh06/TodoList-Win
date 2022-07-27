#ifndef TODOLIST_H
#define TODOLIST_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMenuBar>
#include <QInputDialog>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QApplication>

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
    void reloadListPrincipale();
    void reloadListSecondaire();

public slots:
    // Structures de données
    void ajoutItemListPrincipale();
    void ajoutItemListSecondaire();

    void suppressionItemsListPrincipale();
    void suppressionItemsListSecondaire();


    // XML code example : https://gist.github.com/lamprosg/2133804
    void enregistrement();
    //void importation();


private:
    Ui::TodoList *ui;

    QList<QListWidgetItem> listPrincipal;
    QList<QListWidgetItem> listSecondaire;
};
#endif // TODOLIST_H
