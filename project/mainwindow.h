#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include <QListWidgetItem>
#include "secondwindow.h"
#include "windowofgroups.h"
#include <QCloseEvent>
//#include "editinghistory.h"
#include <QVector>
#include <QShortcut>
#include <editinghistory.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public originator
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

 void deleteItemNoSignal(QString text, uint _id) override;

  void addItemNoSignal(QString text, uint _id) override ;

private slots:
   // void on_pushButton_clicked();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_released();

    void on_lineEdit_editingFinished();

    void removeChecked(QListWidgetItem *item);

    void saveToFile(QString,QListWidget* NotesList);

    void readFromFile( QListWidget*, QString);

   // void saveToArchive(QListWidgetItem *item);

    void saveItem(QListWidgetItem *item, QString nameoffile);

    void deleteItem(QListWidgetItem *item, QListWidget* NotesList);

    void removeSelectedItem();

    void removeSelectedItem(QListWidget* );                                    //overloaded

    void readFromFileNotCheckable(QListWidget* NotesList, QString nameoffile);

    void showNotesFromSelectedGroup();

    void changeMenuSelectionBack();

    void isNameValid();

    void editNameOfGroup();

    void removeLastGroupItem();

    void showContextMenu(const QPoint &pos);

    void copyToGroup();

    void createfiles();

    void moveToGroup();

    void recreateHistoryOperator();

signals:
    void sendDataToAnotherWindow(QString);

   // void itemIsAdded(QListWidgetItem*);

    void itemIsAdded(QString,uint);

    void itemIsDeleted(QString, uint);

    void anotherWindowIsClosed();

private:

    Ui::MainWindow *ui;

    secondwindow* secwindow;

    windowofgroups* windowog;

    caretaker* historyOperator;

   // QVector<QShortcut*> keyCombos;

    int prevIndex;

void createConnections();

void deleteFile(QString);

void closeEvent (QCloseEvent *event) override;


QString qspressed = "font: 11pt\"Bodoni MT\" ;background-color: rgb(109, 127, 209); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";

QString qsreleased = "font: 11pt\"Bodoni MT\" ;background-color: rgb(172, 169, 255); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";

QString const NameOfNotes ="notes";
QString const NameOfArchive="archive";
QString const NameOfMenu = "menu";
QString const fileFormat = ".txt";

};
#endif // MAINWINDOW_H
