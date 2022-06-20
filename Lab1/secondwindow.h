#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QListWidgetItem>
#include <QCloseEvent>
namespace Ui {
class secondwindow;
}

class secondwindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();
private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_released();

    void readFromFile( QListWidget*, QString);

   void removeChecked(QListWidgetItem *item);

   void removeSelectedItem();

   void moveToFile(QListWidgetItem *item);

   void saveArchive();

private:
    Ui::secondwindow *ui;

    void createConnections();

    void closeEvent (QCloseEvent *event) override;

};

#endif // SECONDWINDOW_H
