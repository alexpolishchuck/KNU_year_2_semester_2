#include "archivewindow.h"
#include "ui_archivewindow.h"
#include "QMessageBox"
#include <QFile>
#include <QCloseEvent>
#include "filereader.h"
#include <QTimer>



archivewindow::archivewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::archivewindow)
{
    historyOperator = new caretaker(this);


    nfr = new readerofnotes();

    ui->setupUi(this);
    QListWidget* NotesList = ui->listofnotes;
    NotesList->setStyleSheet("QListView {font: 13pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");
//readFromFile( NotesList, NameOfArchive + fileFormat);
nfr->readFromFile(NotesList,nfr->getNameOfArchive());
createConnections();
}

archivewindow::~archivewindow()
{
     delete historyOperator;
    delete nfr;
    delete ui;

}

void archivewindow::on_exit_button_pressed()
{
    ui->exit_button->setStyleSheet(qspressed);

}
void archivewindow::on_delete_button_pressed()
{
    ui->delete_button->setStyleSheet(qspressed);

}

void archivewindow::on_delete_button_released()
{
    ui->delete_button->setStyleSheet(qsreleased);
}

void archivewindow::on_exit_button_released()
{
    ui->exit_button->setStyleSheet(qsreleased);
    saveArchive();
    close();
}

void archivewindow::createConnections(){
    QObject::connect(ui->listofnotes, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(removeChecked(QListWidgetItem*)));
    QObject::connect(ui->delete_button, SIGNAL(released()),this,SLOT(removeSelectedItem()));

}

void archivewindow::removeChecked(QListWidgetItem *item){
    if(item->checkState() == Qt::Checked){
        moveToFile(item);
         emit itemIsDeleted(item->text(),ui->listofnotes->row(item));
        ui->listofnotes->removeItemWidget(item);
     delete item;
    }
}
void archivewindow::removeSelectedItem()
{
    QListWidget* NotesList = ui->listofnotes;
    QListWidgetItem* item = NotesList->currentItem();
    if(item)
    {
        emit itemIsDeleted(item->text(),NotesList->row(item));
    ui->listofnotes->removeItemWidget(item);
 delete item;
    }
}
void archivewindow::moveToFile(QListWidgetItem *item)
{
    QFile file (nfr->getNameOfNotes() + nfr->getFileFormat());
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
         stream << item->text()<<'\n';
    }
}
void archivewindow::saveArchive()
{
    QFile file (nfr->getNameOfArchive() + nfr->getFileFormat());
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        for(int i=0; i<ui->listofnotes->count(); i++)
        {
        QListWidgetItem *item = ui->listofnotes->item(i);
                    stream << item->text()<<'\n';
        }
        }
}

void archivewindow::closeEvent(QCloseEvent *event)
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

void archivewindow::addItemNoSignal(QString text, uint _id)
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(text);
    item->setData(Qt::CheckStateRole,0);

    ui->listofnotes->insertItem(_id,item);
}

//void archivewindow::deleteItemNoSignal(QString text, uint _id)
//{

//}






