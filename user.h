#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QListWidget>
struct TTwork{
    int N ;     // номер работы
    int No ;    // номер операции
    int mOp;    // max number op
    int NG;     // group
    int ti;     // время выполнения данной операции - изменяется
    int Status; // статус
    int tn;     // время начала
    int S;      // сумма длит остав операций
    int nm;     // номер машины в группе
    int tv;     // время выполнения данной операции - постоянно
};
namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();
    int getdata() ;
    void createuserTable(int n , int CMG_n, int CG_n);
    TTwork T[101];
    int CG[6][11];
private:
    Ui::user *ui;
};

#endif // USER_H
