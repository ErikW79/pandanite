#pragma once
#include <set>
#include "leveldb/db.h"
#include "../core/common.hpp"
#include "data_store.hpp"
using namespace std;

class Ledger : public DataStore {
    public:
        Ledger();
        bool hasWallet(const PublicWalletAddress& wallet);
        TransactionAmount getWalletValue(const PublicWalletAddress& wallet);
        void createWallet(const PublicWalletAddress& wallet);
        void withdraw(const PublicWalletAddress& wallet, TransactionAmount amt);
        void revertSend(const PublicWalletAddress& wallet, TransactionAmount amt);
        void revertDeposit(PublicWalletAddress to, TransactionAmount amt);
        void deposit(const PublicWalletAddress& wallet, TransactionAmount amt);
        bool hasWalletProgram(const PublicWalletAddress& wallet);
        ProgramID getWalletProgram(const PublicWalletAddress& wallet);
        void setWalletProgram(const PublicWalletAddress& wallet, const ProgramID& program);
        void removeWalletProgram(const PublicWalletAddress& wallet);
    protected:
        void setWalletValue(const PublicWalletAddress& wallet, TransactionAmount amount);
};