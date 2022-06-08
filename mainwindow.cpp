#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::error(QListWidgetItem *item1){
    if (item1->text() == "max(S)")
        for (int j = 0 ; j < ui->geton->count(); j++)
            if (ui->geton->item(j)->text()=="min(S)") return j;

    if (item1->text() == "max(tv)")
        for (int j = 0 ; j < ui->geton->count(); j++)
            if (ui->geton->item(j)->text()=="min(tv)") return j;
    if (item1->text() == "min(S)")
        for (int j = 0 ; j < ui->geton->count(); j++)
            if (ui->geton->item(j)->text()=="max(S)") return j;
    if (item1->text() == "min(tv)")
        for (int j = 0 ; j < ui->geton->count(); j++)
            if (ui->geton->item(j)->text()=="max(tv)") return j;
    return  -1 ;
}

void MainWindow::on_getoff_itemDoubleClicked(QListWidgetItem *item)
{
    QListWidget *getoff = ui->getoff, *geton=ui->geton;
    int i = getoff->row(item);
    int er = error(item);
    if (er>=0) {
        getoff->insertItem(er,geton->item(er)->text());
        delete geton->takeItem(er);
        return;
    }
    if(item->text()=="FIFO"){
        for (int j = 0 ; j <geton->count(); j++ )
            getoff->addItem(geton->item(j)->text());
        geton->clear();
        geton->addItem("FIFO");
        delete getoff->takeItem(i);
        return;
    }

    bool tf = 1;
    for (int j = 0 ; j < ui->geton->count(); j++){
        if (ui->geton->item(j)->text()=="USER") tf = 0;
    }

    if (item->text() != "USER") geton->addItem(item->text());
    if (tf) ui->geton->addItem("USER");
    if (geton->item(0)->text() =="FIFO"){
        getoff->addItem("FIFO");
        delete geton->takeItem(0);
    }
    delete getoff->takeItem(i);
}

void MainWindow::on_geton_itemDoubleClicked(QListWidgetItem *item)
{
    int i = ui->geton->row(item);
    bool tf = 1;
    for (int j = 0 ; j < ui->getoff->count(); j++){
        if (ui->getoff->item(j)->text()==item->text()) tf = 0;
    }
    if (tf)
    ui->getoff->addItem(item->text());
    delete ui->geton->takeItem(i);
}

void MainWindow::on_creatematrix_clicked()
{
    Op = ui->countO->text().toInt();
    R = ui->countR->text().toInt();
    ui->matrix1->setColumnCount(Op);
    ui->matrix1->setRowCount(R);
    ui->matrix2->setColumnCount(Op);
    ui->matrix2->setRowCount(R);
    ui->matrix1->clear();
    ui->matrix2->clear();
    ui->matrix2->horizontalHeader()->hide();
    ui->matrix2->verticalHeader()->hide();
    ui->matrix1->horizontalHeader()->hide();
    ui->matrix1->verticalHeader()->hide();
    ui->matrix1->horizontalHeader()->setMaximumSectionSize(50);
    ui->matrix1->horizontalHeader()->setMinimumSectionSize(0);
    ui->matrix1->verticalHeader()->setMaximumSectionSize(50);
    ui->matrix1->verticalHeader()->setMinimumSectionSize(0);
    ui->matrix2->horizontalHeader()->setMaximumSectionSize(50);
    ui->matrix2->horizontalHeader()->setMinimumSectionSize(0);
    ui->matrix2->verticalHeader()->setMaximumSectionSize(50);
    ui->matrix2->verticalHeader()->setMinimumSectionSize(0);
    ui->matrix1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->matrix1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->matrix2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->matrix2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for (int i=0; i < Op;i++){
        ui->matrix1->setColumnWidth(i,25);
        ui->matrix2->setColumnWidth(i,25);
    }
    for (int i = 0; i < R;i++){
        ui->matrix1->setRowHeight(i,25);
        ui->matrix2->setRowHeight(i,25);
    }
}

void MainWindow::on_randomtm_clicked()
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    int left = ui->randomBorderTmLeft->text().toInt(), right = ui->randomBorderTmRight->text().toInt();
    int left_t = ui->min_t->text().toInt(), right_t = ui->max_t->text().toInt();
    MainWindow::on_creatematrix_clicked();
    srand(static_cast<unsigned int>(time(0)));
    int randd = static_cast<int>(rand()* fraction *(right - left + 1) + left);
    for(int j = 0; j < R; j++){
        int min = left;
        if (!min) min++;
        int rands = static_cast<int>(rand()* fraction *(right - min + 1) + min);
        QString t= QString::number(rands);
        ui->matrix1->setItem(j,0,new QTableWidgetItem(t));

    }
    for (int i = 0;i < R; i++)
            for (int j = 1; j < Op; j++){
                if (ui->matrix1->item(i,j-1)->text()=="0"){
                    ui->matrix1->setItem(i,j,new QTableWidgetItem("0"));
                }
                else{
                    QString t;
                    do{
                    int rands = static_cast<int>(rand()* fraction *(right - left + 1) + left);
                    t= QString::number(rands);
                    }while(t == ui->matrix1->item(i,j-1)->text());
                    ui->matrix1->setItem(i,j,new QTableWidgetItem(t));
                }
            }

    for (int i = 0;i < R; i++)
            for (int j = 0; j < Op; j++){
                if (ui->matrix1->item(i,j)->text()=="0"){
                    ui->matrix2->setItem(i,j,new QTableWidgetItem("0"));
                }
                else{
                    if(!left) left++;
                    int rands = static_cast<int>(rand()* fraction *(right_t - left_t + 1) + left_t);
                    QString t= QString::number(rands);
                    ui->matrix2->setItem(i,j,new QTableWidgetItem(t));
                }
            }
}

void MainWindow::on_creatematrix3_clicked()
{
    ui->matrix3->setColumnCount(ui->countm3->text().toInt());
    ui->matrix3->setRowCount(1);
    ui->matrix3->horizontalHeader()->setMaximumSectionSize(50);
    ui->matrix3->horizontalHeader()->setMinimumSectionSize(0);
    ui->matrix3->verticalHeader()->hide();
    ui->matrix3->verticalHeader()->setMaximumSectionSize(50);
    ui->matrix3->verticalHeader()->setMinimumSectionSize(0);
    ui->matrix1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->matrix1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->matrix2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->matrix2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for (int i = 0; i < ui->countm3->text().toInt();i++) ui->matrix3->setColumnWidth(i,25);
    ui->matrix3->setRowHeight(0,25);

}

void MainWindow::on_random3_clicked()
{
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        int left = 1, right = 2;
        MainWindow::on_creatematrix3_clicked();
        srand(static_cast<unsigned int>(time(0)));
        //int randd = static_cast<int>(rand()* fraction *(right - left + 1) + left);
        for (int i = 0; i < ui->matrix3->columnCount(); i++){
            int rands = static_cast<int>(rand()* fraction *(right - left + 1) + left);
            QString t= QString::number(rands);
            ui->matrix3->setItem(0,i,new QTableWidgetItem(t));
        }
}

void MainWindow::on_next_clicked()
{


    if (window->Qoper != Op &&
        window->matrix1[0][0]!=ui->matrix1->item(0,0)->text().toInt()){
    window->Qoper = Op;
    window->Qwork = R;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < Op; j++)
        {
            window->matrix1[i][j]=ui->matrix1->item(i,j)->text().toInt();
            window->matrix2[i][j]=ui->matrix2->item(i,j)->text().toInt();
        }
    for (int i = 0; i < ui->matrix3->columnCount(); i++) window->matrix3[i] = ui->matrix3->item(0,i)->text().toInt();
    window->NG = ui->matrix3->columnCount();

   for (int i = 0; i < ui->geton->count(); i++){
       QString S;
       S = ui->geton->item(i)->text();
       window->Names.append(S);
   }
    window->NamesCount = ui->geton->count();
    window->show();

    window->creatework();
    }
    else if (window->close()==true){
        window->show();
    }

}

void MainWindow::on_saveButton_clicked()
{
    QJsonObject saved_object;
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                            tr("Save Json File"),
                                                            QString(),
                                                            tr("JSON (*.json)"));
    QFileInfo fileInfo(saveFileName);   // С помощью QFileInfo
    QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл, иначе может не заработать
    // Создаём объект файла и открываем его на запись
    qDebug() <<"ok1";
    QFile jsonFile(saveFileName);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    QJsonArray json_matrix_time, json_matrix_tech, json_vector_group,json_rules;
    for( int i=0; i < ui->matrix1->rowCount(); ++i)
    {
        QJsonArray array_json_1;
        QJsonArray array_json_2;
        for (int j=0; j < ui->matrix1->columnCount();++j)
        {
            array_json_1.append(ui->matrix1->item(i,j)->text().toInt());
            array_json_2.append(ui->matrix2->item(i,j)->text().toInt());
        }
        json_matrix_time.append(array_json_2);
        json_matrix_tech.append(array_json_1);

    }
    for (int i = 0; i < ui->matrix3->columnCount(); ++i)
    {
        json_vector_group.append(ui->matrix3->item(0,i)->text().toInt());
    }
    for (int i =0; i<ui->geton->count();++i)
    {
        json_rules.append(ui->geton->item(i)->text());
    }

    saved_object["num_work"]    = ui->countR->text().toInt();
    saved_object["num_op"]      = ui->countO->text().toInt();
    saved_object["num_groups"]  = ui->countm3->text().toInt();
    saved_object["matrix_time"] = json_matrix_time;
    saved_object["matrix_tech"] = json_matrix_tech;
    saved_object["groups"]      = json_vector_group;
    saved_object["rules"]       = json_rules;
    // Записываем текущий объект Json в файл
    jsonFile.write(QJsonDocument(saved_object).toJson(QJsonDocument::Indented));
    jsonFile.close();   // Закрываем файл
}


void MainWindow::on_loadButton_clicked()
{
    // Выбираем файл
    QString openFileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Json File"),
                                                        QString(),
                                                        tr("JSON (*.json)"));
    QFileInfo fileInfo(openFileName);   // С помощью QFileInfo
    QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл
    // Создаём объект файла и открываем его на чтение
    QFile jsonFile(openFileName);
    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    // Считываем весь файл
    QByteArray saveData = jsonFile.readAll();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
    QJsonObject loaded_object;
    loaded_object = jsonDocument.object();
    if(loaded_object.contains("num_op") && loaded_object["num_op"].isString())
        ui->countO->setText(loaded_object["num_op"].toString());
    if(loaded_object.contains("num_work") && loaded_object["num_work"].isString())
        ui->countR->setText(loaded_object["num_work"].toString());
    if(loaded_object.contains("num_groups") && loaded_object["num_groups"].isString())
        ui->countm3->setText(loaded_object["num_op"].toString());
    ui->matrix2->clear();
    ui->matrix1->clear();
    ui->matrix3->clear();
    ui->geton->clear();
    ui->matrix2->setRowCount( ui->countR->text().toInt());
    ui->matrix2->setColumnCount( ui->countO->text().toInt());
    ui->matrix1->setRowCount( ui->countR->text().toInt());
    ui->matrix1->setColumnCount( ui->countO->text().toInt());
    ui->matrix3->setRowCount(1);
    ui->matrix3->setColumnCount(ui->countm3->text().toInt());
    if(loaded_object.contains("matrix_time") && loaded_object["matrix_time"].isArray())
    {
        QJsonArray json_matrix_time, row;
        json_matrix_time = loaded_object["matrix_time"].toArray();
        for (int i = 0; i < json_matrix_time.size() && i < ui->matrix2->rowCount(); ++i)
        {
            if (json_matrix_time[i].isArray()) {
                row = json_matrix_time[i].toArray();
                for (int j = 0; j<row.size() && j < ui->matrix2->columnCount(); ++j)
                {
                    ui->matrix2->setItem(i,j, new QTableWidgetItem(QString::number(row[j].toInt())));
                }
            }

        }
    }
    if(loaded_object.contains("matrix_tech") && loaded_object["matrix_tech"].isArray())
    {
        QJsonArray json_matrix_tech, row;
        json_matrix_tech = loaded_object["matrix_time"].toArray();
        for (int i = 0; i < json_matrix_tech.size() && i < ui->matrix1->rowCount(); ++i)
        {
            if (json_matrix_tech[i].isArray())
            {
                row = json_matrix_tech[i].toArray();
                for (int j = 0; j<row.size() && j < ui->matrix1->columnCount(); ++j)
                {
                    ui->matrix1->setItem(i,j, new QTableWidgetItem(QString::number(row[j].toInt())));
                }
            }

        }
    }
    if(loaded_object.contains("rules") && loaded_object["rules"].isArray())
    {
        QJsonArray json_rules;
        json_rules = loaded_object["rules"].toArray();
        for (int i = 0; i < json_rules.size();++i)
        {
            ui->geton->addItem(json_rules[i].toString());
        }
    }
    if(loaded_object.contains("groups") && loaded_object["groups"].isArray())
    {

        QJsonArray json_groups;
        json_groups = loaded_object["groups"].toArray();
        for (int i = 0; i < json_groups.size();++i)
        {
            ui->matrix3->setItem(0,i, new QTableWidgetItem(QString::number(json_groups[i].toInt())));
        }
    }
    jsonFile.close();
}



