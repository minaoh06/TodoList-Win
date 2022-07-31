#ifndef DIALOGITEMWIDGET_H
#define DIALOGITEMWIDGET_H

#include <QDialog>

namespace Ui {
class DialogItemWidget;
}

class DialogItemWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DialogItemWidget(QWidget *parent = nullptr);
    ~DialogItemWidget();

private:
    Ui::DialogItemWidget *ui;
};

#endif // DIALOGITEMWIDGET_H
