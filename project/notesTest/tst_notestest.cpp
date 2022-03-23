
#include <QtTest>
#include <QCoreApplication>
#include <QWidget>
#include "editinghistory.h"
#include <C:\Qt\labs\lab1\mainwindow.h>
#include <QObjectList>
#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include "ui_mainwindow.h"
#include <QFile>
#include <QTimer>

class notesTest : public QObject
{
    Q_OBJECT

public:
    notesTest();
    ~notesTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void backUpDeletedTest_case();
    void backUpAddedTest_case();
    void undoTest_case();
    void addingNewNotesThroughlineeditTest_case();
    void letterlimitlineeditTest_case();
    void createnewgroupTest_case();
    void editgroupnameTest_case();
    void creategroupswithsamenameTest_case();
    void deleteitemTest_case();
    void checkitemTest_case();
private:
    void closemessagebox();
    void deleteprevfiles();


};
class testhelper: public QObject
{
    Q_OBJECT
    friend notesTest;
public:
    testhelper(){};
    void helpwithmessageboxes(notesTest* nt)
    {
        QTimer::singleShot(0, this, SLOT(closemessagebox()));
    };
    void helpverifymessageboxes(notesTest* nt){
        QTimer::singleShot(0, this, SLOT(closeverifymessagebox()));
    }
private slots:
    void closemessagebox();
    void closeverifymessagebox();
};

notesTest::notesTest()
{

}

notesTest::~notesTest()
{

}

void notesTest::initTestCase()
{

}

void notesTest::cleanupTestCase()
{

}

void notesTest::deleteprevfiles()
{
    MainWindow w;
    QFile f1(w.NameOfNotes + w.fileFormat);
    if(f1.exists())
        f1.remove();
    QFile f2(w.NameOfArchive + w.fileFormat);
    if(f2.exists())
        f2.remove();
    QFile f3(w.NameOfMenu + w.fileFormat);
    if(f3.exists())
        f3.remove();
}

void notesTest::backUpDeletedTest_case()
{
    QObject* qobj = new QObject;
    caretaker* ct = new caretaker(qobj);
    int limit = ct->getlimit();
    for(int i=1; i<=limit + 1; i++)
        ct->backUpDeleted("str" + QString::number(i),i);

    memento* cm;
    for(int i=0; i< limit;i++)
    {
        cm = ct->getmemento(i);
        QCOMPARE(cm->gettext(),"str" + QString::number(i+2));
    }


     delete ct;
     delete qobj;
}

void notesTest::backUpAddedTest_case()
{
    QObject* qobj = new QObject;
    caretaker* ct = new caretaker(qobj);
    int limit = ct->getlimit();
    for(int i=1; i<=limit + 1; i++)
        ct->backUpAdded("str" + QString::number(i),i);

    memento* cm;
    for(int i=0; i< limit;i++)
    {
        cm = ct->getmemento(i);
        QCOMPARE(cm->gettext(),"str" + QString::number(i+2));
    }

    delete ct;
    delete qobj;

}

void notesTest::undoTest_case()
{
    QObject* qobj = new QObject;
    caretaker* ct = new caretaker(qobj);
    ct->backUpAdded("str1",1);
    ct->backUpDeleted("str2",2);
    ct->undo();

     QCOMPARE(ct->elements(),1);
     QCOMPARE(ct->getmemento(0)->gettext(),"str1");
     delete ct;
     delete qobj;

}



void notesTest::addingNewNotesThroughlineeditTest_case()
{
    MainWindow* w = new MainWindow();
    testhelper th;

        QTest::keyClicks(w->ui->lineEdit,"newNote");
        QTest::keyClick(w->ui->lineEdit,Qt::Key_Enter);

        QListWidgetItem* item = w->ui->listWidget->item(0);
        QCOMPARE(item->text(),"newNote");

        th.helpwithmessageboxes(this);
        w->close();
   delete w;
}


void notesTest::letterlimitlineeditTest_case()
{

   // MainWindow* w = new MainWindow();
    MainWindow w;
  // QTimer::singleShot(0, this, SLOT(testhelper::closemessagebox()));
    testhelper th;
    th.helpwithmessageboxes(this);
    for(int i=0; i<=w.letterlimit;i++)
    {
        QTest::keyClick(w.ui->lineEdit,Qt::Key_A);

    }
    QTest::keyClick(w.ui->lineEdit,Qt::Key_Enter);

    th.helpwithmessageboxes(this);
    w.close();


}
void testhelper::closemessagebox()
{

            QWidget*w = QApplication::activeModalWidget();

            QMessageBox *mb = qobject_cast<QMessageBox *>(w);
            if(mb)
            QTest::keyClick(mb, Qt::Key_Enter);


}

void testhelper::closeverifymessagebox()
{


    QWidget*w = QApplication::activeModalWidget();

    QMessageBox *mb = qobject_cast<QMessageBox *>(w);
    if(mb)
      QTest::keyClick(mb, Qt::Key_Enter);
      QVERIFY(mb != nullptr);
}

void notesTest::createnewgroupTest_case()
{

    this->deleteprevfiles();
    MainWindow w;
    testhelper th;

    QTest::mouseClick(w.ui->pushButton_4,Qt::MouseButton::LeftButton);


    QAbstractItemDelegate* delegate = w.ui->listWidget_2->itemDelegate();
   QSignalSpy spy(delegate,SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)));
 w.ui->listWidget_2->item(w.ui->listWidget_2->count()-1)->setText("test1");

 QTest::keyClick(w.ui->listWidget_2->itemWidget(w.ui->listWidget_2->item(w.ui->listWidget_2->count()-1)),Qt::Key_Escape);
 QVERIFY(spy.count() == 1);

   // QTest::keyClick(w.ui->listWidget_2,Qt::Key_Enter);

   QCOMPARE(w.ui->listWidget_2->item(w.ui->listWidget_2->count()-1)->text(),"test1");

   th.helpwithmessageboxes(this);
   w.close();
   }

void notesTest::editgroupnameTest_case()
{
    MainWindow w;

}


   void  notesTest::creategroupswithsamenameTest_case()
   {
        this->deleteprevfiles();
       MainWindow w;
       testhelper th;
      // th.helpwithmessageboxes(this);

       QAbstractItemDelegate* delegate = w.ui->listWidget_2->itemDelegate();
      QSignalSpy spy(delegate,SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)));

      QTest::mouseClick(w.ui->pushButton_4,Qt::MouseButton::LeftButton);
    w.ui->listWidget_2->item(w.ui->listWidget_2->count()-1)->setText("test1");
    QTest::keyClick(w.ui->listWidget_2->itemWidget(w.ui->listWidget_2->item(w.ui->listWidget_2->count()-1)),Qt::Key_Escape);

    QTest::mouseClick(w.ui->pushButton_4,Qt::MouseButton::LeftButton);
  w.ui->listWidget_2->item(w.ui->listWidget_2->count()-1)->setText("test1");

th.helpverifymessageboxes(this);
  QTest::keyClick(w.ui->listWidget_2->itemWidget(w.ui->listWidget_2->item(w.ui->listWidget_2->count()-1)),Qt::Key_Escape);
QVERIFY(spy.count() == 2);

th.helpwithmessageboxes(this);
w.close();
   }

   void notesTest::deleteitemTest_case()
   {
       MainWindow* w = new MainWindow();
       testhelper th;

       QSignalSpy spy(w->ui->listWidget_2,SIGNAL(itemClicked(QListWidgetItem*)));
       QSignalSpy spy1(w,SIGNAL(itemIsDeleted(QString, uint)));
           QRect rect = w->ui->listWidget_2->visualItemRect(w->ui->listWidget_2->item(0));
           QPoint pos(rect.center().x(),rect.center().y() );
       QTest::mouseClick(w->ui->listWidget_2->viewport(),Qt::MouseButton::LeftButton,Qt::KeyboardModifiers(),pos);
       QCOMPARE(spy.count(),1);
       QListWidgetItem* item = new  QListWidgetItem;
       item->setText("test1");
       item->setData(Qt::CheckStateRole,0);
       w->ui->listWidget->addItem(item);
       QCOMPARE(w->ui->listWidget->count(),1);
       w->ui->listWidget->setCurrentItem(item);
       QTest::mouseClick(w->ui->pushButton_2,Qt::MouseButton::LeftButton);
      // w->deleteItem(item,w->ui->listWidget);
       QCOMPARE(spy1.count(),1);
       QCOMPARE(w->ui->listWidget->count(),0);

       th.helpwithmessageboxes(this);
       w->close();
       delete w;
   }

   void notesTest::checkitemTest_case()
   {
       this->deleteprevfiles();
       MainWindow mw;
       testhelper th;

       QVector<QString> names;
       names.push_back(mw.NameOfNotes);
       names.push_back(mw.NameOfArchive);

       QSignalSpy spy(mw.ui->listWidget,SIGNAL(itemChanged(QListWidgetItem*)));


       QRect rect = mw.ui->listWidget_2->visualItemRect(mw.ui->listWidget_2->item(0));
       QPoint pos(rect.center().x(),rect.center().y() );
   QTest::mouseClick(mw.ui->listWidget_2->viewport(),Qt::MouseButton::LeftButton,Qt::KeyboardModifiers(),pos);
   QListWidgetItem* item = new  QListWidgetItem;
   item->setText("test1");
   item->setData(Qt::CheckStateRole,0);
   mw.ui->listWidget->addItem(item);
   mw.ui->listWidget->item(0)->setCheckState(Qt::CheckState::Checked);
  QVERIFY(spy.count() == 1);
  QVERIFY(mw.ui->listWidget->count()==0);

   rect = mw.ui->listWidget_2->visualItemRect(mw.ui->listWidget_2->item(1));
   pos.setX(rect.center().x());
   pos.setY(rect.center().y());
   QTest::mouseClick(mw.ui->listWidget_2->viewport(),Qt::MouseButton::LeftButton,Qt::KeyboardModifiers(),pos);
   QCOMPARE(mw.ui->listWidget->item(0)->text(), "test1");

   th.helpwithmessageboxes(this);
   mw.close();
   }
   #include "tst_notestest.moc"
   QTEST_MAIN(notesTest)




