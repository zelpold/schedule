#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "generator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int CurTime;
       int R,Op;
       generator *window = new generator(this);
       void error();
private slots:
       int error(QListWidgetItem *item1);

       void on_getoff_itemDoubleClicked(QListWidgetItem *item);

       void on_geton_itemDoubleClicked(QListWidgetItem *item);

       void on_creatematrix_clicked();

       void on_randomtm_clicked();

       void on_creatematrix3_clicked();

       void on_random3_clicked();

       void on_next_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
