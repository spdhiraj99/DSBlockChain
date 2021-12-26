#include <iostream>
#include "DSBlockChain.h"
int main()
{
    DSBlockChain blockChain;
    DSBlock block;
    block.setPrevBlockHash("sa");
    Transaction t("dhiraj", "lay", "29/10/2021", "231", "DSCoin");
    Transaction t1("dhiraj", "layt", "21/10/2021", "231", "DSCoin");
    Transaction t2("dhiraj", "layl", "21/09/2021", "238", "DSCoin");
    block.addTransaction(t);
    block.addTransaction(t1);
    std::cout<<"Initial hash with nonce "<<block.getNonce()<<" "<<block.getOwnHash()<<std::endl;
    block.reCalculateHashByIncrementingNonce();
    std::cout<<"hash with nonce "<<block.getNonce()<<" " << block.getOwnHash()<<std::endl;
    blockChain.addToChain(block);
    return 0;
}
