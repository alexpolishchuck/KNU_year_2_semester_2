#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "QMessageBox"
#include <QFile>
#include <QCloseEvent>
#include "filereader.h"
#include <QTimer>

secondwindow::secondwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondwindow)
{
    historyOperator = new caretaker(this);


    fr = new filereader();

    ui->setupUi(this);
    QListWidget* NotesList = ui->listWidget;
    NotesList->setStyleSheet("QListView {font: 13pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");
//readFromFile( NotesList, NameOfArchive + fileFormat);
fr->readFromFileCheckable(NotesList,fr->getNameOfArchive());
createConnections();
}

secondwindow::~secondwindow()
{
     delete historyOperator;
    delete fr;
    delete ui;

}

void secondwindow::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet(qspressed);

}
void secondwindow::on_pushButton_2_pressed()
{
    ui->pushButton_2->setStyleSheet(qspressed);

}

void secondwindow::on_pushButton_2_released()
{
    ui->pushButton_2->setStyleSheet(qsreleased);
}

void secondwindow::on_pushButton_released()
{
    ui->pushButton->setStyleSheet(qsreleased);
    saveArchive();
    close();
}

void secondwindow::createConnections(){
    QObject::connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(removeChecked(QListWidgetItem*)));
    QObject::connect(ui->pushButton_2, SIGNAL(released()),this,SLOT(removeSelectedItem()));

}

void secondwindow::removeChecked(QListWidgetItem *item){
    if(item->checkState() == Qt::Checked){
        moveToFile(item);
         emit itemIsDeleted(item->text(),ui->listWidget->row(item));
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
        emit itemIsDeleted(item->text(),NotesList->row(item));
    ui->listWidget->removeItemWidget(item);
 delete item;
    }
}
void secondwindow::moveToFile(QListWidgetItem *item)
{
    QFile file (fr->getNameOfNotes() + fr->getFileFormat());
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
         stream << item->text()<<'\n';
    }
}
void secondwindow::saveArchive()
{
    QFile file (fr->getNameOfArchive() + fr->getFileFormat());
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

void secondwindow::addItemNoSignal(QString text, uint _id)
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(text);
    item->setData(Qt::CheckStateRole,0);

    ui->listWidget->insertItem(_id,item);
}

void secondwindow::deleteItemNoSignal(QString text, uint _id)
{

}






