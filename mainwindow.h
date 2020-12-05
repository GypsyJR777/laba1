#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <set>
#include <iostream>

#include "queue.h"
#include "discount.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_okNum_clicked();
    void on_okAll_clicked();
    void on_save_triggered();
    void on_load_triggered();
    void on_count_clicked();
    void on_del_clicked();
    void on_write_clicked();

private:
    Ui::MainWindow *ui;
    set<string> cards;
    Queue purchases;
    bool saving{false};
};
#endif // MAINWINDOW_H
