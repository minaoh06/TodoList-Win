#ifndef TODOOBJECT_H
#define TODOOBJECT_H

#include <QWidget>
#include <QString>

namespace Ui {
class TodoObject;
}

class TodoObject : public QWidget
{
    Q_OBJECT

public:
    //explicit TodoObject(QWidget *parent = nullptr);
    explicit TodoObject(QString name, QString description = nullptr, QWidget *parent = nullptr);
    ~TodoObject();

    bool isChecked();
    void setDescription(QString desc);
    QString getDescription();


private:
    Ui::TodoObject *ui;
    QString *description;

};

#endif // TODOOBJECT_H
