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



class memento
{

public:
    virtual QTime gettime()=0;
    virtual bool isAdded()=0;
    virtual bool isDeleted()=0;
    virtual void setAdded(bool added)=0;
    virtual void setDeleted(bool deleted)=0;
    //virtual QListWidgetItem* getitem()=0;
    virtual  QString gettext()=0;
    virtual uint getid()=0;
     ~memento(){};
    //virtual ~memento();
};

class EDITINGHISTORY_EXPORT concretememento:public memento
{


public:


    concretememento(QString str,QTime t,int _id):text(str),time(t),isdeleted(false), isadded(false),id(_id)
    {}
//    ~concretememento()
//    {}
    ~concretememento(){};

    QTime gettime() override;

   // QListWidgetItem* getitem() override;


    QString gettext() override;

    uint getid() override;

    bool isAdded() override;

    bool isDeleted() override;

    void setAdded(bool added) override;

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

class EDITINGHISTORY_EXPORT caretaker:public QObject
{
    Q_OBJECT

    public:
    caretaker(QObject* qobj);
  virtual  ~caretaker();

     memento* getmemento(int id);

     int getlimit();

     int elements();

public slots:
    void backUpDeleted(QString str, uint _id);

    void backUpAdded(QString str, uint _id);

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

class EDITINGHISTORY_EXPORT originator
{

public:
   virtual void deleteItemNoSignal(QString text, uint _id)=0 ;

    virtual void addItemNoSignal(QString text, uint _id)=0 ;


};

#endif // EDITINGHISTORY_H
