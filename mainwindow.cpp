#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cardNum->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
    ui->phone_num->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
    ui->sumBuy->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
}

void MainWindow::on_okNum_clicked(){
    string num_card;
    num_card = ui->cardNum->text().toStdString();
    if (num_card == ""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Введите номер карты");
        msgBox.exec();
    }else {
        if(cards.count(num_card) > 0){
            if(purchases.size() > 0){
                for (int i = 0; i < purchases.size(); ++i) {
                    purchases.setIteratorIndex(i);
                    if(purchases.getIteratorValue().Get_card_number() == num_card){
                        ui->phone_num->setText(QString::fromStdString(purchases.getIteratorValue().Get_phone_number()));
                        ui->checkAct->setChecked(purchases.getIteratorValue().Get_activator());
                        ui->phone_num->setReadOnly(true);
                    }
                }

            }
        } else{
            cards.insert(num_card);
            ui->phone_num->setReadOnly(false);
        }
        ui->cardNum->setReadOnly(true);
        ui->sumBuy->setReadOnly(false);
        ui->dateTime->setReadOnly(false);
    }
}

void MainWindow::on_okAll_clicked(){
    QDateTime dt = ui->dateTime->dateTime();
    string date1 = dt.date().toString("d M yyyy").toStdString() + " " + dt.time().toString().toStdString();
    vector <int>date = Parse(date1);
    int sum = ui->sumBuy->text().toInt();
    string card_num = ui->cardNum->text().toStdString();
    if (card_num == ""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Введите номер карты");
        msgBox.exec();
    }else if (sum == 0){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Введите сумму покупки");
        msgBox.exec();
    } else{
        string phone_num = ui->phone_num->text().toStdString();
        bool active = ui->checkAct->isChecked();
        cout << date[4] << " " << date[3] << " " << date[0] << " " << date[1] << " " << date[2] << " " << sum << " " << card_num << " " << phone_num << " " << active << endl;
        if(purchases.check_discount(card_num, date[0], date[1]) && phone_num != "" && active == true){
            sum -= sum * 0.05;
        }
        Discount purchase(date[4], date[3], date[0], date[1], date[2], sum, card_num, phone_num, active);
        if(purchases.push(purchase) == 1){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Введите корректную дату");
            msgBox.exec();
        }
    }
    ui->cardNum->clear();
    ui->checkAct->setChecked(false);
    ui->dateTime->minimumDateTime();
    ui->phone_num->clear();
    ui->sumBuy->clear();
    ui->cardNum->setReadOnly(false);
}

void MainWindow::on_count_clicked(){
    string dt1 = ui->from->dateTime().date().toString("d M yyyy").toStdString() + " " + ui->from->dateTime().time().toString().toStdString();
    string dt2 = ui->to->dateTime().date().toString("d M yyyy").toStdString() + " " + ui->to->dateTime().time().toString().toStdString();
    vector <int>date1 = Parse(dt1);
    vector <int>date2 = Parse(dt2);
    Time t1 = {date1[4], date1[3]};
    Time t2 = {date2[4], date2[3]};
    Date d1 = {date1[0], date1[1], date1[2]};
    Date d2 = {date2[0], date2[1], date2[2]};
    string sum = purchases.allSum(t1, t2, d1, d2);
    if (sum == ""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Проверьте правильность введенных данных");
        msgBox.exec();
    } else{
        ui->result->setText(QString::fromStdString(sum));
    }
}

void MainWindow::on_del_clicked(){
    if (ui->cardNum->text().toStdString() != "" && ui->phone_num->text().toStdString() != "" && ui->sumBuy->text().toStdString() != ""){
        string date1 = ui->dateTime->dateTime().date().toString("d M yyyy").toStdString() + " " + ui->dateTime->dateTime().time().toString().toStdString();
        vector <int>date = Parse(date1);
        for (int i = 0; i < purchases.size(); ++i) {
            purchases.setIteratorIndex(i);
            if(purchases.getIteratorValue().Get_card_number() == ui->cardNum->text().toStdString() && purchases.getIteratorValue().Get_time_admin().minute == date[4]
                    && purchases.getIteratorValue().Get_time_admin().hour == date[3] && date[0] == purchases.getIteratorValue().Get_date_admin().day
                    && purchases.getIteratorValue().Get_date_admin().month == date[1] && purchases.getIteratorValue().Get_date_admin().year == date[2]){
                purchases.pop(i);
                cards.erase(purchases.getIteratorValue().Get_card_number());
            }
        }
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Введите данные во все поля");
        msgBox.exec();
    }
    ui->cardNum->clear();
    ui->checkAct->setChecked(false);
    ui->dateTime->minimumDateTime();
    ui->phone_num->clear();
    ui->sumBuy->clear();
    ui->cardNum->setReadOnly(false);
}

void MainWindow::on_save_triggered(){
    purchases.toFile();
    saving = true;
}

void MainWindow::on_load_triggered(){
    purchases.intoFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_write_clicked(){
    string buys = "";
    for (int i = 1; i < purchases.size(); i++){
            purchases.setIteratorIndex(i);
            buys +=  "name: " + purchases.getIteratorValue().Get_time_and_date() + "\nCard:" + purchases.getIteratorValue().Get_card_info() + "\n" +
                    "Sum: " + to_string(purchases.getIteratorValue().Get_sum()) + "\n\n";
        }
    ui->result->setText(QString::fromStdString(buys));
}
















//    if(saving == true){
//        purchases.intoFile();
//        saving = false;
//    } else {
//        QMessageBox msgBox;
//        msgBox.setWindowTitle("Внимание");
//        msgBox.setText("Перед загрузкой сохраните файл");
//        msgBox.exec();
//    }
