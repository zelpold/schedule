#include "gnatt.h"
#include "ui_gnatt.h"

gnatt::gnatt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gnatt)
{
    ui->setupUi(this);
}

QMap<QString, int> gnatt::getIndex_map() const
{
    return index_map;
}

void gnatt::setIndex_map(const QMap<QString, int> &value)
{
    index_map = value;
}


gnatt::~gnatt()
{
    delete ui;
}
void gnatt::set_Color(){
    Colo[0][0] = 166; Colo[0][1] = 0; Colo[0][2] = 0;//rgb(166, 0, 0);
    Colo[1][0] = 1; Colo[1][1] = 86; Colo[1][2] = 102;//rgb(1, 86, 102);
    Colo[2][0] = 166; Colo[2][1] = 137; Colo[2][2] = 0;//rgb(166, 137, 0);
    Colo[3][0] = 136; Colo[3][1] = 0; Colo[3][2] = 69;//rgb(136, 0, 69);
    Colo[4][0] = 131; Colo[4][1] = 160; Colo[4][2] = 0;//rgb(131, 160, 0);
    Colo[5][0] = 8; Colo[5][1] = 20; Colo[5][2] = 114;//rgb(8, 20, 114);
    Colo[6][0] = 186; Colo[6][1] = 50; Colo[6][2] = 20;//rgb(166, 0, 0);
    Colo[7][0] = 20; Colo[7][1] = 136; Colo[7][2] = 122;//rgb(1, 86, 102);
    Colo[8][0] = 186; Colo[8][1] = 187; Colo[8][2] = 20;//rgb(166, 137, 0);
    Colo[9][0] = 156; Colo[9][1] = 50; Colo[9][2] = 89;
}
void gnatt::createtable(){
//    for (int i = 1; i < 101 ; i++){
//        if (W[i].N==0) break;
//        rows=W[i].N;
//    }
    set_Color();
    ui->graf->setRowCount(rows);
    ui->graf->setColumnCount(time+1);


    QMapIterator<QString, int> i(index_map);
    for (int row = 0; row <rows;row++)
    {
        ui->graf->setVerticalHeaderItem(row, new QTableWidgetItem(index_map_reverse.find(row).value()));
    }

    qDebug() <<"ok3";
    for ( int i = 0 ; i < ui->graf->columnCount(); i++){
        ui->graf->setColumnWidth(i,20);
    }
    for (int i = 0; i < ui->graf->rowCount();i++) ui->graf->setRowHeight(i,25);
    for(int i = 1; i < 10001 ; i++){
        if (W[i].N==0) break;
        for(int j = W[i].Tn; j < W[i].Tv+W[i].Tn; j++){

            QString s = QString::number(W[i].N)+", "+QString::number(W[i].No);

            auto row_it = index_map.find(QString::number(W[i].NG)+"-"+QString::number(W[i].Nm));
            if(row_it == index_map.end()) {
                qDebug() << "continue " +QString::number(W[i].NG)+"-"+QString::number(W[i].Nm);
                continue;
            }
            qDebug() << row_it.value() <<QString::number(W[i].NG)+"-"+QString::number(W[i].Nm) ;
            ui->graf->setItem(row_it.value(),j, new QTableWidgetItem(s));
            ui->graf->item(row_it.value(), j)->setBackground(QColor(Colo[W[i].N-1][0],Colo[W[i].N-1][1],Colo[W[i].N-1][2]));
            ui->graf->item(row_it.value(),j)->setForeground(QColor(255,255,255));
//            ui->graf->setItem(W[i].N-1,j, new QTableWidgetItem(s));
//            ui->graf->item(W[i].N-1, j)->setBackground(QColor(Colo[W[i].N-1][0],Colo[W[i].N-1][1],Colo[W[i].N-1][2]));
//            ui->graf->item(W[i].N-1,j)->setForeground(QColor(255,255,255));

            //            ui->graf->item(W[i].N-1,j)->setBackgroundColor(QColor(Colo[W[i].N-1][0],Colo[W[i].N-1][1],Colo[W[i].N-1][2]));
//            ui->graf->item(W[i].N-1,j)->setTextColor(QColor(255,255,255));
        }

    }
}
void gnatt::on_back_clicked()
{
    close();
}
