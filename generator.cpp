#include "generator.h"
#include "ui_generator.h"
#include "mainwindow.h"
#include "user.h"

generator::generator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::generator)
{
    ui->setupUi(this);
}

generator::~generator()
{
    delete ui;
}

int generator::getstatus(QString s)
{
    static QMap<QString, int> status_map = {
        {"Н", 0},
        {"-", 0},
        {"О", 1},
        {"И", 2},
        {"З", 3},
        {"F", 3}
    };
    auto item = status_map.find(s);
    if (item == status_map.end() ){
       return 0;
    }

    return item.value();
//    if (s == "Н" || s == "-") return 0 ;     // операция неопределена
//    else if (s == "O") return 1;             // операция в ожидании
//    else if (s == "И") return 2;             // операция исполняется
//    else if (s == "З" || s == "F") return 3; // операция завершена
//    return 0;
}

void generator::getworklist(){

    //настройка таблиц
    ui->work->setRowCount(Qoper*Qwork);
    ui->work->verticalHeader()->hide();
    ui->work->horizontalHeader()->setMaximumSectionSize(50);
    ui->work->horizontalHeader()->setMinimumSectionSize(0);
    ui->work->verticalHeader()->setMaximumSectionSize(50);
    ui->work->verticalHeader()->setMinimumSectionSize(0);

    ui->FO->setRowCount(Qwork);
    ui->FO->verticalHeader()->hide();
    ui->FO->horizontalHeader()->setMaximumSectionSize(50);
    ui->FO->horizontalHeader()->setMinimumSectionSize(0);
    ui->FO->verticalHeader()->setMaximumSectionSize(50);
    ui->FO->verticalHeader()->setMinimumSectionSize(0);

    ui->KONF->setRowCount(Qwork);
    ui->KONF->verticalHeader()->hide();
    ui->KONF->horizontalHeader()->setMaximumSectionSize(50);
    ui->KONF->horizontalHeader()->setMinimumSectionSize(0);
    ui->KONF->verticalHeader()->setMaximumSectionSize(50);
    ui->KONF->verticalHeader()->setMinimumSectionSize(0);

    ui->workSourse->verticalHeader()->hide();
    ui->workSourse->horizontalHeader()->setMaximumSectionSize(50);
    ui->workSourse->horizontalHeader()->setMinimumSectionSize(0);
    ui->workSourse->verticalHeader()->setMaximumSectionSize(50);
    ui->workSourse->verticalHeader()->setMinimumSectionSize(0);


    ui->Busylist->horizontalHeader()->setMaximumSectionSize(50);
    ui->Busylist->horizontalHeader()->setMinimumSectionSize(0);
    ui->Busylist->verticalHeader()->setMaximumSectionSize(50);
    ui->Busylist->verticalHeader()->setMinimumSectionSize(0);

    for (int i=0; i <= 8;i++){
        ui->work->setColumnWidth(i,26);
        ui->FO->setColumnWidth(i,26);
        ui->KONF->setColumnWidth(i,26);
        ui->workSourse->setColumnWidth(i,26);
    }
        ui->work->setColumnWidth(9,40);
        ui->FO->setColumnWidth(9,40);
        ui->KONF->setColumnWidth(9,40);
        ui->workSourse->setColumnWidth(9,40);

    for (int i = 0; i < ui->work->rowCount();i++) ui->work->setRowHeight(i,25);
    for (int i = 0; i < ui->FO->rowCount();i++) ui->FO->setRowHeight(i,25);
    for (int i = 0; i < ui->KONF->rowCount();i++) ui->KONF->setRowHeight(i,25);
// ----------------------------------------------------------------------
    //Получение списка работ
    int a = 0; // номер строки
    for (int i = 0; i < Qwork; i++){
        for (int j = 0; j < Qoper; j++){
            ui->work->setItem(j+a,0, new QTableWidgetItem(QString::number(i+1)));
            ui->work->setItem(j+a,1, new QTableWidgetItem(QString::number(j+1)));
            ui->work->setItem(j+a,2,new QTableWidgetItem(QString::number(matrix1[i][j])));
            ui->work->setItem(j+a,3,new QTableWidgetItem(QString::number(matrix2[i][j])));
            ui->work->setItem(j+a,4, new QTableWidgetItem("Н"));
            ui->work->setItem(j+a,5, new QTableWidgetItem("-1"));
            ui->work->setItem(j+a,6, new QTableWidgetItem("-1"));
            ui->work->setItem(j+a,8,new QTableWidgetItem(QString::number(matrix2[i][j])));
        }
        a+=Qoper;
    }

    //для каждой операции рассчитываем время необходимое для выполнения всей работы
    a = 0;
    for (int i = 0; i < Qwork; i++){
        int c = 0 ;
        for (int j = Qoper-1; j >= 0 ; j--){
            c += matrix2[i][j];
            ui->work->setItem(j+a,7, new QTableWidgetItem(QString::number(c)));
        }
        a+=Qoper;
    }

    // удаляем из списка пустые работы
    a = 0;
    do {
            if (ui->work->item(a,2)->text()=="0")
                ui->work->removeRow(a);
            else a++;
    }while(a != ui->work->rowCount());

    //очищаем массив работ
    for ( int i = 1 ; i <= 100 ; i++ ){
        W[i].N=0;
        W[i].No=0;
        W[i].mOp=0;
        W[i].NG=0;
        W[i].ti=0;
        W[i].Status=0;
        W[i].S=0;
        W[i].tv=0;
        WG[i] = 0;
    }
    NR=ui->work->rowCount(); //кол-во всех операций

    //очищаем массив AGM
    for (int i = 1; i <= NG ; i++){
        for (int j = 1 ; j < 101; j++ ){
            AGM[i][j] = 0;
        }
    }

    //добавляем в массив WG - массив рабочих машин
    for (int j=1; j <= NG; j++) WG[j]=matrix3[j-1];

    //заносим в массив W список работ
    for (int j=1; j <= NR; j++) {
        W[j].N = ui->work->item(j-1,0)->text().toInt();
        W[j].No = ui->work->item(j-1,1)->text().toInt();
        W[j].NG = ui->work->item(j-1,2)->text().toInt();
        W[j].ti = ui->work->item(j-1,3)->text().toInt();
        W[j].tn = ui->work->item(j-1,5)->text().toInt();
        W[j].S = ui->work->item(j-1,7)->text().toInt();
        W[j].Status =getstatus(ui->work->item(j-1,4)->text());
        W[j].nm = -1;
        W[j].tv = ui->work->item(j-1,3)->text().toInt();
        W[j].mOp = 1;
    }

    //считаем количество оставшихся операций в работе для каждой операции
    int m = 1;
    a = 1;
    for (int j = 1; j <= NR; j++){
        if (W[j].N == W[j+1].N && j+1 != NR+1 ){
            m++;
        }
        else{
            for(int c = a; c <= j; c++) W[c].mOp = m;
            m = 1;
            a = j+1;
        }
    }
    //заполняем workSourse
    ui->work->update();
    ui->workSourse->setRowCount(ui->work->rowCount());

    for(int i = 0; i < ui->work->rowCount(); i++)
    {
        for (int j = 0; j< ui->work->columnCount()-1; j++){
            QString s ="1";
            s = ui->work->item(i,j)->text();
            ui->workSourse->setItem(i,j,new QTableWidgetItem (s));
            ui->workSourse->setRowHeight(i,25);
        }
    }
}

// возвращает свободное РМ в текущей ГРМ если есть
int generator::GetFreeM(int G){
    for (int i = 1 ; i <= WG[G]; i++)
         if (!AGM[G][i]) return i;
    return -1;
}

//запуск работ со статусом ожидания
void generator::StartDelayWork(){
    for (int n = 1; n <= Qwork; n++){
        if (T[n].Status == 1){
            T[n].nm = GetFreeM(T[n].NG);
            //if (T[n].nm > 0 && AGM[T[n].NG][T[n].nm] == 0) StartWork(T[n]);
            if (T[n].nm >= 0) StartWork(T[n]);
        }
    }
}

QString generator::OutStatus(int C){
    switch (C) {
        case 0: return "-";
        case 1: return "О";
        case 2: return "И";
        case 3: return "F";
        default: return "-";
    }
}

QString generator::OutUndef(int C){
    if (C == -1) return "-";
    else return QString::number(C);
}
void generator::ShowWorkFO(int raz, Twork *TTW){
    for (int i = 1 ; i <= raz; i++){
        ui->FO->setItem(i-1,0, new QTableWidgetItem(QString::number(TTW[i].N)));
        ui->FO->setItem(i-1,1, new QTableWidgetItem(QString::number(TTW[i].No)));
        ui->FO->setItem(i-1,2, new QTableWidgetItem(QString::number(TTW[i].NG)));
        ui->FO->setItem(i-1,3, new QTableWidgetItem(QString::number(TTW[i].ti)));
        ui->FO->setItem(i-1,4, new QTableWidgetItem(OutStatus(TTW[i].Status)));
        ui->FO->setItem(i-1,5, new QTableWidgetItem(OutUndef(TTW[i].tn)));
        ui->FO->setItem(i-1,6, new QTableWidgetItem(OutUndef(TTW[i].nm)));
        ui->FO->setItem(i-1,7, new QTableWidgetItem(QString::number(TTW[i].S)));
        ui->FO->setItem(i-1,8, new QTableWidgetItem(QString::number(TTW[i].tv)));
        ui->FO->setItem(i-1,9, new QTableWidgetItem(QString::number(TTW[i].mOp)));
    }
}
void generator::ShowWorkKONF(int raz, Twork *TTW){
    for (int i = 1 ; i <= raz; i++){
        ui->KONF->setItem(i-1,0, new QTableWidgetItem(QString::number(TTW[i].N)));
        ui->KONF->setItem(i-1,1, new QTableWidgetItem(QString::number(TTW[i].No)));
        ui->KONF->setItem(i-1,2, new QTableWidgetItem(QString::number(TTW[i].NG)));
        ui->KONF->setItem(i-1,3, new QTableWidgetItem(QString::number(TTW[i].ti)));
        ui->KONF->setItem(i-1,4, new QTableWidgetItem(OutStatus(TTW[i].Status)));
        ui->KONF->setItem(i-1,5, new QTableWidgetItem(OutUndef(TTW[i].tn)));
        ui->KONF->setItem(i-1,6, new QTableWidgetItem(OutUndef(TTW[i].nm)));
        ui->KONF->setItem(i-1,7, new QTableWidgetItem(QString::number(TTW[i].S)));
        ui->KONF->setItem(i-1,8, new QTableWidgetItem(QString::number(TTW[i].tv)));
        ui->KONF->setItem(i-1,9, new QTableWidgetItem(QString::number(TTW[i].mOp)));
    }
}

//процедура отображения массива работы на экран
void generator::ShowWorkWORK(int raz, Twork *TTW){
    for (int i = 1 ; i <= raz; i++){
        ui->work->setItem(i-1,0, new QTableWidgetItem(QString::number(TTW[i].N)));
        ui->work->setItem(i-1,1, new QTableWidgetItem(QString::number(TTW[i].No)));
        ui->work->setItem(i-1,2, new QTableWidgetItem(QString::number(TTW[i].NG)));
        ui->work->setItem(i-1,3, new QTableWidgetItem(QString::number(TTW[i].ti)));
        ui->work->setItem(i-1,4, new QTableWidgetItem(OutStatus(TTW[i].Status)));
        ui->work->setItem(i-1,5, new QTableWidgetItem(OutUndef(TTW[i].tn)));
        ui->work->setItem(i-1,6, new QTableWidgetItem(OutUndef(TTW[i].nm)));
        ui->work->setItem(i-1,7, new QTableWidgetItem(QString::number(TTW[i].S)));
        ui->work->setItem(i-1,8, new QTableWidgetItem(QString::number(TTW[i].tv)));
        ui->work->setItem(i-1,9, new QTableWidgetItem(QString::number(TTW[i].mOp)));
    }
}
QString generator::OutBusyM(int c){
    QString s = "з";
    if (c==0) s = "-";
    return s;
}

//процедура отображения массива ГРМ на экран
void generator::ShowBusyList(){
    ui->Busylist->clear();
    for (int j = 1; j <= NG; j++)
        for (int j1 =1; j1 <= WG[j]; j1++)
            ui->Busylist->setItem(j1-1,j-1, new QTableWidgetItem (OutBusyM(AGM[j][j1])));
}

void generator::creatework(){
    int j, n, mx;

    bool cExit;
    getworklist();
    CurTime = 0;
    mx = 1;
    for (int i = 1; i <= NG; i++)
        if (mx < matrix3[i-1]) mx = WG[i];
    ui->Busylist->setColumnCount(NG);
    ui->Busylist->setRowCount(mx);
    for (int i = 0; i < ui->Busylist->rowCount(); i++) ui->Busylist->setRowHeight(i,25);
    for (int i = 0; i < NG; i++) {
        ui->Busylist->setColumnWidth(i,25);
    }
    n = 1;
    cExit = 0;
    for (int i = 1 ; i <= NR; i++){
        if (!cExit && W[i].N == n && W[i].Status == 0 ){
            T[n]=W[i];
            if (n<Qwork) n++;
            else  cExit = 1;
        }
    }
    for (int i = 1; i <= Qwork; i++){
        int r = GetFreeM(T[i].NG);
        T[i].nm  = r;
        ui->log->append(QString::number(T[i].nm));
        T[i].Status = 1;
    }
    ui->FO->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Busylist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->work->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->workSourse->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->KONF->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ShowWorkFO(Qwork,T);
    cleanCA();
    ConflictCount();
    ConflictSolve();
    StartDelayWork();
    synchronize();
    ShowWorkKONF(Qwork,T);
    ShowWorkWORK(NR,W);
    ShowBusyList();
}

//процедура для синхронизации списка работ и ФО (W и T)
void generator::synchronize(){
    for (int j = 1; j <= Qwork; j++)
        for(int n = 1; n <=NR; n++)
            if (T[j].N == W[n].N && T[j].No == W[n].No) W[n] = T[j];
}

//обнуление массива конфликтов (Ошибок)
void generator::cleanCA(){
    for (int i = 1; i <= 100; i++) CA[i] = 0;
    CM = 0;
    CMGCount = 0;
    CGNOper = 0;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 10; j++) CG[i][j] = 0;
    for (int i = 1; i <= 10 ; i++) CMG[i] = 0;
}

//подсчет конфликтов
void generator::ConflictCount(){
    CM = 0;
    for (int i = 1; i <= Qwork; i++)
        for(int j = 2; j <= Qwork; j++){
            if (i < j)
                if (T[i].Status == T[j].Status && T[i].NG == T[j].NG && T[i].nm == T[j].nm && (T[i].Status!=3 || T[j].Status!=3)){
                    T[i].nm =GetFreeM(T[i].NG);
                    if (T[i].nm > 0 && AGM[T[i].NG][T[i].nm] == 0) {
                        ui->log->append("C>>" + QString::number(T[j].N) + " " + QString::number(T[i].N));
                        PutRow(i);
                        PutRow(j);
                    }
                }
        }
    // разносим конфликты по группам конфликтов
    int z = 1, // номер группы конфликтов
        n = 1, // номер конфликта
        i = 1; // номер операции в гк

    if (CM > 0){
        do {
            if (n != CM){
                if (T[CA[n]].NG == T[CA[n+1]].NG){
                    CG[z][i] = CA[n];
                    CMG[z]++;
                    n++;
                    i++;
                }
                else{
                    CG[z][i] = CA[n];
                    CMG[z]++;
                    z++;
                    n++;
                    i = 1;
                }
            }
            else{
                CG[z][i] = CA[n];
                CMG[z]++;
                n++;
                i = 1;
            }
            CMGCount=z; // количество групп конфликтов
        }while (!(n > CM));
    }
}

//вспомогательная процедура для хранения 'весов' операций
void generator::FillCW(QString S, int n){
    switch (GetNameNumber(S)) {
        case 0:
            for(int i = 1; i <= CMG[n]; i++) CW[i] = T[CG[n][i]].ti;
            break;
        case 1:
            for(int i = 1; i <= CMG[n]; i++) CW[i] = T[CG[n][i]].S;
            break;
        case 2:
            for(int i = 1; i <= CMG[n]; i++) CW[i] = T[CG[n][i]].ti;
            break;
        case 3:
            for(int i = 1; i <= CMG[n]; i++) CW[i] = T[CG[n][i]].S;
            break;
        case 4:
            break;
        case 5:
            for(int i = 1; i <= CMG[n]; i++) CW[i] = T[CG[n][i]].mOp;
            break;
        case 6:
            break;
        case 7:
            break;
    }
}

//решение кофликтов
void generator::ConflictSolve(){
    if (CM > 0) // конфликты есть
        for (int n = 1; n <= CMGCount; n++){
            do {
                int G;
                int k = 0;
                do {
                    G = GetExt(Names[k],n);
                    k++;
                }while(!(G != -1  || k == NamesCount)); // пока не разрешены конфликты и не закончились правила предпочтения
                if (G != -1){ //если кофликты разрешены
                    T[G].nm = GetFreeM(T[G].NG); //получаем номер рабочего места
                    if (T[G].nm > 0 && AGM[T[G].NG][T[G].nm] == 0){
                        StartWork(T[G]); // запускаем работу

                        CG[n][CGNOper] = 0; //обнуляем конфликт для данной операции
                        SortZeroConf(n);
                        CMG[n] = CMG[n]-1; //уменьшаем количество операций в гк
                    }
                }
                if(CG[n][1] == 0) break; // если кофнфликты были решён для всех операций в данной гк
            }while(GetFreeM(T[CG[n][1]].NG) != -1);// пока данная грм не полностью занята
        }
}

// запуск конкретной операции
void generator::StartWork(Twork &TT){
    TT.Status = 2;
    TT.tn = CurTime;
    AGM[TT.NG][TT.nm] = 1;
}

//функция для получения экстремума
int generator::GetExt(QString S, int n){
    int mx;
    // обнуляем веса
    for(int i = 1; i <= 100; i++){ CW[i] = 0;}
    int k = 0;
    FillCW(S,n); // заполняем веса в соответствии с правилом предпочтения
    int G = -1;
    int Result =-1;
    switch (GetNameNumber(S)){
    case 0:{
        mx = 1000;
        for (int j = 1; j <= CMG[n]; j++)
            if (mx > CW[j]){
                mx = CW[j];
                G = CG[n][j];
                k = j;
            }
        break;
    }   //min(tv)
    case 1:{
        mx = 1000;
        for (int j = 1; j <= CMG[n]; j++)
            if (mx > CW[j]){
                mx = CW[j];
                G = CG[n][j];
                k = j;
            }
        break;
    }   //min(S)
    case 2:{
        mx = 0;
        for (int j = 1; j <= CMG[n]; j++){
            if(mx < CW[j]){
                mx = CW[j];
                G =CG[n][j];
                k = j;
            }
        }
        break;
    } //max(tv)
    case 3:{
        mx = 0;
        for (int j = 1; j <= CMG[n]; j++){
            if(mx < CW[j]){
                mx = CW[j];
                G = CG[n][j];
                k = j;
            }
        }
        break;
    } //max(S)
    case 4:{
        CM = 0;
        return CA[1];
        break;
    } //FIFO
    case 5:{
        int mx = 1000;
        for (int j = 1; j <= CMG[n]; j++){
            if (mx > CW[j]){
                mx = CW[j];
                G=CG[n][j];
                k = j;
            }
        }
        break;
    } //min(Op)
    case 6:

        break; // user 1

    case 7: {
        user *userw = new user(this);
        for(int i = 1; i <= 100; i++ ){
            userw->T[i].N=T[i].N;
            userw->T[i].NG=T[i].NG;
            userw->T[i].No=T[i].No;
            userw->T[i].nm=T[i].nm;
            userw->T[i].S=T[i].S;
            userw->T[i].Status=T[i].Status;
            userw->T[i].ti=T[i].ti;
            userw->T[i].tn=T[i].tn;
            userw->T[i].tv=T[i].tv;
            userw->T[i].mOp=T[i].mOp;
        }
        for (int i = 1; i < 6 ; i++){

            for (int j = 1; j < 11; j++) userw->CG[i][j] = CG[i][j];
        }
        userw->createuserTable(n, CMG[n], CG[n][1]);
        userw->setModal(true);

        if( userw->exec() == QDialog::Accepted){
            G = userw->getdata();

        }
        Result = G;
        for (int j = 1; j <= CMG[n]; j++) if (CG[n][j] == G) CGNOper = j;
        break;
    }// user
    }
    //проверка на двойной экстремум
    bool DB = false; // если в данной гк встречены одинаковые веса для разных операций
    for(int j = 1; j <= CMG[n]; j++){
        if (k != j && mx == CW[j]) DB = true;
    }
    if (!DB) {
        Result = G;
        CGNOper = k;
    }

    else if (CMG[n] != 2) {
        for (int j = 1; j <= CMG[n]; j++){
            if (mx != CW[j]) CG[n][j] = 0;

        }
        SortZeroConf(n);
        for(int j = 1 ; j <= CMG[n]; j++){
            if (CG[n][j] == 0){
                CMG[n] = j-1;
                break;
            }
        }
    }
    //else if (CMG[n] == 2) return Result;
    return Result;
}

//переводит правила предпочтения в цифры
int generator::GetNameNumber(QString x){
    for(int i  = 0; i<8;i++) {
        if (x == "min(tv)") return 0;
        if (x == "min(S)") return 1;
        if (x == "max(tv)") return 2;
        if (x == "max(S)") return 3;
        if (x == "FIFO") return 4 ;
        if (x == "min(Op)") return 5;
        if (x == "max(Time)") return 6;
        if (x == "USER") return 7;
    }
}

// поиск конфликтов и занесение их в память
void generator::PutRow(int X){
    // eсли счётчик конфликтов = 0
    if (CM == 0){
        CM = 1;
        CA[CM] = X;
    }
    else{
        bool exist = false;
        for (int i = 1; i <= CM ; i++)
            if ( CA[i] == X) exist = 1 ;
        if (!exist){
            CM++; CA[CM] = X;
        }
    }
}

//сортировка массива конфликтов с нулями
void generator::SortZeroConf(int n){
    for (int j = 1; j <= CMG[n]; j++){
        if (CG[n][j] == 0 && CG[n][j+1] == 0 && j+1 != CMG[n] ){
            for (int k = j; k <= CMG[n]; k++){
                if (CG[n][k] != 0){
                    CG[n][j] = CG[n][k];
                    CG[n][k] = 0;
                    break;
                }
            }
        }
        if (CG[n][j] == 0 && CG[n][j+1] != 0 && j != CMG[n]){
            CG[n][j] = CG[n][j+1];
            CG[n][j+1] = 0;
        }
    }
}

void generator::on_step_clicked()
{
    CurTime++;
    ui->time->setText(QString::number(CurTime));
    ui->log->clear();
    //выполняем работы которые в статусе выполнения статус = 2;
    DoWork();
    //отображаем файл обмена первый просмотр
    ShowWorkFO(Qwork,T);
    //обнуляем конфликты прошлого шага
    cleanCA();
    //считаем конфликты
    ConflictCount();
    //решаем конфликты
    ConflictSolve();
    //запускаем работы со статусом ожидания
    StartDelayWork();
    //отображаем занятость рм
    ShowBusyList();
    //файл обмена после разрешения кофликтов
    ShowWorkKONF(Qwork,T);
    synchronize();
    //отображаем список работ
    ShowWorkWORK(NR,W);
    if(EndWorks()) CurTime--;
}

void generator::autoClick(){
    do {
        CurTime++;
        ui->time->setText(QString::number(CurTime));
        ui->log->clear();
        DoWork();
        ShowWorkFO(Qwork,T);
        cleanCA();
        ConflictCount();
        ConflictSolve();
        StartDelayWork();
        ShowBusyList();
        ShowWorkKONF(Qwork,T);
        synchronize();
        ShowWorkWORK(NR,W);
    }while(!EndWorks());
    CurTime--;
}

//выполнения и завершения текущей работы
void generator::DoWork(){
    for (int m = 1 ; m <= Qwork; m++){
        // если работа выполняется
        if (T[m].Status == 2){
            T[m].ti--;
            T[m].S--;
        }
        // если осташееся время выполнения работы =0

        if(T[m].ti == 0 && T[m].Status != 3){
            T[m].Status=3; // обновляем статус на завершённый
            T[m].mOp--;
            int p = GetPlaceW(T[m]);
            W[p]=T[m]; //синхронизируем с W
            AGM[T[m].NG][T[m].nm]=0; // освобождаем рм
            //следующая операция у конкретной работы
            if (W[p].N == W[p+1].N){
                W[p+1].Status=1;
                W[p+1].mOp = T[m].mOp;
                T[m] = W[p+1];
            }
        }
    }
}


//функция возвращает номер свободной РМ в ГРМ ?????
int generator::GetPlaceW(Twork v){
    int k =-7;
    for (int j =1; j <= NR; j++)
        if  (v.N==W[j].N&&v.No==W[j].No) k = j;
    return k;
}


//функция возвращает истину если все работы закончены
bool generator::EndWorks(){
    for (int m = 0; m < NR; m++){
        if (ui->work->item(m, 4)->text() != "F") return false;
    }
    return true;
}

void generator::on_auto_2_clicked()
{
    do {
        CurTime++;
        ui->time->setText(QString::number(CurTime));
        ui->log->clear();
        DoWork();
        ShowWorkFO(Qwork,T);
        cleanCA();
        ConflictCount();
        ConflictSolve();
        StartDelayWork();
        ShowBusyList();
        ShowWorkKONF(Qwork,T);
        synchronize();
        ShowWorkWORK(NR,W);
    }while(!EndWorks());
    CurTime--;
}

void generator::on_KD_clicked()
{
    gnatt *gant = new gnatt(this);
    for (int i = 1; i < 101; i++ ){
        gant->W[i].N=W[i].N;
        gant->W[i].No=W[i].No;
        gant->W[i].Tn=W[i].tn;
        gant->W[i].Tv=W[i].tv;
        gant->W[i].NG = W[i].NG;
        gant->W[i].Nm = W[i].nm;
    }
    int rows = 0;
    for (int i = 0; i < NG ; i++)
    {

        rows += matrix3[i];
        for (int j = rows-matrix3[i]; j < rows; j++){
            gant->index_map[QString::number(i+1) + "-" + QString::number(j+1 - rows+matrix3[i])] = j;
            gant->index_map_reverse[j] = QString::number(i+1) + "-" + QString::number(j+1 - rows+matrix3[i]);
        }
    }
    gant->rows = rows;
    gant->time = CurTime;
    qDebug() <<"ok1";
    gant->createtable();
    qDebug() <<"ok2";
    gant->setModal(true);
    this->hide();
    gant->exec();
    if (gant->close()) this->show();

}

void generator::on_pushButton_4_clicked()
{
    close();
}
