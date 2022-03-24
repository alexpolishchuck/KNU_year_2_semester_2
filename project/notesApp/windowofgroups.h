#ifndef WINDOWOFGROUPS_H
#define WINDOWOFGROUPS_H

#include <QDialog>
#include <QListWidgetItem>
#include "filereader.h"

namespace Ui {
class windowofgroups;
}

/*!
 * \brief The windowofgroups class
 *
 * Provides convenient list of groups to interact with
 *
 */
class windowofgroups : public QDialog
{
    Q_OBJECT
friend class notesTest;
public:
    explicit windowofgroups(QWidget *parent = nullptr);
    ~windowofgroups();
/*!
 * \brief receiveData
 * \param a[in] text of item
 * \param curInMenu[in] name of the currently selected group
 *
 * Receives data sent from another window
 */
void receiveData(QString a, QString curInMenu);
/*!
 * \brief receiveData
 * \param a[in] text of item
 * \param curInMenu[in] name of the currently selected group
 * \param b[in] is true, if new item was added to another group,otherwise is false
 *
 * Receives data sent from another window
 */
void receiveData(QString a, QString curInMenu,bool* b);

private slots:


    void on_pushButton_released();

    void on_pushButton_pressed();

private:
    Ui::windowofgroups *ui;



    /*!
     * \brief addtofile
     * \param nameoffile[in]
     *
     * Saves item to file
     */
    void addtofile(QString nameoffile);

    /*!
     * \brief line
     * Text of the selected item
     */
    QString line;
    /*!
     * \brief curMenu
     * Name of currently open group
     */
    QString curMenu;
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

    bool* isadded = nullptr;

    /*!
     * @filereader See filereader
     */
    filereader* fr;




    //void closeEvent(QCloseEvent *event) override;
};

#endif // WINDOWOFGROUPS_H
