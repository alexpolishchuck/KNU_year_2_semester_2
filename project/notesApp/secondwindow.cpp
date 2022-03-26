#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "QMessageBox"
#include <QFile>
#include <QCloseEvent>
secondwindow::secondwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondwindow)
{
    ui->setupUi(this);
    QListWidget* NotesList = ui->listWidget;
    NotesList->setStyleSheet("QListView {font: 75 11pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");
readFromFile( NotesList, "archieve.txt");
createConnections();
}

secondwindow::~secondwindow()
{
    delete ui;
}
QString qspressed1 = "font: 11pt\"Bodoni MT\" ;background-color: rgb(109, 127, 209); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";
QString qsreleased1 = "font: 11pt\"Bodoni MT\" ;background-color: rgb(172, 169, 255); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";

void secondwindow::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet(qspressed1);

}
void secondwindow::on_pushButton_2_pressed()
{
    ui->pushButton_2->setStyleSheet(qspressed1);

}
void secondwindow::on_pushButton_3_pressed()
{
    ui->pushButton_3->setStyleSheet(qspressed1);

}
void secondwindow::on_pushButton_4_pressed()
{
    ui->pushButton_4->setStyleSheet(qspressed1);
}
void secondwindow::on_pushButton_2_released()
{
    ui->pushButton_2->setStyleSheet(qsreleased1);
}
void secondwindow::on_pushButton_3_released()
{
    ui->pushButton_3->setStyleSheet(qsreleased1);
}
void secondwindow::on_pushButton_4_released()
{
    ui->pushButton_4->setStyleSheet(qsreleased1);
}
void secondwindow::on_pushButton_released()
{
    ui->pushButton->setStyleSheet(qsreleased1);
    saveArchive();
    close();
}

void secondwindow::readFromFile(QListWidget* NotesList, QString nameoffile)
{
    QFile file (nameoffile);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
       while(!file.atEnd())
       {
        QString line = file.readLine();
        if(line[line.size()-1]=='\n')
            line.resize(line.size()-1);

        QListWidgetItem* b = new QListWidgetItem;
        b->setText(line);
        b->setData(Qt::CheckStateRole,0);
        NotesList->addItem(b);
       }
     }
}

void secondwindow::createConnections(){
    QObject::connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(removeChecked(QListWidgetItem*)));
    QObject::connect(ui->pushButton_2, SIGNAL(released()),this,SLOT(removeSelectedItem()));

}

void secondwindow::removeChecked(QListWidgetItem *item){
    if(item->checkState() == Qt::Checked){
        moveToFile(item);
        ui->listWidget->removeItemWidget(item);
     delete item;
    }
}
void secondwindow::removeSelectedItem()
{
    QListWidget* NotesList = ui->listWidget;
    QListWidgetItem* item = NotesList->currentItem();
    if(item)
    {
    ui->listWidget->removeItemWidget(item);
 delete item;
    }
}
void secondwindow::moveToFile(QListWidgetItem *item)
{
    QFile file ("notes.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
         stream << item->text()<<'\n';
    }
}
void secondwindow::saveArchive()
{
    QFile file ("archieve.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        for(int i=0; i<ui->listWidget->count(); i++)
        {
        QListWidgetItem *item = ui->listWidget->item(i);
                    stream << item->text()<<'\n';
        }
        }
}

void secondwindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,"Exit",
                                                                    tr("Do you want to save archive?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn == QMessageBox::Cancel)
        {
            event->ignore();
        }
        else if(resBtn == QMessageBox::No)
        {
            event->accept();
        }
        else {
            saveArchive();

            event->accept();
        }
}
