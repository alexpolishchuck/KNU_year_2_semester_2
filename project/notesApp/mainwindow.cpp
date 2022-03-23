#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QFile>
#include <QCloseEvent>
//#include "editinghistory.h"
#include <editinghistory.h>
#include <QShortcut>
#include "filereader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    historyOperator = new caretaker(this);

    fr = new filereader(NameOfNotes,NameOfArchive,NameOfMenu,fileFormat);

    createfiles();


    QListWidget* NotesList = ui->listWidget;
    NotesList->setStyleSheet("QListView {font: 13pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");

   // readFromFile(NotesList, "notes");
    fr->readFromFileCheckable(NotesList,NameOfNotes);
    NotesList->setContextMenuPolicy(Qt::CustomContextMenu);

    NotesList = ui->listWidget_2;

    NotesList->setStyleSheet("QListView {font: 16pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                           "QListView::item{color:rgb(155, 38, 175); ;}");

    // readFromFileNotCheckable(NotesList, "menu");
    fr->readFromFileNotCheckable(NotesList,NameOfMenu);
    NotesList->setCurrentItem(NotesList->item(0));

    prevIndex = 0;

    createConnections();



}
MainWindow::~MainWindow()
{
    delete historyOperator;
    delete ui;
}


void MainWindow::createfiles()
{
    QFile f1(this->NameOfMenu + fileFormat);
    if(!f1.exists()){
        f1.open(QIODevice::WriteOnly);
        f1.close();
        QListWidgetItem item;
        item.setText(NameOfNotes);
        saveItem(&item,NameOfMenu);
        item.setText(NameOfArchive);
        saveItem(&item,NameOfMenu);


    }
}
void MainWindow::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet(qspressed);
}
void MainWindow::on_pushButton_2_pressed()
{
    ui->pushButton_2->setStyleSheet(qspressed);

}
void MainWindow::on_pushButton_3_pressed()
{
    ui->pushButton_3->setStyleSheet(qspressed);
}
void MainWindow::on_pushButton_4_pressed()
{
    ui->pushButton_4->setStyleSheet(qspressed);
}
void MainWindow::on_pushButton_2_released()
{
    ui->pushButton_2->setStyleSheet(qsreleased); 
}
void MainWindow::on_pushButton_3_released()
{
    QListWidget* NotesList = ui->listWidget;
    ui->pushButton_3->setStyleSheet(qsreleased);

    changeMenuSelectionBack();
    QString line = ui->listWidget_2->currentItem()->toolTip();         //saving notes to the file of the activated list
    saveToFile(line,NotesList);



    secwindow = new secondwindow(this);                    //showing archive
    secwindow->setModal(true);
    secwindow->exec();
    //delete secwindow;
    emit anotherWindowIsClosed();
    NotesList->clear();
    //readFromFile(NotesList, line);                    //showing the main list
    fr->readFromFileCheckable(NotesList,line);
}
void MainWindow::on_pushButton_4_released()
{


    ui->pushButton_4->setStyleSheet(qsreleased);
    QListWidget* NotesList = ui->listWidget_2;
    QListWidgetItem* item = new QListWidgetItem;



    item->setText("change");
    NotesList->addItem(item);

  item->setFlags(item->flags()|Qt::ItemIsEditable);
  item->setFont(NotesList->font());
  NotesList->editItem(item);
  item->setFlags(item->flags()& ~Qt::ItemIsEditable);




}
void MainWindow::on_pushButton_released()
{
    ui->pushButton->setStyleSheet(qsreleased);

    changeMenuSelectionBack();
    QString line = ui->listWidget_2->currentItem()->toolTip();

   // saveToFile(line,ui->listWidget);
    saveToFile(NameOfMenu,ui->listWidget_2);
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
            QString filename = ui->listWidget_2->currentItem()->toolTip().replace("\r","");
            filename.shrink_to_fit();
            saveToFile(filename,ui->listWidget);

            event->accept();
        }
}

void MainWindow::removeLastGroupItem()
{

    QMessageBox::warning(this,"Error", "Group with this name already exists or the name is empty");
    QListWidgetItem* item = ui->listWidget_2->item(ui->listWidget_2->count()-1);
    deleteItem(item,ui->listWidget_2);

}
void MainWindow::editNameOfGroup()
{

    QListWidgetItem* item = ui->listWidget_2->item(ui->listWidget_2->count()-1);

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


    int width = ui->listWidget_2->width()/2;
    QString shortname = QFontMetrics(ui->listWidget_2->font()).elidedText(name,Qt::ElideRight,width,0);
    item->setText(shortname);
    item->setToolTip(name);
    isNameValid();



    }
}

void MainWindow::isNameValid()
{

     QListWidgetItem* item = ui->listWidget_2->item(ui->listWidget_2->count()-1);

     int count = ui->listWidget_2->count()-1;
     for(int i=0; i<count; i++)
     {

         if(!QString::compare(ui->listWidget_2->item(i)->toolTip(),item->toolTip(),Qt::CaseSensitivity::CaseSensitive))
         {
             removeLastGroupItem();
             return;
         }
     }
             saveToFile(NameOfMenu,ui->listWidget_2);

}


void MainWindow::deleteFile(QString nameoffile)
{
    nameoffile+=fileFormat;
    QFile file(nameoffile);
    file.remove();

}


void MainWindow::saveToFile(QString nameOfFile,QListWidget* NotesList)
{

    nameOfFile+=fileFormat;

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
    QFile file (nameoffile + fileFormat);
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
    if(NotesList == ui->listWidget)
    emit  itemIsDeleted(item->text(), NotesList->row(item));
    delete item;

}
void MainWindow::deleteItemNoSignal(QString text, uint _id)
{

   QListWidgetItem * item = ui->listWidget->item(_id);
   ui->listWidget->removeItemWidget(item);
   delete item;

}

void MainWindow::addItemNoSignal(QString text, uint _id)
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(text);
    item->setData(Qt::CheckStateRole,0);

    ui->listWidget->insertItem(_id,item);
}

void MainWindow::showNotesFromSelectedGroup()
{

    QListWidget*NotesList2 = ui->listWidget_2;
    QListWidget*NotesList = ui->listWidget;

    QString line = NotesList2->item(prevIndex)->toolTip();


    saveToFile(line, NotesList);
    prevIndex = NotesList2->currentRow();

    NotesList->clear();

    delete historyOperator;
    historyOperator = new caretaker(this);


    line = NotesList2->currentItem()->toolTip();

    //readFromFile(NotesList, line);
    fr->readFromFileCheckable(NotesList,line);

}
void MainWindow::on_lineEdit_editingFinished()
{

    QString a = ui->lineEdit->text();
    ui->lineEdit->clear();

    if(a!="" && a.size()<=30)
    {

        QListWidget* NotesList = ui->listWidget;
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(a);
        item->setData(Qt::CheckStateRole,0);

        NotesList->addItem(item);
        emit itemIsAdded(item->text(),NotesList->row(item));
    }
    else
    if(a.size()>letterlimit)
    {
        QMessageBox::warning(this,"Error", "You entered more than 30 symbols");
    }
}
void MainWindow::createConnections()
{
    QObject::connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(removeChecked(QListWidgetItem*)));

    QObject::connect(ui->pushButton_2, SIGNAL(released()),this,SLOT(removeSelectedItem()));

    QObject::connect(ui->listWidget_2,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showNotesFromSelectedGroup()));

    QObject::connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    QObject::connect(this, SIGNAL(anotherWindowIsClosed()),this,SLOT(recreateHistoryOperator()));

    QListWidget* NotesList = ui->listWidget_2;
    QAbstractItemDelegate* delegate = NotesList->itemDelegate();
    QObject::connect(delegate,SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)),this,SLOT(editNameOfGroup()));

}

void MainWindow::showContextMenu(const QPoint &pos)
{

    QListWidget* NotesList = ui->listWidget;

    QPoint globalPos = NotesList->mapToGlobal(pos);


    QMenu myMenu;
    myMenu.addAction("Copy To Group", this, SLOT(copyToGroup()));
    myMenu.addAction("Move to Group",this,SLOT(moveToGroup()));


    myMenu.exec(globalPos);
}

void MainWindow::copyToGroup()
{
QListWidget* NotesList = ui->listWidget;
QListWidgetItem* item = NotesList->currentItem();
if(item)
{
    saveToFile(NameOfMenu,ui->listWidget_2);
   windowog = new windowofgroups(this);
   windowog->receiveData(item->text(),ui->listWidget_2->currentItem()->toolTip());
   windowog->setModal(true);
    windowog->exec();
    //delete windowog;
 emit anotherWindowIsClosed();
}
}

void MainWindow::moveToGroup()
{
    QListWidget* NotesList = ui->listWidget;
    QListWidgetItem* item = NotesList->currentItem();
    if(item)
    {
        saveToFile(NameOfMenu,ui->listWidget_2);
       windowog = new windowofgroups(this);
       bool isadded = false;
       windowog->receiveData(item->text(),ui->listWidget_2->currentItem()->toolTip(), &isadded);
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
    ui->listWidget_2->setCurrentItem(ui->listWidget_2->item(prevIndex));
}

void MainWindow::removeChecked(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Checked)
    {
        QListWidgetItem * menuitem = ui->listWidget_2->currentItem();
            QString check = menuitem->toolTip().replace("\r","");
            check.shrink_to_fit();
        if(QString::compare(check,NameOfArchive, Qt::CaseInsensitive))
        {
        saveItem(item, NameOfArchive);
        deleteItem(item, ui->listWidget);
        }
        else
        {
            saveItem(item,NameOfNotes);
            deleteItem(item, ui->listWidget);
        }
    }
}
void MainWindow::removeSelectedItem(QListWidget*NotesList )
{
    QListWidgetItem* item = NotesList->currentItem();
    if(item)
    {
//    NotesList->removeItemWidget(item);
// delete item;

            deleteItem(item,NotesList);
    }
}
void MainWindow::removeSelectedItem()
{
    QListWidget* NotesList = ui->listWidget;
    QListWidgetItem* item = NotesList->currentItem();
    if(item)
    {
//    NotesList->removeItemWidget(item);
// delete item;
     deleteItem(item,NotesList);
    }
    else
     {
       QListWidget* NotesList2 = ui->listWidget_2;
        item = NotesList2->currentItem();
        if(item && NotesList2->currentRow()>1)
        {
            QString line = NotesList2->currentItem()->toolTip();

            deleteFile(line);
            NotesList->clear();

//        NotesList2->removeItemWidget(item);
//     delete item;
         deleteItem(item,NotesList2);

        NotesList2->setCurrentItem(NotesList2->item(0));
        line = NotesList2->currentItem()->toolTip();
       // readFromFile(NotesList,line);
        fr->readFromFileCheckable(NotesList,line);
        prevIndex = NotesList2->currentRow();


        }
     }
}

void MainWindow::recreateHistoryOperator()
{
    delete historyOperator;
    historyOperator = new caretaker(this);
}