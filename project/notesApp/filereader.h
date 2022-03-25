#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QString>

/*!
 * \brief The filereader class
 *
 * The class responsible for reading files, creating items (QListWidgetItem) and adding them to relevant lists (QListWidget)
 *
 */

class filereader
{
public:
    filereader(QString notes,QString archive,QString menu, QString file);
    filereader(){};
    virtual ~filereader(){};
    /*!
      * \brief readFromFileCheckable
      * Reads file, saves items with the CheckStateRole
      */

     void readFromFileCheckable( QListWidget*, QString);

     /*!
      * \brief makeshort
      * \param[in] NotesList list widget
      * \param[in] str string to edit
      * \return shortened initial string
      *
      * Elides symbols that are beyond the limit
      */
     virtual QString makeshort(QListWidget* NotesList,QString str);

     /*!
      * \brief setToolTip
      * \param item[in,out] the item to edit
      * \param str[in] the string to set as a ToolTip
      *
      * Sets ToolTip for the specific item of the list
      */
     virtual void setToolTip(QListWidgetItem* item, QString str);

     /*!
      * \brief readFromFileNotCheckable
      * Reads file, saves items without the CheckStateRole
      */
     void readFromFileNotCheckable( QListWidget*, QString);

     /*!
      * \brief setcheckable
      * \param item[in,out] the item to edit
      *
      * Sets CheckStateRole for the item
      */
     virtual void setcheckable(QListWidgetItem* item);
     /*!
      * \brief getNameOfNotes
      * \return Name of the main file of saved notes
      */
     QString getNameOfNotes();
     /*!
      * \brief getNameOfArchive
      * \return Name of the archive
      */
     QString getNameOfArchive();
     /*!
      * \brief getNameOfMenu
      * \return Name of the menu file
      */
     QString getNameOfMenu();
     /*!
      * \brief getFileFormat
      * \return File format of the files
      */
     QString getFileFormat();
protected:
     /*!
      * \brief NameOfNotes
      * Name of the main file of
      */
     QString const NameOfNotes ="notes";
     /*!
      * \brief NameOfArchive
      * Name of file that contains archived notes
      */
     QString const NameOfArchive="archive";
     /*!
      * \brief NameOfMenu
      * Name of file that contains all names of groups
      */
     QString const NameOfMenu = "menu";
     /*!
      * \brief fileFormat
      * Stores file format
      */
     QString const fileFormat = ".txt";
};

#endif // FILEREADER_H
