#include "ACCOUNT.HPP"
#include "CLIENT.HPP"

#include <iostream>
#include <algorithm>


/// ACCOUNT'S CONSTRUCTOR WITH PARAMS
ACCOUNT::ACCOUNT(int numAcc, float money)
{
    this->numAcc=numAcc;
    this->money=money;
}

/// PRINT ACCOUNT BALANCE
void ACCOUNT::BankBalance(int& userID, int& accountIndex)
{
    std::cout<<"BANK BALANCE: "<<clientAndAccount[userID].second[accountIndex].money<<"\n\n";
    return;
}

/// ADD MONEY TO ACCOUNT
void ACCOUNT::AddMoney(int& userID,int& accountIndex,int& moneyToAdd)
{
    clientAndAccount[userID].second[accountIndex].money += moneyToAdd;
    return;
}

/// WITHDRAW MONEY FROM ACCOUNT
void ACCOUNT::WithdrawMoney(int& userID, int& accountIndex, int& moneyToWithdraw)
{
    if((clientAndAccount[userID].second[accountIndex].money - moneyToWithdraw) < 0)
        throw std::string("\nAccount has insufficient funds !\n\n");

    clientAndAccount[userID].second[accountIndex].money -= moneyToWithdraw;
    return;
}

/// SEND MONEY TO OTHER ACCOUNT
void ACCOUNT::SendMoney(int& userID, int& accountIndex, int& foundID, int& foundAccNumber, int& moneyToSend)
{
    if((clientAndAccount[userID].second[accountIndex].money - moneyToSend) < 0) // CHECK IF ACCOUNT HAS MONEY
        throw std::string("\nAccount has insufficient funds !\n\n");

    clientAndAccount[userID].second[accountIndex].money -= moneyToSend;
    clientAndAccount[foundID].second[foundAccNumber].money += moneyToSend;
    return;
}

/// ADD CO-OWNER TO ACCOUNT
void ACCOUNT::AddCoowner(int& coownerID, int& userID, int& accountIndex)
{
    if(coownerID==userID) // CHECK IF USER HAS ACCESS
        throw std::string("You already have access to your accounts !\n\n");
    for(size_t i=0;i<clientAndAccount[coownerID].second.size();i++)
        if(clientAndAccount[coownerID].second[i].numAcc == clientAndAccount[userID].second[accountIndex].numAcc)
            throw std::string("You already share account with this client !\n\n");
    clientAndAccount[coownerID].second.push_back(clientAndAccount[userID].second[accountIndex]);

    sort(clientAndAccount[coownerID].second.begin(), clientAndAccount[coownerID].second.end(),
         [](const auto& first, const auto& second) ->bool {return first.numAcc < second.numAcc;});
    return;
}

/// DELETE ACCOUNT OR CLIENT
void ACCOUNT::DeleteAccount(int& userID, int& accountIndex, char deleteUser)
{
    switch(deleteUser)
    {
    case 'y': // DELETE CLIENT
        clientAndAccount.erase(clientAndAccount.begin()+userID);
        break;
    case 'n': // DELETE ACCOUNT
        clientAndAccount[userID].second.erase(clientAndAccount[userID].second.begin()+accountIndex);
        break;
    }
}

