#include "todolist.h"
#include "ui_todolist.h"

TodoList::TodoList(QWidget *parent) : QWidget(parent), ui(new Ui::TodoList)
{
    //Constructiuon de la fenetre avec tout les widgets a l'intérieur
    ui->setupUi(this);

    TodoList::setEvent();
}

void TodoList::setEvent(){
    //Ajout
    QObject::connect(ui->boutonPlusPrincipale, &QPushButton::clicked, this, &TodoList::ajoutItemListPrincipale);

    QObject::connect(ui->boutonPlusSecondaire, &QPushButton::clicked, this, &TodoList::ajoutItemListSecondaire);

    //Suppression d'un élément
    QObject::connect(ui->boutonMoinsPrincipale, &QPushButton::clicked, this, &TodoList::suppressionItemsListPrincipale);

    QObject::connect(ui->boutonMoinsSecondaire, &QPushButton::clicked, this, &TodoList::suppressionItemsListSecondaire);

    //Suppression de tout les éléments
    QObject::connect(ui->boutonSupprimer, &QPushButton::clicked, [=](){
        ui->listWidgetPrincipale->clear();
        ui->listWidgetSecondaire->clear();
    });

    //Enregistrement

    // Fermer
    QObject::connect(ui->boutonFermer, &QPushButton::clicked, this, &QApplication::quit);
}

void TodoList::reloadListPrincipale() {
    ui->listWidgetPrincipale->clear();
    for(qsizetype i = 0; i < listPrincipal.size(); i++) {
        ui->listWidgetPrincipale->addItem(new QListWidgetItem(listPrincipal.takeAt(i)));
    }
}

void TodoList::reloadListSecondaire() {
    ui->listWidgetPrincipale->clear();
    for(qsizetype i = 0; i < listSecondaire.size(); i++) {
        ui->listWidgetPrincipale->addItem(new QListWidgetItem(listSecondaire.takeAt(i)));
    }
}

// Ajout
void TodoList::ajoutItemListPrincipale() {
    QListWidgetItem *item = new QListWidgetItem(QInputDialog::getText(this, "Nom de la tache", "Tache :"));
    item->setCheckState(Qt::Unchecked);
    listPrincipal.append(*item);
    ui->listWidgetPrincipale->addItem(item);
}

void TodoList::ajoutItemListSecondaire() {
    QListWidgetItem *item = new QListWidgetItem(QInputDialog::getText(this, "Nom de la tache", "Tache :"));
    item->setCheckState(Qt::Unchecked);
    listPrincipal.append(*item);
    ui->listWidgetSecondaire->addItem(item);
}

// Suppression
void TodoList::suppressionItemsListPrincipale() {
    QList listSuppression = ui->listWidgetPrincipale->selectedItems();
    if (!listSuppression.isEmpty()) {
        for (auto x : listSuppression) {
            listPrincipal.remove(ui->listWidgetPrincipale->row(x));
            delete ui->listWidgetPrincipale->takeItem(ui->listWidgetPrincipale->row(x));
        }
    }
}

void TodoList::suppressionItemsListSecondaire() {
    QList listSuppression = ui->listWidgetSecondaire->selectedItems();
    if (!listSuppression.isEmpty()){
        for (auto x : listSuppression) {
            listSecondaire.remove(ui->listWidgetSecondaire->row(x));
            delete ui->listWidgetSecondaire->takeItem(ui->listWidgetSecondaire->row(x));
        }
    }
}

void TodoList::enregistrement() {
    QString file = QFileDialog::getSaveFileName(this, "Enregistrement Xml", ".", "Xml files (*.xml)");

}

TodoList::~TodoList()
{
    delete ui;
}

