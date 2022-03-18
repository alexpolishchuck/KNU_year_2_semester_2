#include "editinghistory.h"

//       concretememento::
//       caretaker::
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


void caretaker::backUpDeleted(QString str)
{
    //don't foget to set a limit for saved mementos
    if(mementos.size() >limit)
        mementos.pop_front();

    concretememento* mem = new concretememento(str,QTime::currentTime());

    mem->setDeleted(true);

    mementos.push_back(mem);
    qDebug()<<"deleted";

}
//    void caretaker:: backUpAdded(QListWidgetItem* it)
//    {
//        if(mementos.size() >limit)
//            mementos.pop_front();

//        memento* mem = new concretememento(it,QTime::currentTime());
//        mem->setAdded(true);
//        mementos.push_back(mem);
//        qDebug()<<"added";
//    }

void caretaker::backUpAdded(QString str)
{
    if(mementos.size() >limit)
        mementos.pop_front();

    concretememento* mem = new concretememento(str,QTime::currentTime());

    mem->setAdded(true);

    mementos.push_back(mem);

    qDebug()<<"added";
}

void caretaker::undo()
{
    if(mementos.size()<1)
        return;
    concretememento*mem = mementos.last();
    if(mem->isAdded())
    {
       emit deleteAdded(mem->gettext());
        qDebug()<<"Trying to delete added";

    }
    else if(mem->isDeleted())
    {
        emit addDeleted(mem->gettext());
    }

    mementos.pop_back();
}


caretaker::caretaker()
{
        mementos.reserve(1);
}

caretaker::~caretaker()
{
    int count = mementos.size();
    for(int i=0; i<count ; i++)
        delete mementos[i];
}
