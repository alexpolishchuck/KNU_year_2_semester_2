#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QListWidgetItem>
#include <QCloseEvent>
namespace Ui {
class secondwindow;
}

class secondwindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();
private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_released();

    void readFromFile( QListWidget*, QString);

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

};

#endif // SECONDWINDOW_H
