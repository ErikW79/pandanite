#pragma once
#include "virtual_chain.hpp"
#include "mempool.hpp"
using namespace std;


class BlockChain : public VirtualChain {
    public:
        BlockChain(Program& program, HostManager& hosts);
        void setMemPool(MemPool * memPool);
        ExecutionStatus addBlock(Block& block);
        ProgramID getProgramForWallet(PublicWalletAddress addr);
        ExecutionStatus verifyTransaction(const Transaction& t);
        map<string, uint64_t> getHeaderChainStats() const;
    protected:
        MemPool * memPool;
};
