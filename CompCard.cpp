#include "CompCard.h"

CompCard::CompCard(const QString& acctNo, const QString& pwd,
                   const QString& name, const QString& gender,
                   const QString& address, const QString& phone,
                   const QString& idNum, double rate, double creditLimit)
    : Account(acctNo,pwd,name,gender,address,phone,idNum)
    , Debit(acctNo,pwd,name,gender,address,phone,idNum,rate)
    , Credit(acctNo,pwd,name,gender,address,phone,idNum,creditLimit) {}

void CompCard::withdraw(double amt) {
    try {
        Debit::withdraw(amt);
    } catch (std::runtime_error&) {
        double remaining = amt - m_balance;
        // Withdraw all possible from debit
        Debit::withdraw(m_balance);
        // Use credit for the rest
        Credit::withdraw(remaining);
    }
}

double CompCard::calculateInterest() const {
    // Sum interest earned (debit) and interest owed (credit)
    double debitInterest = Debit::calculateInterest();
    double creditInterest = Credit::calculateInterest();
    return debitInterest - creditInterest;
}
