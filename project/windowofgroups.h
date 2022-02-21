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

private slots:


    void on_pushButton_released();

    void on_pushButton_pressed();

private:
    Ui::windowofgroups *ui;

    void readFromFileNotCheckable(QListWidget* NotesList, QString nameoffile);

    void addtofile(QString nameoffile);
};

#endif // WINDOWOFGROUPS_H
