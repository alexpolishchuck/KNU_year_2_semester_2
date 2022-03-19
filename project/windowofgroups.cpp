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
    NotesList->setStyleSheet("QListView {font:  16pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");


    readFromFileNotCheckable(NotesList, "menu");
}

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
        int width = NotesList->width()/2;
        QString shortline = QFontMetrics(NotesList->font()).elidedText(line,Qt::ElideRight,width,0);
         b->setText(shortline);
         b->setToolTip(line);
        NotesList->addItem(b);
       }
     }
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
         //nameoffile.resize(nameoffile.size()-1);                              //why???

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

//void windowofgroups::closeEvent(QCloseEvent *event)
//{
//    QMessageBox::StandardButton resBtn = QMessageBox::question( this,"Exit",
//                                                                 tr("Do you want exit?"),
//                                                                 QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
//                                                                 QMessageBox::Yes);
//        if (resBtn == QMessageBox::Cancel)
//        {
//            event->ignore();
//        }
//        else if(resBtn == QMessageBox::No)
//        {
//            event->ignore();
//        }
//        else {
//            event->accept();
//        }
//}
