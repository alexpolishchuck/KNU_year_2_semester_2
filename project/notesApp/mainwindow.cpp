#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QFile>
#include <QCloseEvent>
#include <editinghistory.h>
#include <QShortcut>
#include "filereader.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    historyOperator = new caretaker(this);

    gfr = new readerofgroups();
    nfr = new readerofnotes();
    createfiles();


    QListWidget* NotesList = ui->listofnotes;
    NotesList->setStyleSheet("QListView {font: 13pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");

   // readFromFile(NotesList, "notes");
    nfr->readFromFile( NotesList,nfr->getNameOfNotes());
    NotesList->setContextMenuPolicy(Qt::CustomContextMenu);

    NotesList = ui->listofgroups;

    NotesList->setStyleSheet("QListView {font: 16pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                           "QListView::item{color:rgb(155, 38, 175); ;}");

    // readFromFileNotCheckable(NotesList, "menu");
    gfr->readFromFile(NotesList,gfr->getNameOfMenu());
    NotesList->setCurrentItem(NotesList->item(0));

    prevIndex = 0;

    createConnections();



}
MainWindow::~MainWindow()
{
    delete historyOperator;
    delete nfr;
    delete gfr;
    delete ui;
}


void MainWindow::createfiles()
{
    QFile f1(gfr->getNameOfMenu() + gfr->getFileFormat());
    if(!f1.exists()){
        f1.open(QIODevice::WriteOnly);
        f1.close();
        QListWidgetItem item;
        item.setText(gfr->getNameOfNotes());
        saveItem(&item,gfr->getNameOfMenu());
        item.setText(gfr->getNameOfArchive());
        saveItem(&item,gfr->getNameOfMenu());


    }
}
void MainWindow::on_exit_button_pressed()
{
    ui->exit_button->setStyleSheet(qspressed);
}
void MainWindow::on_delete_button_pressed()
{
    ui->delete_button->setStyleSheet(qspressed);

}
void MainWindow::on_archive_button_pressed()
{
    ui->archive_button->setStyleSheet(qspressed);
}
void MainWindow::on_add_group_button_pressed()
{
    ui->add_group_button->setStyleSheet(qspressed);
}
void MainWindow::on_delete_button_released()
{
    ui->delete_button->setStyleSheet(qsreleased);
}
void MainWindow::on_archive_button_released()
{
    QListWidget* NotesList = ui->listofnotes;
    ui->archive_button->setStyleSheet(qsreleased);

    changeMenuSelectionBack();
    QString line = ui->listofgroups->currentItem()->toolTip();         //saving notes to the file of the activated list
    saveToFile(line,NotesList);



    secwindow = new archivewindow(this);
    secwindow->setModal(true);
    secwindow->exec();
    emit anotherWindowIsClosed();
    NotesList->clear();
    nfr->readFromFile(NotesList,line);
}
void MainWindow::on_add_group_button_released()
{


    ui->add_group_button->setStyleSheet(qsreleased);
    QListWidget* NotesList = ui->listofgroups;
    QListWidgetItem* item = new QListWidgetItem;



    item->setText(this->initgroupname);
    NotesList->addItem(item);

  item->setFlags(item->flags()|Qt::ItemIsEditable);
  item->setFont(NotesList->font());
  NotesList->editItem(item);
  item->setFlags(item->flags()& ~Qt::ItemIsEditable);




}
void MainWindow::on_exit_button_released()
{
    ui->exit_button->setStyleSheet(qsreleased);

    changeMenuSelectionBack();
    QString line = ui->listofgroups->currentItem()->toolTip();


    saveToFile(gfr->getNameOfMenu(),ui->listofgroups);
    QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,"Exit",
                                                                 tr("Do you want to save current\n group of notes?\n"),
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
            QString filename = ui->listofgroups->currentItem()->toolTip().replace("\r","");
            filename.shrink_to_fit();
            saveToFile(filename,ui->listofnotes);

            event->accept();
        }
}

void MainWindow::removeLastGroupItem()
{

    QMessageBox::warning(this,"Error", this->nameoferrors[0]);
    QListWidgetItem* item = ui->listofgroups->item(ui->listofgroups->count()-1);
    deleteItem(item,ui->listofgroups);

}
void MainWindow::editNameOfGroup()
{

    QListWidgetItem* item = ui->listofgroups->item(ui->listofgroups->count()-1);

    QString name = item->text();
    name = name.trimmed();
    if(name.size()==0)
    {  
        removeLastGroupItem();
    }
    else
    {
    for(int i=0; i<name.size(); i++)
        if(name[i] == '\\' || name[i] =='/' || name[i] ==':' || name[i] =='?' || name[i] =='"' || name[i] =='>' || name[i] =='<' || name[i] =='|')
        {
            removeLastGroupItem();
           return;
        }


    int width = ui->listofgroups->width()/2;
    QString shortname = QFontMetrics(ui->listofgroups->font()).elidedText(name,Qt::ElideRight,width,0);
    item->setText(shortname);
    item->setToolTip(name);
    isNameValid();



    }
}

void MainWindow::isNameValid()
{

     QListWidgetItem* item = ui->listofgroups->item(ui->listofgroups->count()-1);

     int count = ui->listofgroups->count()-1;
     for(int i=0; i<count; i++)
     {

         if(!QString::compare(ui->listofgroups->item(i)->toolTip(),item->toolTip(),Qt::CaseSensitivity::CaseSensitive))
         {
             removeLastGroupItem();
             return;
         }
     }
             saveToFile(gfr->getNameOfMenu(),ui->listofgroups);

}


void MainWindow::deleteFile(QString nameoffile)
{
    nameoffile+=gfr->getFileFormat();
    QFile file(nameoffile);
    file.remove();

}


void MainWindow::saveToFile(QString nameOfFile,QListWidget* NotesList)
{

    nameOfFile+=gfr->getFileFormat();

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


void MainWindow::saveItem(QListWidgetItem *item, QString nameoffile)
{
    QFile file (nameoffile + gfr->getFileFormat());
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
         stream << item->text()<<'\n';
         file.close();
    }

}

void MainWindow::deleteItem(QListWidgetItem *item, QListWidget* NotesList)
{
    NotesList->removeItemWidget(item);
    if(NotesList == ui->listofnotes)
    emit  itemIsDeleted(item->text(), NotesList->row(item));
    delete item;

}
void MainWindow::deleteItemNoSignal(QString text, uint _id)
{

   QListWidgetItem * item = ui->listofnotes->item(_id);
   ui->listofnotes->removeItemWidget(item);
   delete item;

}

void MainWindow::addItemNoSignal(QString text, uint _id)
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(text);
    item->setData(Qt::CheckStateRole,0);

    ui->listofnotes->insertItem(_id,item);
}

void MainWindow::showNotesFromSelectedGroup()
{

    QListWidget*NotesList2 = ui->listofgroups;
    QListWidget*NotesList = ui->listofnotes;

    QString line = NotesList2->item(prevIndex)->toolTip();


    saveToFile(line, NotesList);
    prevIndex = NotesList2->currentRow();

    NotesList->clear();

    recreateHistoryOperator();


    line = NotesList2->currentItem()->toolTip();

    //readFromFile(NotesList, line);
    nfr->readFromFile(NotesList,line);

}
void MainWindow::on_lineEdit_editingFinished()
{

    QString a = ui->lineEdit->text();
    ui->lineEdit->clear();

    if(a!="" && a.size()<=30)
    {

        QListWidget* NotesList = ui->listofnotes;
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(a);
        item->setData(Qt::CheckStateRole,0);

        NotesList->addItem(item);
        emit itemIsAdded(item->text(),NotesList->row(item));
    }
    else
    if(a.size()>letterlimit)
    {
        QString error =this->nameoferrors[1];
        QMessageBox::warning(this,"Error", error);
    }
}
void MainWindow::createConnections()
{
    QObject::connect(ui->listofnotes, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(removeChecked(QListWidgetItem*)));

    QObject::connect(ui->delete_button, SIGNAL(released()),this,SLOT(removeSelectedItem()));

    QObject::connect(ui->listofgroups,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showNotesFromSelectedGroup()));

    QObject::connect(ui->listofnotes, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    QObject::connect(this, SIGNAL(anotherWindowIsClosed()),this,SLOT(recreateHistoryOperator()));

    QListWidget* NotesList = ui->listofgroups;
    QAbstractItemDelegate* delegate = NotesList->itemDelegate();
    QObject::connect(delegate,SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)),this,SLOT(editNameOfGroup()));

}

void MainWindow::showContextMenu(const QPoint &pos)
{

    QListWidget* NotesList = ui->listofnotes;

    QPoint globalPos = NotesList->mapToGlobal(pos);


    QMenu myMenu;
    myMenu.addAction("Copy To Group", this, SLOT(copyToGroup()));
    myMenu.addAction("Move to Group",this,SLOT(moveToGroup()));


    myMenu.exec(globalPos);
}

void MainWindow::copyToGroup()
{
QListWidget* NotesList = ui->listofnotes;
QListWidgetItem* item = NotesList->currentItem();
if(item)
{
    saveToFile(gfr->getNameOfMenu(),ui->listofgroups);
   windowog = new windowofgroups(this);
   windowog->receiveData(item->text(),ui->listofgroups->currentItem()->toolTip());
   windowog->setModal(true);
    windowog->exec();
    //delete windowog;
 emit anotherWindowIsClosed();
}
}

void MainWindow::moveToGroup()
{
    QListWidget* NotesList = ui->listofnotes;
    QListWidgetItem* item = NotesList->currentItem();
    if(item)
    {
        saveToFile(gfr->getNameOfMenu(),ui->listofgroups);
       windowog = new windowofgroups(this);
       bool isadded = false;
       windowog->receiveData(item->text(),ui->listofgroups->currentItem()->toolTip(), &isadded);
       windowog->setModal(true);
       windowog->exec();
      emit anotherWindowIsClosed();
      // delete windowog;

       if(isadded)
           removeSelectedItem(NotesList);
    }
}

void MainWindow::changeMenuSelectionBack()
{
    ui->listofgroups->setCurrentItem(ui->listofgroups->item(prevIndex));
}

void MainWindow::removeChecked(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Checked)
    {
        QListWidgetItem * menuitem = ui->listofgroups->currentItem();
            QString check = menuitem->toolTip().replace("\r","");
            check.shrink_to_fit();
        if(QString::compare(check,gfr->getNameOfArchive(), Qt::CaseInsensitive))
        {
        saveItem(item, gfr->getNameOfArchive());
        deleteItem(item, ui->listofnotes);
        }
        else
        {
            saveItem(item,gfr->getNameOfNotes());
            deleteItem(item, ui->listofnotes);
        }
    }
}
void MainWindow::removeSelectedItem(QListWidget*NotesList )
{
    QListWidgetItem* item = NotesList->currentItem();
    if(item)
    {

            deleteItem(item,NotesList);
    }
}
void MainWindow::removeSelectedItem()
{
    QListWidget* NotesList = ui->listofnotes;
    QListWidgetItem* item = NotesList->currentItem();
    if(item)
    {

     deleteItem(item,NotesList);
    }
    else
     {
       QListWidget* NotesList2 = ui->listofgroups;
        item = NotesList2->currentItem();
        if(item && NotesList2->currentRow()>1)
        {
            QString line = NotesList2->currentItem()->toolTip();

            deleteFile(line);
            NotesList->clear();

         deleteItem(item,NotesList2);

        NotesList2->setCurrentItem(NotesList2->item(0));
        line = NotesList2->currentItem()->toolTip();
        nfr->readFromFile(NotesList,line);
        prevIndex = NotesList2->currentRow();


        }
     }
}

void MainWindow::recreateHistoryOperator()
{
    delete historyOperator;
    historyOperator = new caretaker(this);
}
