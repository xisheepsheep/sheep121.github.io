#ifndef DEBIT_H
#define DEBIT_H

#include "Account.h"

class Debit : public virtual Account {
public:
    Debit(const QString& acctNo, const QString& pwd,
          const QString& name, const QString& gender,
          const QString& address, const QString& phone,
          const QString& idNum, double rate = 0.015);
    void withdraw(double amt) override;
    double calculateInterest() const override;

private:
    double m_rate;
};

#endif // DEBIT_H
