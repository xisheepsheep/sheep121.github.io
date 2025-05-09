#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QDataStream>

class Account {
public:
    Account(const QString& acctNo, const QString& pwd,
            const QString& name, const QString& gender,
            const QString& address, const QString& phone,
            const QString& idNum);
    virtual ~Account();

    bool verify(const QString& acctNo, const QString& pwd) const;
    QString getAcctNo() const;

    virtual void deposit(double amt);
    virtual void withdraw(double amt) = 0;
    double balance() const;
    virtual double calculateInterest() const = 0;

    void recordLogin();
    int loginCount() const;

    friend QDataStream& operator<<(QDataStream& out, const Account& a);
    friend QDataStream& operator>>(QDataStream& in, Account& a);

protected:
    QString m_acctNo, m_pwd, m_name, m_gender, m_address, m_phone, m_idNum;
    double m_balance;
    int m_loginCount;
};

#endif // ACCOUNT_H
