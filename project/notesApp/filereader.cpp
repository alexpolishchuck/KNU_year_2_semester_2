#include "filereader.h"
#include <QString>
#include <QFile>
#include <QIODevice>
filereader::  filereader(QString notes,QString archive,QString menu, QString file):NameOfNotes(notes),NameOfArchive(archive),NameOfMenu(menu),fileFormat(file)
{

}

void filereader::readFromFileCheckable( QListWidget* NotesList, QString nameoffile)
{
    nameoffile+=fileFormat;
    QFile file (nameoffile);
    if(file.open(QIODevice::ReadOnly))
    {

       while(!file.atEnd())
       {
        QString line = file.readLine();
        if(line[line.size()-1]=='\n')
            line.resize(line.size()-1);

        QListWidgetItem* item = new QListWidgetItem;
        item->setText(line);
        this->setcheckable(item);
        NotesList->addItem(item);
       }
       file.close();
     }
}

void filereader::readFromFileNotCheckable( QListWidget* NotesList, QString nameoffile)
{
    nameoffile+=fileFormat;
    QFile file (nameoffile);
    if(file.open(QIODevice::ReadOnly))
    {

       while(!file.atEnd())
       {
        QString line = file.readLine();
        if(line[line.size()-1]=='\n')
            line.resize(line.size()-1);

        QListWidgetItem* item = new QListWidgetItem;
        item->setText(this->makeshort(NotesList,line));
        this->setToolTip(item, line);
        NotesList->addItem(item);
       }
       file.close();
     }
}

void filereader::setcheckable(QListWidgetItem *item)
{
     item->setData(Qt::CheckStateRole,0);
}

QString filereader::makeshort(QListWidget* NotesList,QString str)
{
    int width = NotesList->width()/2;
   str = QFontMetrics(NotesList->font()).elidedText(str,Qt::ElideRight,width,0);
   return str;
}

void filereader::setToolTip(QListWidgetItem* item,QString str)
{
    item->setToolTip(str);
}

QString filereader::getNameOfNotes()
{
    return this->NameOfNotes;
}
QString filereader::getNameOfArchive()
{
    return this->NameOfArchive;
}
QString filereader::getNameOfMenu()
{
    return this->NameOfMenu;
}
QString filereader::getFileFormat()
{
    return this->fileFormat;
}
