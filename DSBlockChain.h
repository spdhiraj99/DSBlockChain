#ifndef DS_BLOCKCHAIN_H

#define DS_BLOCKCHAIN_H

#include <iostream>
#include <vector>
#include <map>
#include "vendor/sha256/sha256.h"

// Transaction class - Represents a Transaction
class Transaction
{
private:
    std::string from;
    std::string to;
    std::string dateTime;
    std::string amt;
    std::string currency;
public:
    Transaction(std::string from, std::string to, std::string dateTime, std::string amt, std::string currency);
    std::string toString();
};

// Block Header, Acts as the Header of a block, which can contain details like previous hash, current hash, nonce etc
class DSBlockHeader
{
private:
    std::string prevBlockHash;
    std::string ownHash;
public:
    DSBlockHeader();
    DSBlockHeader(std::string prevBlockHash, std::string ownHash);
    std::string getOwnHash();
    void setOwnHash(std::string ownHash);
    std::string getPrevBlockHash();
    void setPrevBlockHash(std::string prevHash);
    std::string toString();
};

//Block Body, Acts as the main Body of a block and usually holds all transactions that make up the block
class DSBlockBody
{
private:
    std::vector<Transaction> transactions;
public:
    DSBlockBody();
    DSBlockBody(std::vector<Transaction> transactions);
    bool addTransaction(Transaction transaction);
    std::string toString();
};

//Block class, made up of header and body;
typedef unsigned long long ULL;
class DSBlock
{
private:
    DSBlockHeader header;
    DSBlockBody body;
    ULL nonce = 0;
public:
    DSBlock();
    DSBlock(std::string prevHash, std::string ownHash);
    void setPrevBlockHash(std::string prevBlockHash);
    std::string getPrevBlockHash();
    void calculateSelfHash();
    void reCalculateHashByIncrementingNonce();
    std::string getOwnHash();
    bool addTransaction(Transaction transaction);
    std::string toString();
    void setNonce(ULL nonce);
    ULL getNonce();
    void reInit();
};

class DSBlockChain{
private:
    std::map<std::string, DSBlock> chain;
    std::string headBlockHash;
public:
    DSBlockChain(){}
    bool addToChain(DSBlock& dsBlock);
    DSBlock getBlockOfHash(std::string hashString);
    DSBlock getHeadBlock();
    std::string getHeadBlockHash(){
        return this->headBlockHash;
    }
};
#endif
