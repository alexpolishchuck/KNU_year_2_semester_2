#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QFile>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QListWidget* NotesList = ui->listWidget;
    NotesList->setStyleSheet("QListView {font: 75 11pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");
    readFromFile(NotesList, "notes");
    NotesList->setContextMenuPolicy(Qt::CustomContextMenu);       //maybe delete

    NotesList = ui->listWidget_2;
    NotesList->setStyleSheet("QListView {font: 75 11pt\"Bodoni MT\";border-style:solid;border-width:2px;border-color: rgb(109, 127, 209);}"
                             "QListView::item{color:rgb(155, 38, 175);}");
     readFromFileNotCheckable(NotesList, "menu");
NotesList->setCurrentItem(NotesList->item(0));
prevIndex = 0;
    createConnections(); //delete?



}
MainWindow::~MainWindow()
{
    delete ui;
}
//styles for buttons
QString qspressed = "font: 11pt\"Bodoni MT\" ;background-color: rgb(109, 127, 209); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";
QString qsreleased = "font: 11pt\"Bodoni MT\" ;background-color: rgb(172, 169, 255); border-radius: 10px; border-bottom-style:solid;border-bottom-width: 5px; border-bottom-color: rgb(109, 127, 209);";
//list of notes

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
    QString line = ui->listWidget_2->currentItem()->text();         //saving notes to the file of the activated list
    line.resize(line.size()-1);
    saveToFile(line,NotesList);



    secwindow = new secondwindow(this);                    //showing archive
    secwindow->setModal(true);
    secwindow->exec();

    NotesList->clear();
    readFromFile(NotesList, line);                    //showing the main list
}
void MainWindow::on_pushButton_4_released()
{


    ui->pushButton_4->setStyleSheet(qsreleased);
    QListWidget* NotesList = ui->listWidget_2;
    QListWidgetItem* item = new QListWidgetItem;



    item->setText("change");
    NotesList->addItem(item);

  item->setFlags(item->flags()|Qt::ItemIsEditable);
  NotesList->editItem(item);
   item->setFlags(item->flags()& ~Qt::ItemIsEditable);




}
void MainWindow::on_pushButton_released()
{
    ui->pushButton->setStyleSheet(qsreleased);

    changeMenuSelectionBack();
    QString line = ui->listWidget_2->currentItem()->text();
    line.resize(line.size()-1);


    saveToFile(line,ui->listWidget);
    saveToFile("menu",ui->listWidget_2);
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
            QString filename = ui->listWidget_2->currentItem()->text().replace("\r","");
            filename.shrink_to_fit();
            saveToFile(filename,ui->listWidget);

            event->accept();
        }
}

void MainWindow::removeLastGroupItem()
{

    QMessageBox::warning(this,"Error", "Group with this name already exists or the name is empty");
    QListWidgetItem* item = ui->listWidget_2->item(ui->listWidget_2->count()-1);
    ui->listWidget_2->removeItemWidget(item);
    delete item;

}
void MainWindow::editNameOfGroup()
{

    QListWidgetItem* item = ui->listWidget_2->item(ui->listWidget_2->count()-1);
    qDebug()<<ui->listWidget_2->count();                        //delete
    QString name = item->text();

    if(name.size()==0)
    {  
        removeLastGroupItem();
    }
    else
    {
    name.replace("_"," ");
    name = name.simplified();
    name.replace(" ","_");
    for(int i=0; i<name.size(); i++)
        if(!name[i].isLetterOrNumber() && name[i]!='_')
        {
            removeLastGroupItem();
           return;
        }
    if(name.size()==0)
    {
          removeLastGroupItem();
          return;
    }
    else
       {
        name.push_back(' ');
        item->setText(name);
        isNameValid();
       }
    }
}

void MainWindow::isNameValid()
{

     QListWidgetItem* item = ui->listWidget_2->item(ui->listWidget_2->count()-1);
     QString name = item->text();
     name.resize(name.size()-1);
    QFile file ("menu.txt");

    if(file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            QString line = file.readLine();
            if(line[line.size()-1]=='\n')
                line.resize(line.size()-2);
            if(!QString::compare(line,name,Qt::CaseSensitivity::CaseSensitive))
            {

                removeLastGroupItem();                      //delete
                return;
            }
        }
    }

    saveToFile("menu",ui->listWidget_2);

}


void MainWindow::deleteFile(QString nameoffile)
{
    nameoffile+=".txt";
    QFile file(nameoffile);
    file.remove();

}
void MainWindow::readFromFile(QListWidget* NotesList, QString nameoffile)
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
        b->setData(Qt::CheckStateRole,0);
        NotesList->addItem(b);
       }
     }
}
void MainWindow::readFromFileNotCheckable(QListWidget* NotesList, QString nameoffile)
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
void MainWindow::saveToFile(QString nameOfFile,QListWidget* NotesList)
{

    nameOfFile+=".txt";

    QFile file (nameOfFile);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        for(int i=0; i<NotesList->count(); i++)
        {
        QListWidgetItem *item = NotesList->item(i);
                    stream << item->text()<<'\n';
        }
        }
}
void MainWindow::saveToArchive(QListWidgetItem *item)
{
    QFile file ("archieve.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
         stream << item->text()<<'\n';
    }
}

void MainWindow::showNotesFromSelectedGroup()
{

    QListWidget*NotesList2 = ui->listWidget_2;
    QListWidget*NotesList = ui->listWidget;

    QString line = NotesList2->item(prevIndex)->text();
    line.resize(line.size()-1);

    saveToFile(line, NotesList);
    prevIndex = NotesList2->currentRow();

    NotesList->clear();

    line = NotesList2->currentItem()->text();
    line.resize(line.size()-1);

    readFromFile(NotesList, line);

}
void MainWindow::on_lineEdit_editingFinished()
{

    QString a = ui->lineEdit->text();
    ui->lineEdit->clear();

    if(a!="" && a.size()<=30)
    {

//QListView* NotesList = ui->listView;
//NotesList->model()->insertRow(NotesList->model()->rowCount());
//int rowindex = NotesList->model()->rowCount()-1;
//NotesList->model()->setData(NotesList->model()->index(rowindex,0),a);    //string
        QListWidget* NotesList = ui->listWidget;
        QListWidgetItem* b = new QListWidgetItem;
        b->setText(a);
        b->setData(Qt::CheckStateRole,0);
        NotesList->addItem(b);

    }
    else
    if(a.size()>30)
    {
        QMessageBox::warning(this,"Error", "You entered more than 30 symbols");
    }
}
void MainWindow::createConnections(){
    QObject::connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(removeChecked(QListWidgetItem*)));
    QObject::connect(ui->pushButton_2, SIGNAL(released()),this,SLOT(removeSelectedItem()));
    QObject::connect(ui->listWidget_2,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showNotesFromSelectedGroup()));

    QObject::connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));//delete

    QListWidget* NotesList = ui->listWidget_2;
    QAbstractItemDelegate* delegate = NotesList->itemDelegate();
    QObject::connect(delegate,SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)),this,SLOT(editNameOfGroup()));


}

void MainWindow::showContextMenu(const QPoint &pos) //delete
{

    QListWidget* NotesList = ui->listWidget;

    QPoint globalPos = NotesList->mapToGlobal(pos);


    QMenu myMenu;
    myMenu.addAction("Copy To Group", this, SLOT(copyToGroup()));
   // myMenu.addAction("Move to Group",this,SLOT(moveToGroup()));


    myMenu.exec(globalPos);
}

void MainWindow::copyToGroup()
{
QListWidget* NotesList = ui->listWidget;
QListWidgetItem* item = NotesList->currentItem();
if(item)
{
    saveToFile("menu",ui->listWidget_2);
   windowog = new windowofgroups(this);
   windowog->receiveData(item->text(),ui->listWidget_2->currentItem()->text());
   windowog->setModal(true);
    windowog->exec();

}
}

//void MainWindow::moveToGroup()
//{
//    QListWidget* NotesList = ui->listWidget;
//    QListWidgetItem* item = NotesList->currentItem();
//    if(item)
//    {
//        saveToFile("menu",ui->listWidget_2);
//       windowog = new windowofgroups(this);
//       windowog->receiveData(item->text(),ui->listWidget_2->currentItem()->text());
//       windowog->setModal(true);
//        windowog->exec();

//    }
//}

void MainWindow::changeMenuSelectionBack()
{
    ui->listWidget_2->setCurrentItem(ui->listWidget_2->item(prevIndex));
}

void MainWindow::removeChecked(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Checked)
    {
        QListWidgetItem * menuitem = ui->listWidget_2->currentItem();
            QString check = menuitem->text().replace("\r","");
            check.shrink_to_fit();
        if(QString::compare(check,"archieve", Qt::CaseInsensitive))
        {
        saveToArchive(item);
        ui->listWidget->removeItemWidget(item);
     delete item;
        }
        else
        {
            QString nameOfFile="notes.txt";

            QFile file (nameOfFile);
            if(file.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                QTextStream stream(&file);
                stream<<item->text()<<'\n';
            }
            ui->listWidget->removeItemWidget(item);
         delete item;

        }
    }
}

void MainWindow::removeSelectedItem()
{
    QListWidget* NotesList = ui->listWidget;
    QListWidgetItem* item = NotesList->currentItem();
    if(item)
    {
    NotesList->removeItemWidget(item);
 delete item;
    }
    else
     {
       QListWidget* NotesList2 = ui->listWidget_2;
        item = NotesList2->currentItem();
        if(item && NotesList2->currentRow()>1)
        {
            QString line = NotesList2->currentItem()->text();
            line.resize(line.size()-1);
            deleteFile(line);
            NotesList->clear();
        NotesList2->removeItemWidget(item);
     delete item;
        NotesList2->setCurrentItem(NotesList2->item(0));
        line = NotesList2->currentItem()->text();
        line.resize(line.size()-1);
        readFromFile(NotesList,line);
        prevIndex = NotesList2->currentRow();
        }
     }
}
