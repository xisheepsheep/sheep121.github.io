#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Account.h"
#include "ATM.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnShowInterest_clicked();
    void on_btnNewAcct_clicked();
    void on_btnLogin_clicked();
    void on_btnLogout_clicked();
    void on_btnBalance_clicked();
    void on_btnDeposit_clicked();
    void on_btnWithdraw_clicked();
    void on_btnTransfer_clicked();
    void on_btnDeleteAcct_clicked();
    void on_btnStats_clicked();
    void updateAccountList();
    void updateUIState();

private:
    Account* m_currentUser = nullptr;  // 当前登录用户账户指针
    Ui::MainWindow *ui;
    ATM m_atm;
};

#endif // MAINWINDOW_H