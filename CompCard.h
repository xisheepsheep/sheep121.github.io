#ifndef COMPCARD_H
#define COMPCARD_H

#include "Account.h"
#include "Debit.h"
#include "Credit.h"

class CompCard : public virtual Account, public Debit, public Credit {
public:
    CompCard(const QString& acctNo, const QString& pwd,
             const QString& name, const QString& gender,
             const QString& address, const QString& phone,
             const QString& idNum, double rate, double creditLimit);
    void withdraw(double amt) override;
    double calculateInterest() const override;
};

#endif // COMPCARD_H
