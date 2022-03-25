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
  *
  * Removes item from the list that demonstrates previously saved and newly added notes without signal
  */
 void deleteItemNoSignal(QString text, uint _id) override;

 /*!
   * \brief addItemNoSignal
  * \param text[in] text of an item
  * \param _id[in] row number of the item in the list
  *
  *Adds item to the list that demonstrates previously saved and newly added notes without signal
   */
  void addItemNoSignal(QString text, uint _id) override ;
private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_2_released();

    void on_pushButton_released();

    /*!
    * \brief removeChecked
    * \param item[in] checked item
    *
    * Removes checked item from the list of notes
    */
   void removeChecked(QListWidgetItem *item);
   /*!
    * \brief removeSelectedItem
    * Removes selected item from the list of notes
    */
   void removeSelectedItem();
   /*!
    * \brief moveToFile
    * \param item[in]
    *
    * Saves item to the file
    */
   void moveToFile(QListWidgetItem *item);
   /*!
    * \brief saveArchive
    * Saves list of notes to the archive
    */
   void saveArchive();

private:
    Ui::secondwindow *ui;


    /*!
 * \brief createConnections
 * Creates connections between QObjects
 */
    void createConnections();
    /*!
     * \brief closeEvent
     * \param event
     * Displays message box before closing the application
     */
    void closeEvent (QCloseEvent *event) override;
    /*!
     * \brief qspressed
     * Style for a pressed button
     */
    QString const qspressed = "font: 11pt\"Bodoni MT\" ;background-color: rgb(109, 127, 209); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";
    /*!
     * \brief qsreleased
     * Style for a released button
     */
    QString const qsreleased = "font: 11pt\"Bodoni MT\" ;background-color: rgb(172, 169, 255); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";

    /*!
     * @ref caretaker See caretaker
     */
    caretaker* historyOperator;
    /*!
     * @filereader See filereader
     */
    filereader* fr;


signals:
    void itemIsAdded(QString,uint);
    void itemIsDeleted(QString, uint);

};

#endif // SECONDWINDOW_H
