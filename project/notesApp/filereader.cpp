#include "filereader.h"
#include <QString>
#include <QFile>
#include <QIODevice>
initfilereader::  initfilereader(QString notes,QString archive,QString menu, QString file):NameOfNotes(notes),NameOfArchive(archive),NameOfMenu(menu),fileFormat(file)
{

}

void initfilereader::readFromFile( QListWidget* NotesList, QString nameoffile)
{
        nameoffile+=this->fileFormat;
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
            this->setcheckable(item);
            NotesList->addItem(item);
           }
           file.close();
         }
}

void readerofnotes::saveToFile(QString nameOfFile,QListWidget* NotesList)
{

    nameOfFile+=this->fileFormat;

    QFile file (nameOfFile);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        for(int i=0; i<NotesList->count(); i++)
        {
        QListWidgetItem *item = NotesList->item(i);
                    if(!item->toolTip().size())
                    stream << item->text()<<'\n';
                    else
                        stream << item->toolTip()<<'\n';
        }
        file.close();
        }
}


void readerofnotes::saveItem(QListWidgetItem *item, QString nameoffile)
{
    QFile file (nameoffile + this->fileFormat);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
         stream << item->text()<<'\n';
         file.close();
    }

}

void readerofgroups::saveToFile(QString nameOfFile,QListWidget* NotesList)
{

    nameOfFile+=this->fileFormat;

    QFile file (nameOfFile);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        for(int i=0; i<NotesList->count(); i++)
        {
        QListWidgetItem *item = NotesList->item(i);
                    if(!item->toolTip().size())
                    stream << item->text()<<'\n';
                    else
                        stream << item->toolTip()<<'\n';
        }
        file.close();
        }
}


void readerofgroups::saveItem(QListWidgetItem *item, QString nameoffile)
{
    QFile file (nameoffile + this->fileFormat);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
         stream << item->text()<<'\n';
         file.close();
    }

}
