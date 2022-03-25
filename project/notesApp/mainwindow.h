#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include <QListWidgetItem>
#include "secondwindow.h"
#include "windowofgroups.h"
#include <QCloseEvent>
#include <QVector>
#include <QShortcut>
#include <editinghistory.h>
#include "filereader.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*!
 * \brief The MainWindow class
 *
 * Provides all the main features of this aplication
 *
 */
class MainWindow : public QMainWindow, public originator
{
    Q_OBJECT

    friend class notesTest;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /*!
  * \brief deleteItemNoSignal
  * @ref originator "See originator::deleteItemNoSignal(QString text, uint _id)"
  */
 void deleteItemNoSignal(QString text, uint _id) override;

 /*!
   *\brief addItemNoSignal
   * @ref originator "See originator::addItemNoSignal(QString text, uint _id)"
   */
  void addItemNoSignal(QString text, uint _id) override ;



private slots:

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_released();

    void on_lineEdit_editingFinished();

    void removeChecked(QListWidgetItem *item);//

    /*!
     * \brief removeSelectedItem
     * Removes selected item from the list of notes
     */
    void removeSelectedItem();//
    /*!
     * \brief removeSelectedItem
     * Removes selected item from the list of notes
     */
    void removeSelectedItem(QListWidget* );                                    //overloaded
    /*!
     * \brief showNotesFromSelectedGroup
     * Displays notes from the selected group
     */
    void showNotesFromSelectedGroup();//
    /*!
     * \brief editNameOfGroup
     * Edits name of the last added group
     */
    void editNameOfGroup();//
    /*!
     * \brief showContextMenu
     * \param pos[in] position of the cursor
     *
     * Displays context menu
     */
    void showContextMenu(const QPoint &pos);//
    /*!
     * \brief recreateHistoryOperator
     * Creates new history opearator
     * @ref caretaker See caretaker
     */
    void recreateHistoryOperator();//

    /*!
     * \brief copyToGroup
     * Copies item to the selected group
     */
    void copyToGroup();

    /*!
     * \brief moveToGroup
     * Moves item to the selected group
     */
    void moveToGroup();

    /*!
     * \brief saveToFile
     * \param nameOfFile[in] name of file
     * \param NotesList[in] list of notes
     *
     * Saves notes from <QListWidget* NotesList> to file
     */
    void saveToFile(QString nameOfFile,QListWidget* NotesList);
    /*!
     * \brief saveItem
     * \param item[in]
     * \param nameoffile[in] name of file
     *
     * Saves specific item to file
     */

    void saveItem(QListWidgetItem *item, QString nameoffile);
    /*!
     * \brief deleteItem
     * \param item
     * \param NotesList list of notes
     *
     * Deletes item from the list, send
     */
    void deleteItem(QListWidgetItem *item, QListWidget* NotesList);

    /*!
     * \brief createfiles
     * Creates files of the primary groups, such as 'notes'and 'archive'
     */
    void createfiles();
    /*!
     * \brief changeMenuSelectionBack
     * Opens previous group
     */
    void changeMenuSelectionBack();
    /*!
     * \brief isNameValid
     * Checks if name of a group meets all the requirements
     */
    void isNameValid();
    /*!
     * \brief removeLastGroupItem
     */

    /*!
     * \brief removeLastGroupItem
     * Removes invalid item from the list of groups
     */
    void removeLastGroupItem();
signals:
    void sendDataToAnotherWindow(QString);

    void itemIsAdded(QString,uint);

    void itemIsDeleted(QString, uint);

    void anotherWindowIsClosed();



private:

    Ui::MainWindow *ui;

    /*!
     * @ref secondwindow See secondwindow
     */
    secondwindow* secwindow;

    /*!
     * @ref windowofgroups See windowofgroups
     */
    windowofgroups* windowog;

    /*!
     * @ref caretaker See caretaker
     */
    caretaker* historyOperator;
    /*!
     * @filereader See filereader
     */
    filereader* fr;
    /*!
     * \brief prevIndex
     * Saves id of the previously selected group
     */


    int prevIndex;
    /*!
     * \brief letterlimit
     * Maintains maximum number of symbols that can be written in one note
     */
    const int letterlimit = 30;

    /*!
 * \brief createConnections
 * Creates connections between QObjects
 */
void createConnections();
/*!
 * \brief deleteFile
 * Removes file
 */
void deleteFile(QString);
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
QString qspressed = "font: 11pt\"Bodoni MT\" ;background-color: rgb(109, 127, 209); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";
/*!
 * \brief qsreleased
 * Style for a released button
 */
QString qsreleased = "font: 11pt\"Bodoni MT\" ;background-color: rgb(172, 169, 255); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";




};



#endif // MAINWINDOW_H
