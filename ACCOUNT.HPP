#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include "CLIENT.HPP"

#include <vector>

class ACCOUNT//: public CLIENT
{
private:
    int numAcc; //ACCOUNT NUMBER
    float money; //AMOUNT OF MONEY IN THIS ACCOUNT
    std::vector<int>co_owners; // CONTAIN ID OF CO-OWNERS OF THIS ACCOUNT
    std::vector<std::pair<CLIENT,std::vector<ACCOUNT>>> clientAndAccount; // CONTAINS PAIR OF CLIENT AND HIS ACCOUNTS
public:
    friend class INTERFACE;
    int numberCount=1000;
    ACCOUNT() {};
    ACCOUNT(int num_acc, float money=0);
    ~ACCOUNT() {};
    void BankBalance(int& userID, int& accountIndex);
    void AddMoney(int& userID,int& accountIndex,int& moneyToAdd);
    void WithdrawMoney(int& userID,int& accountIndex,int& moneyToWithdraw);
    void DeleteAccount(int& userID, int& accountIndex, char deleteUser='n');
    void AddCoowner(int& coownerID, int& userID, int& accountIndex);
    void SendMoney(int& userID,int& accountIndex,int& foundID,int& foundAccNumber, int& moneyToSend);
};



#endif
