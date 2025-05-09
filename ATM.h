#ifndef ATM_H
#define ATM_H

#include "Account.h"
#include <vector>
#include <memory>

class ATM {
public:
    ATM();
    ~ATM();

    void addAccount(std::unique_ptr<Account> acct);
    void removeAccount(const QString& acctNo);
    Account* login(const QString& acctNo, const QString& pwd);
    Account* findAccount(const QString& acctNo);
    const std::vector<std::unique_ptr<Account>>& accounts() const;

    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);

    double totalAssets() const;
    double avgLoginCount() const;

private:
    std::vector<std::unique_ptr<Account>> m_accounts;
};

#endif // ATM_H
