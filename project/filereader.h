#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QString>
class filereader
{
public:
    filereader(QString notes,QString archive,QString menu, QString file);
    filereader(){};
    virtual ~filereader(){};
     void readFromFileCheckable( QListWidget*, QString);

     virtual QString makeshort(QListWidget* NotesList,QString str);

     virtual void setToolTip(QListWidgetItem* item, QString str);

     void readFromFileNotCheckable( QListWidget*, QString);

     virtual void setcheckable(QListWidgetItem* item);

     QString getNameOfNotes();
     QString getNameOfArchive();
     QString getNameOfMenu();
     QString getFileFormat();
protected:
     QString const NameOfNotes ="notes";
     QString const NameOfArchive="archive";
     QString const NameOfMenu = "menu";
     QString const fileFormat = ".txt";
};

#endif // FILEREADER_H
