#include "todoobject.h"
#include "ui_todoobject.h"

TodoObject::TodoObject(QString name, QString desc, QWidget *parent) : QWidget(parent), ui(new Ui::TodoObject)
{
    ui->setupUi(this);
    ui->nom->setText(name);
    description = new QString(desc);
}

TodoObject::~TodoObject()
{
    delete ui;
}

bool TodoObject::isChecked(){
    return ui->checkBoxValidation->isChecked();
}
