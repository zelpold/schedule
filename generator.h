#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMainWindow>
#include <QListWidget>
#include <QDebug>
#include "user.h"
#include "gnatt.h"
struct Twork{
    int N ;     // номер работы
    int No ;    // номер операции
    int mOp;    // max number op
    int NG;     // group
    int ti;     // время выполнения данной операции - изменяется
    int Status; // статус
    int tn;     // время начала выполнения операции
    int S;      // сумма длит остав операций
    int nm;     // номер машины в группе
    int tv;     // время выполнения данной операции - постоянно
};

namespace Ui {
class generator;
}

class generator : public QMainWindow
{
    Q_OBJECT

public:

//    const QMap<QString, int> status_map = {
//        {"Н", 0},
//        {"-", 0},
//        {"О", 1},
//        {"И", 2},
//        {"З", 3},
//        {"F", 3}
//    };
    explicit generator(QWidget *parent = nullptr);
    ~generator();
    void creatework();
    int Qoper,                  // кол-во операций
    Qwork,                      // кол-во работ
    matrix1[10][10], matrix2[10][10],matrix3[100],
    CurTime,                    //
    NR,                         // кол-во операций всего
    NG,                         // кол-во ГРМ
    WG[101],                    // массив ГРМ
    AGM[101][101];              // доступность РМ

    // переменные для конфликтов
    bool Db;                        // повторы в конфликтах
    int CM;                         // счетчик конфликтов
    int CMGCount, CGNOper;          // счетчик конфликтов в ГК
    int CA[101],CW[101];            // конфликты и весы конфликтов
    int CG[6][11];                  // группы конфликтов
    int CMG[11];                    // кол-во операций в ГК
    Twork W[101] ,T[101];           // массив работ
    QStringList Names;
    int NamesCount;

private slots:
    void on_step_clicked();

    void on_auto_2_clicked();

    void on_KD_clicked();

    void on_pushButton_4_clicked();

private:

    Ui::generator *ui;
    int getstatus(QString s);               // возвращает статус операции
    void getworklist();
    int GetFreeM(int G);
    void ShowWorkFO(int raz, Twork *TTW);
    void ShowWorkKONF(int raz, Twork *TTW);
    QString OutStatus(int C);
    QString OutUndef(int C);
    void cleanCA();
    void ConflictCount();
    void PutRow (int X);
    void ConflictSolve();
    int GetNameNumber(QString X);
    void FillCW(QString S, int n);
    int GetExt(QString S, int n);
    void SortZeroConf(int n);
    void StartWork(Twork &TT);
    void StartDelayWork();
    void synchronize();
    void ShowWorkWORK(int raz, Twork *TTW);
    void ShowBusyList();
    QString OutBusyM(int c);
    void DoWork();
    int GetPlaceW(Twork v);
    bool EndWorks();
    void autoClick();
};

#endif // GENERATOR_H
