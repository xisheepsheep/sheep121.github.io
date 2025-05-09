#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QStandardItemModel>

namespace Ui { class AdminWindow; }

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
        void viewStatistics();
        void queryAccount();
        void freezeAccount();
        void setInterestRate();
        void on_btnQuery_clicked();
    

private:
    Ui::AdminWindow *ui;
    QStandardItemModel *model;
    void loadStats();
    void loadTransactions(const QDate &from, const QDate &to);
};

#endif // ADMINWINDOW_H
