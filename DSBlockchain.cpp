#include "DSBlockChain.h"

//Transaction Def

Transaction::Transaction(std::string from, std::string to, std::string dateTime, std::string amt, std::string currency){
    this->from = from;
    this->to = to;
    this->dateTime = dateTime;
    this->amt = amt;
    this->currency = currency;
}

std::string Transaction::toString(){
    return "From "+this->from + " To " + this->to + "; on "+ this->dateTime + ";"+this->amt + " "+this->currency;
}

//Block Header def
DSBlockHeader::DSBlockHeader(){}
DSBlockHeader::DSBlockHeader(std::string prevBlockHash, std::string ownHash){
    this->prevBlockHash = prevBlockHash;
    this->ownHash = ownHash;
}
std::string DSBlockHeader::getOwnHash(){
    return this->ownHash;
}
void DSBlockHeader::setOwnHash(std::string ownHash){
    this->ownHash = ownHash;
}
std::string DSBlockHeader::getPrevBlockHash(){
    return this->prevBlockHash;
}
void DSBlockHeader::setPrevBlockHash(std::string prevBlockHash){
    this->prevBlockHash = prevBlockHash;
}
std::string DSBlockHeader::toString(){
    return this->getPrevBlockHash();
}

// Block Body
DSBlockBody::DSBlockBody(){}
DSBlockBody::DSBlockBody(std::vector<Transaction> transcations){
    this->transactions = transactions;
}
bool DSBlockBody::addTransaction(Transaction transaction){
    this->transactions.push_back(transaction);
    return true;
}
std::string DSBlockBody::toString(){
    std::string retVal = "";
    for(auto transaction : this->transactions){
        retVal += "||" + transaction.toString();
    }
    return retVal;
}

//Block
DSBlock::DSBlock(){}
DSBlock::DSBlock(std::string prevHash, std::string ownHash){
    this->header.setOwnHash(ownHash);
    this->header.setPrevBlockHash(prevHash);
}
void DSBlock::setPrevBlockHash(std::string prevBlockHash){
    this->header.setPrevBlockHash(prevBlockHash);
}
std::string DSBlock::getPrevBlockHash(){
    return this->header.getPrevBlockHash();
}
void DSBlock::calculateSelfHash(){
    this->header.setOwnHash(sha256(this->toString()));
}
void DSBlock::reCalculateHashByIncrementingNonce(){
    this->nonce += 1L;
    this->header.setOwnHash(sha256(this->toString()));
}
std::string DSBlock::getOwnHash(){
    return this->header.getOwnHash();
}
bool DSBlock::addTransaction(Transaction t){
    if(this->body.addTransaction(t)){
        this->calculateSelfHash();
        return true;
    }
    return true;
}
std::string DSBlock::toString(){
    return this->header.toString() + this->body.toString() + "||" +std::to_string(nonce);
}
void DSBlock::setNonce(unsigned long long nonce){
    this->nonce = nonce;
}
unsigned long long DSBlock::getNonce(){
    return this->nonce;
}
void DSBlock::reInit(){
    DSBlockHeader newHeader;
    DSBlockBody newBody;
    this->header = newHeader;
    this->body = newBody;
    this->nonce = 0;
}

//Block Chain def
bool DSBlockChain::addToChain(DSBlock& dsBlock){
    dsBlock.setPrevBlockHash(this->headBlockHash);
    dsBlock.calculateSelfHash();
    if(this->chain.find(dsBlock.getOwnHash())!=this->chain.end()){
     return false;
    }
    this->chain[dsBlock.getOwnHash()] = dsBlock;
    this->headBlockHash = dsBlock.getOwnHash();
    dsBlock.reInit();
    return true;
}
DSBlock DSBlockChain::getBlockOfHash(std::string hashString){
    return this->chain[hashString];
}
DSBlock DSBlockChain::getHeadBlock(){
    return this->chain[this->headBlockHash];
}
