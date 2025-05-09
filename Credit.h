#ifndef CREDIT_H
#define CREDIT_H

#include "Account.h"

enum class CreditLevel { Standard, VIP };

class Credit : public virtual Account {
public:
    Credit(const QString& acctNo, const QString& pwd,
           const QString& name, const QString& gender,
           const QString& address, const QString& phone,
           const QString& idNum, double creditLimit = 5000.0,
           CreditLevel level = CreditLevel::Standard);
    void withdraw(double amt) override;
    double calculateInterest() const override;

    CreditLevel level() const;
    void setLevel(CreditLevel lvl);

private:
    double m_limit;
    CreditLevel m_level;
};

#endif // CREDIT_H
