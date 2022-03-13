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
    NotesList->setStyleSheet("QListView {font: 13pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");
readFromFile( NotesList, NameOfArchive + fileFormat);
createConnections();
}

secondwindow::~secondwindow()
{
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
void secondwindow::on_pushButton_3_pressed()
{
    ui->pushButton_3->setStyleSheet(qspressed);

}
void secondwindow::on_pushButton_4_pressed()
{
    ui->pushButton_4->setStyleSheet(qspressed);
}
void secondwindow::on_pushButton_2_released()
{
    ui->pushButton_2->setStyleSheet(qsreleased);
}
void secondwindow::on_pushButton_3_released()
{
    ui->pushButton_3->setStyleSheet(qsreleased);
}
void secondwindow::on_pushButton_4_released()
{
    ui->pushButton_4->setStyleSheet(qsreleased);

    QString a = "abcd";
    QString b = "AbCd";
    QString c = "abc";
    qDebug() << QString::compare(a,b,Qt::CaseSensitivity::CaseSensitive);
    qDebug()<<QString::compare(a,c,Qt::CaseSensitivity::CaseSensitive);
     qDebug()<<QString::compare(a,b,Qt::CaseSensitivity::CaseInsensitive);
}
void secondwindow::on_pushButton_released()
{
    ui->pushButton->setStyleSheet(qsreleased);
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
    QFile file (NameOfNotes + fileFormat);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
         stream << item->text()<<'\n';
    }
}
void secondwindow::saveArchive()
{
    QFile file (NameOfArchive + fileFormat);
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
