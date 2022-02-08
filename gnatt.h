#ifndef GNATT_H
#define GNATT_H

#include <QDialog>
struct work{
    int N;
    int No;
    int Tv;
    int Tn;
};

namespace Ui {
class gnatt;
}

class gnatt : public QDialog
{
    Q_OBJECT

public:
    explicit gnatt(QWidget *parent = nullptr);
    int Nr;
    ~gnatt();
    work W[101];
    void createtable();
    int time;

    void set_Color();
private slots:
    void on_back_clicked();

private:
    Ui::gnatt *ui;
    int Colo[10][3];
};

#endif // GNATT_H
