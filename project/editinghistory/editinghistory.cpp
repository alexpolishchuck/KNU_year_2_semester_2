#include "editinghistory.h"
#include <QObject>
#include <QString>
#include <QTime>
#include <QVector>
#include <QListWidgetItem>
#include <QShortcut>



QTime concretememento::gettime()
{
    return time;
}

//QListWidgetItem* concretememento::getitem()
//{
//    return item;
//}

QString concretememento::gettext()
{

    return text;
}

bool concretememento::isAdded()
{
    return isadded;
}
bool concretememento::isDeleted()
{
    return isdeleted;

}
void concretememento::setAdded(bool added)
{
    isadded = added;
}
void concretememento::setDeleted(bool deleted)
{
    isdeleted = deleted;
}

uint concretememento::getid()
{
    return id;
}

void caretaker::backUpDeleted(QString str, uint _id)
{
    //don't foget to set a limit for saved mementos
    if(mementos.size() >=limit)
        mementos.pop_front();

    concretememento* mem = new concretememento(str,QTime::currentTime(), _id);

    mem->setDeleted(true);

    mementos.push_back(mem);
    qDebug()<<"deleted";

}


void caretaker::backUpAdded(QString str,uint _id)
{
    if(mementos.size() >=limit)
        mementos.pop_front();

    concretememento* mem = new concretememento(str,QTime::currentTime(),_id);

    mem->setAdded(true);

    mementos.push_back(mem);

    qDebug()<<"added";
}

void caretaker::undo()
{
    if(mementos.size()<1)
        return;
    //concretememento*mem = mementos.last();
     memento*mem = mementos.last();
    if(mem->isAdded())
    {
       emit deleteAdded(mem->gettext(),mem->getid());
        qDebug()<<"Trying to delete added";

    }
    else if(mem->isDeleted())
    {
        emit addDeleted(mem->gettext(),mem->getid());
    }

    mementos.pop_back();
}

void  caretaker::createConnections(QObject* qobj)
{
    QObject::connect(qobj,SIGNAL(itemIsAdded(QString,uint)),this,SLOT(backUpAdded(QString,uint)));

    QObject::connect(qobj,SIGNAL(itemIsDeleted(QString,uint)),this,SLOT(backUpDeleted(QString,uint)));

    QObject::connect(this,SIGNAL(addDeleted(QString,uint)),qobj,SLOT(addItemNoSignal(QString,uint)));

    QObject::connect(this,SIGNAL(deleteAdded(QString,uint)),qobj,SLOT(deleteItemNoSignal(QString,uint)));

    QObject::connect(keyCombos[0],SIGNAL(activated()),this,SLOT(undo()));
}

caretaker::caretaker(QObject*qobj)
{
        parent = qobj;
        mementos.reserve(1);
        keyCombos.push_back(new QShortcut(QKeySequence(tr("Ctrl+Z")),qobj));
        createConnections(qobj);

}

caretaker::~caretaker()                     //disconnect
{
   this->disconnect();
   parent->disconnect(this);

    for(int i=0; i<keyCombos.size();i++)
    {
        keyCombos[i]->disconnect();
        delete keyCombos[i];
    }
    int count = mementos.size();
    for(int i=0; i<count ; i++)
        delete mementos[i];
}

memento* caretaker::getmemento(int id)
{
    if(id < this->mementos.size())
        return this->mementos[id];

    return nullptr;
}

int caretaker::getlimit()
{
    return limit;
}

int caretaker::elements()
{
    return mementos.size();
}
