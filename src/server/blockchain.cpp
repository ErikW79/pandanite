#include "blockchain.hpp"



ProgramID BlockChain::getProgramForWallet(PublicWalletAddress addr) {
    if (this->program.hasWalletProgram(addr)) return this->program.getWalletProgram(addr).getId();
    return NULL_SHA256_HASH;
}

void BlockChain::setMemPool(MemPool * memPool) {
    this->memPool = memPool;
}

ExecutionStatus BlockChain::verifyTransaction(const Transaction& t) {
    if (this->isSyncing) return IS_SYNCING;
    if (t.isFee()) return EXTRA_MINING_FEE;
    if (!t.signatureValid()) return INVALID_SIGNATURE;
    
    // verify the transaction is consistent with ledger
    std::unique_lock<std::mutex> ul(lock);
    LedgerState deltas;
    ExecutionStatus status = this->program.executeTransaction(t, deltas);

    //roll back the ledger to it's original state:
    this->program.rollback(deltas);
    return status;
}

ExecutionStatus BlockChain::addBlock(Block& block) {
    ExecutionStatus status = VirtualChain::addBlock(block);
    if (status == SUCCESS) {
        this->memPool->finishBlock(block);
    }
}