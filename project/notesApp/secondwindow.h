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

/*!
 * \brief The secondwindow class
 *
 * The window that provides user interaction with archived notes
 *
 */
class secondwindow : public QDialog, originator
{
    Q_OBJECT

    friend class notesTest;
public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();

public slots:
    /*!
  * \brief deleteItemNoSignal
  * \param text[in] text of an item
  * \param _id[in] row number of the item in the list
  * Removes item from the list that demonstrates previously saved and newly added notes without signal
  */
 void deleteItemNoSignal(QString text, uint _id) override;

 /*!
   * \brief addItemNoSignal
  * \param text[in] text of an item
  * \param _id[in] row number of the item in the list
  *Adds item to the list that demonstrates previously saved and newly added notes without signal
   */
  void addItemNoSignal(QString text, uint _id) override ;
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
