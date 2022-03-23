#ifndef EDITINGHISTORY_H
#define EDITINGHISTORY_H

#include "editinghistory_global.h"
#include <QObject>
#include <QString>
#include <QTime>
#include <QVector>
#include <QListWidgetItem>
#include <QShortcut>


//The class derived from originator needs two signals to be created:
//void itemIsAdded(QString,uint);
//void itemIsDeleted(QString, uint);
//Those must be emitted any time an item is added or deleted to the widget


/*!
 * \brief The memento class
 *
 * Abstract class, provides template for saving information about the latest action done in the list of notes
 *
 */
class memento
{

public:
    /*!
     * \brief gettime
     * \return Time of the last action
     */
    virtual QTime gettime()=0;
    /*!
     * \brief isAdded
     * \return True, if item was added
     */
    virtual bool isAdded()=0;
    /*!
     * \brief isDeleted
     * \return True, if item was deleted
     */
    virtual bool isDeleted()=0;
    /*!
     * \brief setAdded
     * \param added
     * Assigns value of <bool added> to status of the item,that the action was performed on, in the memento
     */
    virtual void setAdded(bool added)=0;
    /*!
     * \brief setDeleted
     * \param deleted
     * Assigns value of bool deleted to status of the item,that the action was performed on, in the memento
     */
    virtual void setDeleted(bool deleted)=0;
    //virtual QListWidgetItem* getitem()=0;
    /*!
     * \brief gettext
     * \return Text of the item, the action was performed on
     */
    virtual  QString gettext()=0;
    /*!
     * \brief getid
     * \return Number of the row item occupied in the list
     */
    virtual uint getid()=0;
     ~memento(){};
    //virtual ~memento();
};

/*!
 * \brief The concretememento class
 *
 * Implements memento class
 *
 */
class EDITINGHISTORY_EXPORT concretememento:public memento
{


public:


    concretememento(QString str,QTime t,int _id):text(str),time(t),isdeleted(false), isadded(false),id(_id)
    {}
//    ~concretememento()
//    {}
    ~concretememento(){};
    /*!
     * @ref memento "See memento::gettime()"
     */
    QTime gettime() override;

   // QListWidgetItem* getitem() override;

    /*!
     * @ref memento "See memento::gettext()"
     */
    QString gettext() override;
    /*!
     * @ref memento "See memento::getid()"
     */
    uint getid() override;
    /*!
     * @ref memento "See memento::isAdded()"
     */
    bool isAdded() override;
    /*!
     * @ref memento "See memento::isDeleted()"
     */
    bool isDeleted() override;
    /*!
     * @ref memento "See memento::setAdded()"
     */
    void setAdded(bool added) override;
    /*!
     * @ref memento "See memento::setDeleted()"
     */
    void setDeleted(bool deleted) override;



private:


    QString text;
    QString nameoffile;
    QTime time;
    bool isdeleted;
    bool isadded;
    uint id;
   // QListWidgetItem* item;
};

/*!
 * \brief The caretaker class
 *
 * Responsible for storing and operating information on performed actions
 *
 */
class EDITINGHISTORY_EXPORT caretaker:public QObject
{
    Q_OBJECT

    public:
    caretaker(QObject* qobj);
  virtual  ~caretaker();
    /*!
      * \brief getmemento
      * \param id[in] Number of the saved memento in the array
      * \return Pointer to memento
      */
     memento* getmemento(int id);
     /*!
      * \brief getlimit
      * \return Maximum number of saved mementos
      */
     int getlimit();
     /*!
      * \brief elements
      * \return Number of stored mementos
      */
     int elements();

public slots:
     /*!
     * \brief backUpDeleted
     * \param str[in] Text of the item, the action was performed on
     * \param _id[in] Number of the row item occupied in the list
     * Creates new memento with information about deleted item
     */
    void backUpDeleted(QString str, uint _id);
    /*!
     * \brief backUpAdded
     * \param str[in] Text of the item,that the action was performed on
     * \param _id[in] Number of the row item occupied in the list
     * Creates new memento with information about added item
     */
    void backUpAdded(QString str, uint _id);
    /*!
     * \brief undo
     * Removes last added memento, undoes last perfromed action
     */
    void undo();



signals:
    void deleteAdded(QString, uint);

    void addDeleted(QString,uint);

private:
//public:
    QVector <concretememento*> mementos;

    void createConnections(QObject* qobj);

    const int limit = 20;

     QVector<QShortcut*> keyCombos;

     QObject* parent;

};

/*!
 * \brief The originator class
 *
 * Abstract class, provides template for the class that owns list of items,that actions will be performed on
 *
 */
class EDITINGHISTORY_EXPORT originator
{

public:
    /*!
  * \brief deleteItemNoSignal
  * \param text[in] text of an item
  * \param _id[in] row number of the item in the list
  * Removes item from the list without signal
  */
   virtual void deleteItemNoSignal(QString text, uint _id)=0 ;
    /*!
      * \brief addItemNoSignal
     * \param text[in] text of an item
     * \param _id[in] row number of the item in the list
     *Adds item to the list without signal
      */
    virtual void addItemNoSignal(QString text, uint _id)=0 ;


};

#endif // EDITINGHISTORY_H
