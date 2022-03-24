#include "windowofgroups.h"
#include "ui_windowofgroups.h"
#include "QMessageBox"
#include <QFile>
#include "mainwindow.h"
windowofgroups::windowofgroups(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::windowofgroups)
{
    ui->setupUi(this);


    fr = new filereader(fr->getNameOfNotes(),fr->getNameOfArchive(),fr->getNameOfMenu(),fr->getFileFormat());

    QListWidget* NotesList = ui->listWidget;
    NotesList->setStyleSheet("QListView {font:  16pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");



    fr->readFromFileNotCheckable(NotesList,fr->getNameOfMenu());
}

windowofgroups::~windowofgroups()
{
    delete fr;
    delete ui;
}

void windowofgroups::receiveData(QString a, QString curInMenu)
{
    line = a;
    curMenu = curInMenu;
}
void windowofgroups::receiveData(QString a, QString curInMenu,bool* b)
{

    line = a;
    isadded = b;
    curMenu = curInMenu;
}
void windowofgroups::on_pushButton_released()
{
     ui->pushButton->setStyleSheet(qsreleased);
     QListWidget* NotesList = ui->listWidget;
     QListWidgetItem* item = NotesList->currentItem();
     if(item && item->toolTip()!=curMenu)
     {
         QString nameoffile = item->toolTip();

        addtofile(nameoffile);

        if(isadded != nullptr)
            *isadded = true;
     }else if(isadded!=nullptr)
         *isadded = false;
     close();
}


void windowofgroups::on_pushButton_pressed()
{
     ui->pushButton->setStyleSheet(qspressed);
}

void windowofgroups::addtofile(QString nameoffile)
{

    nameoffile+=".txt";

    QFile file (nameoffile);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
                    stream <<line<<'\n';

        file.close();
    }

}


