#include "ATM.h"
#include "Debit.h"
#include <QFile>
#include <QDataStream>
#include <algorithm>

ATM::ATM() {}
ATM::~ATM() {}

void ATM::addAccount(std::unique_ptr<Account> acct) {
    m_accounts.push_back(std::move(acct));
}

void ATM::removeAccount(const QString& acctNo) {
    m_accounts.erase(std::remove_if(m_accounts.begin(), m_accounts.end(),
        [&](const std::unique_ptr<Account>& a){ return a->getAcctNo() == acctNo; }),
        m_accounts.end());
}

Account* ATM::findAccount(const QString& acctNo) {
    for (auto& up : m_accounts)
        if (up->getAcctNo() == acctNo) return up.get();
    return nullptr;
}

Account* ATM::login(const QString& acctNo, const QString& pwd) {
    for (auto& up : m_accounts) {
        if (up->verify(acctNo, pwd)) {
            up->recordLogin();
            return up.get();
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Account>>& ATM::accounts() const {
    return m_accounts;
}

void ATM::saveToFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) return;
    QDataStream out(&file);
    out << quint32(m_accounts.size());
    for (auto& up : m_accounts) out << *up;
}

void ATM::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return;
    QDataStream in(&file);
    quint32 n; in >> n;
    m_accounts.clear();
    while (n--) {
        auto acct = std::make_unique<Debit>("","","","","","","");
        in >> *acct;
        m_accounts.push_back(std::move(acct));
    }
}

double ATM::totalAssets() const {
    double sum=0; for(auto& up: m_accounts) sum+=up->balance(); return sum;
}

double ATM::avgLoginCount() const {
    if(m_accounts.empty()) return 0;
    int tot=0; for(auto& up: m_accounts) tot+=up->loginCount();
    return double(tot)/m_accounts.size();
}
