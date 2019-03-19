#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "ACCOUNT.HPP"
#include "CLIENT.HPP"

struct INTERFACE
{
    ACCOUNT account;
    CLIENT client;
    void BankMenu();
    void AccountMenu();
    void RunBankingSystem();
    void CreateClient();
    int FindClient(int& userID);
    std::pair<int,int> FindAccount(int& receiverNumber);
    void LoginToClient();
    void LoginToAccount(int userID);
    void AccountManagement(int userID, int accountIndex);
    bool CheckIfCinGood(const std::string& userInput);
} ;



#endif
