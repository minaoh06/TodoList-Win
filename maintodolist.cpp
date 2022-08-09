#include "maintodolist.h"
#include "ui_maintodolist.h"

MainTodoList::MainTodoList(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainTodoList)
{
    ui->setupUi(this);

    dir = QDir(QDir::homePath() + "/Documents/TodoList");
    if (!dir.exists()){
        QDir dirTmp = QDir(QDir::homePath() + "/Documents");
        dirTmp.mkdir("TodoList");
    }

    setEvent();
}

MainTodoList::~MainTodoList()
{

}

void MainTodoList::setEvent() {
    //Ajout
    QObject::connect(ui->boutonPlusPrincipale, &QPushButton::clicked, this, &MainTodoList::ajoutItemListPrincipale);

    //Suppression d'un élément
    QObject::connect(ui->boutonMoinsPrincipale, &QPushButton::clicked, this, &MainTodoList::suppressionItemsListPrincipale);

    //Quitter
    QObject::connect(ui->actionFermer, &QAction::triggered, this, &QApplication::quit);

    //Enregistrer
    QObject::connect(ui->actionEnregistrer, &QAction::triggered, this, &MainTodoList::enregistrement);

    //Ouvrir
    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainTodoList::importation);
}

void MainTodoList::ajoutItemListPrincipale() {
    QListWidgetItem *item = new QListWidgetItem(QInputDialog::getText(this, "Nom de la tache", "Tache :"));
    item->setCheckState(Qt::Unchecked);
    ui->listWidgetPrincipale->addItem(item);
}

// Suppression
void MainTodoList::suppressionItemsListPrincipale() {
    QList listSuppression = ui->listWidgetPrincipale->selectedItems();
    if (!listSuppression.isEmpty()) {
        for (auto x : listSuppression) {
            delete ui->listWidgetPrincipale->takeItem(ui->listWidgetPrincipale->row(x));
        }
    }
}

void MainTodoList::enregistrement() {
    // Récupération du file name
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrement Xml", QDir::homePath() + "/Documents/TodoList/", "Xml files (*.xml)");
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)){

        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("TODO");

        //Principale
        if (ui->listWidgetPrincipale->count() > 0){
            xmlWriter.writeStartElement("PRINCIPALE");
            for(qsizetype i = 0; i < ui->listWidgetPrincipale->count(); i++){
                xmlWriter.writeStartElement("ITEM");

                xmlWriter.writeTextElement("TITRE", ui->listWidgetPrincipale->item(i)->text());
                // CheckState
                switch (ui->listWidgetPrincipale->item(i)->checkState()) {
                case Qt::Checked:
                    xmlWriter.writeTextElement("CHECKSTATE", "Checked");
                    break;
                case Qt::PartiallyChecked:
                    xmlWriter.writeTextElement("CHECKSTATE", "PartiallyChecked");
                    break;
                case Qt::Unchecked:
                    xmlWriter.writeTextElement("CHECKSTATE", "Unchecked");
                    break;
                default:
                    xmlWriter.writeTextElement("CHECKSTATE", "lol");
                    break;
                }

                xmlWriter.writeEndElement();
            }
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}

void MainTodoList::importation() {

    QString fileName = QFileDialog::getOpenFileName(this, "Enregistrement Xml", QDir::homePath() + "/Documents/TodoList/", "Xml files (*.xml)");
    QFile file(fileName);

    if (file.open(QFile::ReadOnly | QFile::Text)){

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);


        while (xmlReader.name().toString() != "TODO") {
            xmlReader.readNext();
        }

        while(!xmlReader.isEndDocument()){
            xmlReader.readNextStartElement();

            if (xmlReader.name().toString() == "PRINCIPALE") {
                xmlReader.readNextStartElement();
                QString titre, check;
                while(xmlReader.name().toString() != "PRINCIPALE"){
                    if (xmlReader.name().toString() == "ITEM"){
                       // Selection des éléments
                        xmlReader.readNextStartElement();
                        titre = xmlReader.readElementText();
                        xmlReader.readNextStartElement();
                        check = xmlReader.readElementText();
                        xmlReader.readNextStartElement();
                        xmlReader.readNextStartElement();
                        qDebug() << titre << check;

                        // Ajout de l'item dans la liste
                        QListWidgetItem *item = new QListWidgetItem(titre);
                        if (check == "Checked"){
                            item->setCheckState(Qt::Checked);
                        } else if (check == "Unchecked") {
                            item->setCheckState(Qt::Unchecked);
                        } else {
                            item->setCheckState(Qt::PartiallyChecked);
                        }
                        ui->listWidgetPrincipale->addItem(item);
                    }
                }
            }
            else {
                xmlReader.readNext();
                break;
            }
            qDebug() << xmlReader.name();
        }
    }
}
