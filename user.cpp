#include "user.h"
#include "ui_user.h"
user::user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
}

user::~user()
{
    delete ui;
}
void user::createuserTable(int n, int CMG_n, int CG_n){
    ui->rab->setText(QString::number(CG_n));
    ui->usertable->verticalHeader()->hide();
    ui->usertable->horizontalHeader()->setMaximumSectionSize(50);
    ui->usertable->horizontalHeader()->setMinimumSectionSize(0);
    ui->usertable->verticalHeader()->setMaximumSectionSize(50);
    ui->usertable->verticalHeader()->setMinimumSectionSize(0);
    ui->usertable->setRowCount(CMG_n);
    for (int i = 1; i <= CMG_n; i++){

        ui->usertable->setItem(i-1,0, new QTableWidgetItem(QString::number(T[CG[n][i]].N)));
        ui->usertable->setItem(i-1,1, new QTableWidgetItem(QString::number(T[CG[n][i]].No)));
        ui->usertable->setItem(i-1,2, new QTableWidgetItem(QString::number(T[CG[n][i]].NG)));
        ui->usertable->setItem(i-1,3, new QTableWidgetItem(QString::number(T[CG[n][i]].ti)));
        ui->usertable->setItem(i-1,4, new QTableWidgetItem(QString::number(T[CG[n][i]].Status)));
        ui->usertable->setItem(i-1,5, new QTableWidgetItem(QString::number(T[CG[n][i]].tn)));
        ui->usertable->setItem(i-1,6, new QTableWidgetItem(QString::number(T[CG[n][i]].nm)));
        ui->usertable->setItem(i-1,7, new QTableWidgetItem(QString::number(T[CG[n][i]].S)));
        ui->usertable->setItem(i-1,8, new QTableWidgetItem(QString::number(T[CG[n][i]].tv)));
        ui->usertable->setColumnWidth(i-1,25);
    }
}

int user::getdata(){
    return ui->rab->text().toInt();
}
