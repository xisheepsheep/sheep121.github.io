#include "Account.h"
#include <stdexcept>

Account::Account(const QString& acctNo, const QString& pwd,
                 const QString& name, const QString& gender,
                 const QString& address, const QString& phone,
                 const QString& idNum)
    : m_acctNo(acctNo), m_pwd(pwd),
      m_name(name), m_gender(gender),
      m_address(address), m_phone(phone),
      m_idNum(idNum), m_balance(0.0),
      m_loginCount(0) {}

Account::~Account() {}

bool Account::verify(const QString& acctNo, const QString& pwd) const {
    return m_acctNo == acctNo && m_pwd == pwd;
}

QString Account::getAcctNo() const { return m_acctNo; }

void Account::deposit(double amt) {
    if (amt <= 0) throw std::invalid_argument("存款金额必须大于0");
    m_balance += amt;
}

double Account::balance() const { return m_balance; }

void Account::recordLogin() { ++m_loginCount; }
int Account::loginCount() const { return m_loginCount; }

QDataStream& operator<<(QDataStream& out, const Account& a) {
    out << a.m_acctNo << a.m_pwd << a.m_name << a.m_gender
        << a.m_address << a.m_phone << a.m_idNum
        << a.m_balance << a.m_loginCount;
    return out;
}

QDataStream& operator>>(QDataStream& in, Account& a) {
    in >> a.m_acctNo >> a.m_pwd >> a.m_name >> a.m_gender
       >> a.m_address >> a.m_phone >> a.m_idNum
       >> a.m_balance >> a.m_loginCount;
    return in;
}
