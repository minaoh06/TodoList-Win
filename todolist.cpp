#include "todolist.h"
#include "ui_todolist.h"

TodoList::TodoList(QWidget *parent) : QWidget(parent), ui(new Ui::TodoList)
{
    //Constructiuon de la fenetre avec tout les widgets a l'intérieur
    ui->setupUi(this);
    dir = QDir(QDir::homePath() + "/Documents/TodoList");
    if (!dir.exists()){
        QDir dirTmp = QDir(QDir::homePath() + "/Documents");
        dirTmp.mkdir("TodoList");
    }

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
    QObject::connect(ui->boutonEnregistrer, &QPushButton::clicked, this, &TodoList::enregistrement);

    //Ouvrir
    QObject::connect(ui->boutonOuvrir, &QPushButton::clicked, this, &TodoList::importation);

    // Fermer
    QObject::connect(ui->boutonFermer, &QPushButton::clicked, this, &QApplication::quit);
}

// Ajout
void TodoList::ajoutItemListPrincipale() {
    QListWidgetItem *item = new QListWidgetItem(QInputDialog::getText(this, "Nom de la tache", "Tache :"));
    item->setCheckState(Qt::Unchecked);
    ui->listWidgetPrincipale->addItem(item);
}

void TodoList::ajoutItemListSecondaire() {
    QListWidgetItem *item = new QListWidgetItem(QInputDialog::getText(this, "Nom de la tache", "Tache :"));
    item->setCheckState(Qt::Unchecked);
    ui->listWidgetSecondaire->addItem(item);
}

// Suppression
void TodoList::suppressionItemsListPrincipale() {
    QList listSuppression = ui->listWidgetPrincipale->selectedItems();
    if (!listSuppression.isEmpty()) {
        for (auto x : listSuppression) {
            delete ui->listWidgetPrincipale->takeItem(ui->listWidgetPrincipale->row(x));
        }
    }
}

void TodoList::suppressionItemsListSecondaire() {
    QList listSuppression = ui->listWidgetSecondaire->selectedItems();
    if (!listSuppression.isEmpty()){
        for (auto x : listSuppression) {
            delete ui->listWidgetSecondaire->takeItem(ui->listWidgetSecondaire->row(x));
        }
    }
}

void TodoList::enregistrement() {
    // Récupération du file name
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrement Xml", QDir::homePath() + "/Documents/TodoList", "Xml files (*.xml)");
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

        if (ui->listWidgetSecondaire->count() > 0){
            xmlWriter.writeStartElement("SECONDAIRE");
            for(qsizetype i = 0; i < ui->listWidgetSecondaire->count(); i++){
                xmlWriter.writeStartElement("ITEM");

                xmlWriter.writeTextElement("TITRE", ui->listWidgetSecondaire->item(i)->text());
                // CheckState
                switch (ui->listWidgetSecondaire->item(i)->checkState()) {
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

void TodoList::importation() {

    QString fileName = QFileDialog::getOpenFileName(this, "Enregistrement Xml", QDir::homePath() + "/Documents/TodoList", "Xml files (*.xml)");
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
            else if (xmlReader.name().toString() == "SECONDAIRE") {
                xmlReader.readNextStartElement();
                QString titre, check;
                while(xmlReader.name().toString() != "SECONDAIRE"){
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
                        ui->listWidgetSecondaire->addItem(item);
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

TodoList::~TodoList()
{
    delete ui;
}

