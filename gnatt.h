#ifndef GNATT_H
#define GNATT_H

#include <QDialog>
#include <QMap>
struct work{
    int N;
    int No;
    int NG;
    int Nm;
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
    int rows;
    QMap<QString, int> index_map;
    QMap<int, QString> index_map_reverse;
    ~gnatt();
    work W[101];
    void createtable();
    int time;

    void set_Color();
    QMap<QString, int> getIndex_map() const;
    void setIndex_map(const QMap<QString, int> &value);

private slots:
    void on_back_clicked();

private:
    Ui::gnatt *ui;
    int Colo[10][3];
};

#endif // GNATT_H
