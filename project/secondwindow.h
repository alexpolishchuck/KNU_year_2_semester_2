#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <editinghistory.h>
#include "filereader.h"

namespace Ui {
class secondwindow;
}

class secondwindow : public QDialog, originator
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();

public slots:
    void deleteItemNoSignal(QString text, uint _id) override ;

     void addItemNoSignal(QString text, uint _id) override;
private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_2_released();

    void on_pushButton_released();

   void removeChecked(QListWidgetItem *item);

   void removeSelectedItem();

   void moveToFile(QListWidgetItem *item);

   void saveArchive();

private:
    Ui::secondwindow *ui;

    void createConnections();

    void closeEvent (QCloseEvent *event) override;

    QString const qspressed = "font: 11pt\"Bodoni MT\" ;background-color: rgb(109, 127, 209); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";

    QString const qsreleased = "font: 11pt\"Bodoni MT\" ;background-color: rgb(172, 169, 255); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";

    QString const NameOfNotes ="notes";
    QString const NameOfArchive="archive";
    QString const NameOfMenu = "menu";
    QString const fileFormat = ".txt";

    caretaker* historyOperator;
    filereader* fr;

signals:
    void itemIsAdded(QString,uint);
    void itemIsDeleted(QString, uint);

};

#endif // SECONDWINDOW_H
