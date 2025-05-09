#include "MainWindow.h"
#include "Account.h"
#include <QMessageBox>
#include "ui_MainWindow.h"
#include "DepositDialog.h"
#include "WithdrawDialog.h"
#include "TransferDialog.h"
#include "Debit.h"
#include "Credit.h"
#include "CompCard.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentUser(nullptr)
{
    ui->setupUi(this);
    connect(ui->btnShowInterest, &QPushButton::clicked, this, &MainWindow::on_btnShowInterest_clicked);
    m_atm.loadFromFile("accounts.dat");
    updateAccountList();
    updateUIState();
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::on_btnLogout_clicked);
}

MainWindow::~MainWindow()
{
    m_atm.saveToFile("accounts.dat");
    delete ui;
}

void MainWindow::updateAccountList()
{
    ui->comboAccounts->clear();
    for (const auto& a : m_atm.accounts())
        ui->comboAccounts->addItem(a->getAcctNo());
}

void MainWindow::updateUIState()
{
    bool loggedIn = (m_currentUser != nullptr);
    ui->btnNewAcct->setEnabled(!loggedIn);
    ui->btnLogin->setEnabled(!loggedIn);
    ui->btnLogout->setEnabled(loggedIn);
    ui->btnBalance->setEnabled(loggedIn);
    ui->btnDeposit->setEnabled(loggedIn);
    ui->btnWithdraw->setEnabled(loggedIn);
    ui->btnTransfer->setEnabled(loggedIn);
    ui->btnDeleteAcct->setEnabled(loggedIn);
    ui->btnStats->setEnabled(loggedIn);
    ui->comboAccounts->setEnabled(loggedIn);
}

void MainWindow::on_btnNewAcct_clicked()
{
    bool ok;
    QString no = QInputDialog::getText(this, "账号", "账号：", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString pwd = QInputDialog::getText(this, "密码", "密码：", QLineEdit::Password, "", &ok);
    if (!ok) return;
    QString name = QInputDialog::getText(this, "姓名", "姓名：", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString gender = QInputDialog::getItem(this, "性别", "性别：", {"男","女"}, 0, false, &ok);
    if (!ok) return;
    QString addr = QInputDialog::getText(this, "地址", "地址：", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString phone = QInputDialog::getText(this, "电话", "电话：", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString idNum = QInputDialog::getText(this, "身份证", "身份证：", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString type = QInputDialog::getItem(this, "类型", "类型：", {"储蓄","信用","复合"}, 0, false, &ok);
    if (!ok) return;

    std::unique_ptr<Account> acct;
    if (type == "储蓄") {
        acct = std::make_unique<Debit>(no,pwd,name,gender,addr,phone,idNum,0.015);
    } else if (type == "信用") {
        QString lvl = QInputDialog::getItem(this, "等级", "等级：", {"Standard","VIP"}, 0, false, &ok);
        if (!ok) return;
        CreditLevel cl = (lvl == "VIP" ? CreditLevel::VIP : CreditLevel::Standard);
        acct = std::make_unique<Credit>(no,pwd,name,gender,addr,phone,idNum,5000,cl);
    } else {
        acct = std::make_unique<CompCard>(no,pwd,name,gender,addr,phone,idNum,0.015,5000);
    }
    m_atm.addAccount(std::move(acct));
    updateAccountList();
    QMessageBox::information(this, "提示", "创建成功");
}

void MainWindow::on_btnLogin_clicked()
{
    bool ok;
    QString no = QInputDialog::getText(this, "登录", "账号：", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString pwd = QInputDialog::getText(this, "登录", "密码：", QLineEdit::Password, "", &ok);
    if (!ok) return;

    Account* a = m_atm.login(no, pwd);
    if (!a) {
        QMessageBox::warning(this, "失败", "账号或密码错误");
        return;
    }
    m_currentUser = a;
    QMessageBox::information(this, "欢迎", "登录成功");
    updateAccountList();
    updateUIState();
}

void MainWindow::on_btnLogout_clicked()
{
    m_currentUser = nullptr;
    QMessageBox::information(this, "退出", "您已退出登录");
    updateUIState();
}

void MainWindow::on_btnBalance_clicked()
{
    double bal = m_currentUser->balance();
    QString msg = QString("余额：%1").arg(bal);
    if (auto cred = dynamic_cast<Credit*>(m_currentUser)) {
        QString level = (cred->level() == CreditLevel::VIP ? "VIP" : "Standard");
        msg += QString("\n信用等级：%1\n信用额度：%2").arg(level).arg(cred->level()==CreditLevel::VIP ? 7500 : 5000);
    }
    QMessageBox::information(this, "余额查询", msg);
}

void MainWindow::on_btnDeposit_clicked()
{
    DepositDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        m_currentUser->deposit(dlg.amount());
        QMessageBox::information(this, "存款", "余额：" + QString::number(m_currentUser->balance()));
    }
}

void MainWindow::on_btnWithdraw_clicked()
{
    WithdrawDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        try {
            m_currentUser->withdraw(dlg.amount());
            QMessageBox::information(this, "取款", "余额：" + QString::number(m_currentUser->balance()));
        } catch (std::exception& e) {
            QMessageBox::warning(this, "失败", e.what());
        }
    }
}

void MainWindow::on_btnTransfer_clicked()
{
    TransferDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QString to = dlg.recipient();
        double amt = dlg.amount();
        Account* recv = m_atm.findAccount(to);
        if (!recv) {
            QMessageBox::warning(this, "错误", "接收账号不存在");
            return;
        }
        try {
            m_currentUser->withdraw(amt);
            recv->deposit(amt);
            QMessageBox::information(this, "转账", "已转账：" + QString::number(amt));
        } catch (std::exception& e) {
            QMessageBox::warning(this, "失败", e.what());
        }
    }
}

void MainWindow::on_btnDeleteAcct_clicked()
{
    QString no = m_currentUser->getAcctNo();
    m_atm.removeAccount(no);
    m_currentUser = nullptr;
    QMessageBox::information(this, "删除", "账户已删除");
    updateAccountList();
    updateUIState();
}

void MainWindow::on_btnStats_clicked()
{
    double total = m_atm.totalAssets();
    double avg = m_atm.avgLoginCount();
    QMessageBox::information(this, "统计", QString("总资产：%1\n平均登录：%2").arg(total).arg(avg));
}

void MainWindow::on_btnShowInterest_clicked()
{
    double interest = m_currentUser ? m_currentUser->calculateInterest() : 0.0;
    QMessageBox::information(this, tr("利息信息"), tr("当前累计利息为：%1").arg(interest));
}