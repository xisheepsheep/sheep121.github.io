#include "Credit.h"

Credit::Credit(const QString& acctNo, const QString& pwd,
               const QString& name, const QString& gender,
               const QString& address, const QString& phone,
               const QString& idNum, double creditLimit,
               CreditLevel level)
    : Account(acctNo,pwd,name,gender,address,phone,idNum),
      m_limit(creditLimit), m_level(level) {}

void Credit::withdraw(double amt) {
    double lim = (m_level == CreditLevel::VIP) ? m_limit * 1.5 : m_limit;
    if (amt <= 0 || m_balance - amt < -lim)
        throw std::runtime_error("超出信用额度或金额非法");
    m_balance -= amt;
}

double Credit::calculateInterest() const {
    // 透支利率：VIP 3%，Standard 5%
    double rate = (m_level == CreditLevel::VIP) ? 0.03 : 0.05;
    if (m_balance < 0) {
        return -m_balance * rate;
    } else {
        return 0.0;
    }
}

CreditLevel Credit::level() const { return m_level; }
void Credit::setLevel(CreditLevel lvl) { m_level = lvl; }
