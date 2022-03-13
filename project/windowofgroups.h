#ifndef WINDOWOFGROUPS_H
#define WINDOWOFGROUPS_H

#include <QDialog>
#include <QListWidgetItem>
//#include "mainwindow.h"
namespace Ui {
class windowofgroups;
}

class windowofgroups : public QDialog
{
    Q_OBJECT

public:
    explicit windowofgroups(QWidget *parent = nullptr);
    ~windowofgroups();

void receiveData(QString,QString);

void receiveData(QString a, QString curInMenu,bool* b);

private slots:


    void on_pushButton_released();

    void on_pushButton_pressed();

private:
    Ui::windowofgroups *ui;

    void readFromFileNotCheckable(QListWidget* NotesList, QString nameoffile);

    void addtofile(QString nameoffile);

    QString line;

    QString curMenu;

    QString qspressed = "font: 11pt\"Bodoni MT\" ;background-color: rgb(109, 127, 209); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";

    QString qsreleased = "font: 11pt\"Bodoni MT\" ;background-color: rgb(172, 169, 255); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";

    bool* isadded = nullptr;
};

#endif // WINDOWOFGROUPS_H
