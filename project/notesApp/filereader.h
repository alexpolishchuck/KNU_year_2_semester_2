#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QString>

/*!
 * \brief The initfilereader class
 *
 * Abstract class, provides template for filereader
 */
class initfilereader
{
public:
    initfilereader(QString notes,QString archive,QString menu, QString file);
    initfilereader(){};

    /*!
      * \brief readFromFile
      *
      * Template method, reads information from files and saves it to QListWidgets
      */
     virtual void readFromFile( QListWidget*, QString);

     /*!
      * \brief getNameOfNotes
      * \return Name of the main file of saved notes
      */
    virtual  QString getNameOfNotes()
    {
        return this->NameOfNotes;
    };
     /*!
      * \brief getNameOfArchive
      * \return Name of the archive
      */
     virtual QString getNameOfArchive()
    {
    return this->NameOfArchive;
    };
     /*!
      * \brief getNameOfMenu
      * \return Name of the menu file
      */
     virtual QString getNameOfMenu()
    {
    return this->NameOfMenu;


    };
     /*!
      * \brief getFileFormat
      * \return File format of the files
      */
    virtual QString getFileFormat()
    {

        return this->fileFormat;
    };
protected:
    /*!
     * \brief setcheckable
     * \param item[in,out] the item to edit
     *
     * Sets CheckStateRole for the item
     */
    virtual void setcheckable(QListWidgetItem* item)=0;
    /*!
     * \brief setToolTip
     * \param item[in,out] the item to edit
     * \param str[in] the string to set as a ToolTip
     *
     * Sets ToolTip for the specific item of the list
     */
    virtual void setToolTip(QListWidgetItem* item, QString str){};
    /*!
     * \brief makeshort
     * \param[in] NotesList list widget
     * \param[in] str string to edit
     * \return shortened initial string
     *
     * Elides symbols that are beyond the limit
     */
    virtual QString makeshort(QListWidget* NotesList,QString str)=0;

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



//class filereader:public initfilereader
//{
//public:
//    filereader(QString notes,QString archive,QString menu, QString file);
//    filereader(){};
//    virtual ~filereader(){};
 //  /*!
 //    * \brief readFromFileCheckable
//      * Reads file, saves items with the CheckStateRole
  //   */

//     void readFromFileCheckable( QListWidget*, QString) override;

//     /*!
//      * \brief readFromFileNotCheckable
//      * Reads file, saves items without the CheckStateRole
//      */
//     void readFromFileNotCheckable( QListWidget*, QString) override;

//     void readFromFile( QListWidget*, QString) override;

//     /*!
//      * @ref initfilereader::getNameOfNotes
//      */
//     QString getNameOfNotes() override;
//     /*!
//      * @ref initfilereader::getNameOfArchive
//      */
//     QString getNameOfArchive() override;
//     /*!
//      * @ref initfilereader::getNameOfMenu
//      */
//     QString getNameOfMenu() override;
//     /*!
//      * @ref initfilereader::getFileFormat
//      */
//     QString getFileFormat() override;
//protected:
//     /*!
//      * @ref initfilereader::setcheckable
//      */
//     virtual void setcheckable(QListWidgetItem* item) override{return;};
//     /*!
//      * @ref initfilereader::setToolTip
//      */
//     virtual void setToolTip(QListWidgetItem* item, QString str) override{return;};
//     /*!
//      * @ref initfilereader::makeshort
//      */
//     virtual QString makeshort(QListWidget* NotesList,QString str) override{return str;};
//     /*!
//      * \brief NameOfNotes
//      * Name of the main file of
//      */
//     QString const NameOfNotes ="notes";
//     /*!
//      * \brief NameOfArchive
//      * Name of file that contains archived notes
//      */
//     QString const NameOfArchive="archive";
//     /*!
//      * \brief NameOfMenu
//      * Name of file that contains all names of groups
//      */
//     QString const NameOfMenu = "menu";
//     /*!
//      * \brief fileFormat
//      * Stores file format
//      */
//     QString const fileFormat = ".txt";
//};

class filesaver
{
protected:
    virtual void saveToFile(QString nameOfFile,QListWidget* NotesList)=0;

    virtual void saveItem(QListWidgetItem *item, QString nameoffile)=0;
};



/*!
 * \brief The readerofnotes class
 *
 * Class that implements initfilereader, reads notes from file
 */
class readerofnotes: public initfilereader, public filesaver
{
public:
    readerofnotes(QString notes,QString archive,QString menu, QString file): initfilereader( notes, archive, menu,  file){};
    readerofnotes():initfilereader(){};
    ~readerofnotes(){};
    /*!
     * @ref initfilereader::makeshort
     */
    QString makeshort(QListWidget* NotesList,QString str) override
    {
        int width = NotesList->width()/2;
       str = QFontMetrics(NotesList->font()).elidedText(str,Qt::ElideRight,width,0);
       return str;
    }
    /*!
     * @ref initfilereader::setcheckable
     *
     */
    void setcheckable(QListWidgetItem *item) override
    {
         item->setData(Qt::CheckStateRole,0);
    }
    /*!
     * \brief saveToFile
     * \param nameOfFile[in] name of file
     * \param NotesList[in] list of notes
     *
     * Saves notes from <QListWidget* NotesList> to file
     */
    void saveToFile(QString nameOfFile,QListWidget* NotesList) override;
    /*!
     * \brief saveItem
     * \param item[in]
     * \param nameoffile[in] name of file
     *
     * Saves specific item to file
     */

    void saveItem(QListWidgetItem *item, QString nameoffile) override;
};
/*!
 * \brief The readerofgroups class
 *
 * Class that implements initfilereader, reads names of groups from file
 */
class readerofgroups : public initfilereader, public filesaver
{
public:
    readerofgroups():initfilereader(){};
    readerofgroups(QString notes,QString archive,QString menu, QString file): initfilereader( notes, archive, menu,  file){};
    ~readerofgroups(){};
private:


    /*!
     * @ref initfilereader::makeshort
     */
    QString makeshort(QListWidget* NotesList,QString str) override
    {
        int width = NotesList->width()/2;
       str = QFontMetrics(NotesList->font()).elidedText(str,Qt::ElideRight,width,0);
       return str;
    }
    /*!
     * @ref initfilereader::setToolTip
     */

    void setToolTip(QListWidgetItem* item,QString str) override
    {
        item->setToolTip(str);
    }

    /*!
     * @ref initfilereader::setcheckable
     *
     */
    void setcheckable(QListWidgetItem *item) override
    {
         item->setData(Qt::TextAlignmentRole,Qt::AlignLeft);
    }

    /*!
     * \brief saveToFile
     * \param nameOfFile[in] name of file
     * \param NotesList[in] list of notes
     *
     * Saves notes from <QListWidget* NotesList> to file
     */
    void saveToFile(QString nameOfFile,QListWidget* NotesList) override;
    /*!
     * \brief saveItem
     * \param item[in]
     * \param nameoffile[in] name of file
     *
     * Saves specific item to file
     */

    void saveItem(QListWidgetItem *item, QString nameoffile) override;
};



#endif // FILEREADER_H
