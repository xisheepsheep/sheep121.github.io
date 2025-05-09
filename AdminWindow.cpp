#include "AdminWindow.h"
#include "ui_AdminWindow.h"
#include <QMessageBox>

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    connect(ui->btnViewStatistics, &QPushButton::clicked, this, &AdminWindow::viewStatistics);
    connect(ui->btnQueryAccount, &QPushButton::clicked, this, &AdminWindow::queryAccount);
    connect(ui->btnFreezeAccount, &QPushButton::clicked, this, &AdminWindow::freezeAccount);
    connect(ui->btnSetInterestRate, &QPushButton::clicked, this, &AdminWindow::setInterestRate);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::viewStatistics()
{
    QMessageBox::information(this, "统计", "查看银行统计功能");
}

void AdminWindow::queryAccount()
{
    QMessageBox::information(this, "查询账户", "查询账户功能");
}

void AdminWindow::freezeAccount()
{
    QMessageBox::information(this, "冻结账户", "冻结账户功能");
}

void AdminWindow::setInterestRate()
{
    QMessageBox::information(this, "设置利率", "设置利率功能");
}









void AdminWindow::on_btnQuery_clicked()
{
    // Basic implementation of the button click event
    QMessageBox::information(this, "Query Button", "Query button clicked!");
}
