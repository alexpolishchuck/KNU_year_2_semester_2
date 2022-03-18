#ifndef EDITINGHISTORY_H
#define EDITINGHISTORY_H
#include <QObject>
#include <QString>
#include <QTime>
#include <QVector>
#include <QListWidgetItem>

class caretaker;

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
};

class concretememento:public memento
{


public:

//    concretememento(QString str, QTime t):text(str),time(t),isdeleted(false),isadded(false)
//    {
//    }
    //concretememento(QListWidgetItem* it,QTime t):time(t),isdeleted(false), isadded(false),item(it)
    //{}
    concretememento(QString str,QTime t):text(str),time(t),isdeleted(false), isadded(false)
    {}

    QTime gettime() override;

   // QListWidgetItem* getitem() override;


    QString gettext() override;


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
   // QListWidgetItem* item;
};

class caretaker:public QObject
{
    Q_OBJECT

    public:
    caretaker();
    ~caretaker();



public slots:
    void backUpDeleted(QString str);

    void backUpAdded(QString str);

    void undo();


signals:
    void deleteAdded(QString);

    void addDeleted(QString);

    private:

    QVector <concretememento*> mementos;

    const int limit = 20;


};

#endif // EDITINGHISTORY_H
