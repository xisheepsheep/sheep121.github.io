#include "Debit.h"

Debit::Debit(const QString& acctNo, const QString& pwd,
             const QString& name, const QString& gender,
             const QString& address, const QString& phone,
             const QString& idNum, double rate)
    : Account(acctNo,pwd,name,gender,address,phone,idNum),
      m_rate(rate) {}

void Debit::withdraw(double amt) {
    if (amt <= 0 || amt > m_balance)
        throw std::runtime_error("余额不足或金额非法");
    m_balance -= amt;
}

double Debit::calculateInterest() const {
    return m_balance * m_rate;
}
