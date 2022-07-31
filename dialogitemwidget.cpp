#include "dialogitemwidget.h"
#include "ui_dialogitemwidget.h"

DialogItemWidget::DialogItemWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogItemWidget)
{
    ui->setupUi(this);
}

DialogItemWidget::~DialogItemWidget()
{
    delete ui;
}
