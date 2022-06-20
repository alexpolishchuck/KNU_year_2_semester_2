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

    QListWidget* NotesList = ui->listWidget;
    NotesList->setStyleSheet("QListView {font: 75 11pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");


    readFromFileNotCheckable(NotesList, "menu");
}
QString line;
QString curMenu;
QString qspressed3 = "font: 11pt\"Bodoni MT\" ;background-color: rgb(109, 127, 209); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";
QString qsreleased3 = "font: 11pt\"Bodoni MT\" ;background-color: rgb(172, 169, 255); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";
windowofgroups::~windowofgroups()
{
    delete ui;
}


void windowofgroups::readFromFileNotCheckable(QListWidget* NotesList, QString nameoffile)
{

    nameoffile+=".txt";
    QFile file (nameoffile);
    if(file.open(QIODevice::ReadOnly))
    {

       while(!file.atEnd())
       {
        QString line = file.readLine();
        if(line[line.size()-1]=='\n')
            line.resize(line.size()-1);

        QListWidgetItem* b = new QListWidgetItem;
        b->setText(line);
        NotesList->addItem(b);
       }
     }
}
void windowofgroups::receiveData(QString a, QString curInMenu)
{
    line = a;
    curMenu = curInMenu;
}
void windowofgroups::on_pushButton_released()
{
     ui->pushButton->setStyleSheet(qsreleased3);
     QListWidget* NotesList = ui->listWidget;
     QListWidgetItem* item = NotesList->currentItem();
     if(item && item->text()!=curMenu)
     {
         QString nameoffile = item->text();
         nameoffile.resize(nameoffile.size()-1);

        addtofile(nameoffile);
     }
     close();
}


void windowofgroups::on_pushButton_pressed()
{
     ui->pushButton->setStyleSheet(qspressed3);
}

void windowofgroups::addtofile(QString nameoffile)
{

    nameoffile+=".txt";

    QFile file (nameoffile);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
                    stream <<line<<'\n';
    }

}
