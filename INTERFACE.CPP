#include "INTERFACE.HPP"
#include "ACCOUNT.HPP"
#include "CLIENT.HPP"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <conio.h>
#include <cctype>
#include <sstream>
#include <regex>


/// CREATE CLIENT AND ACCOUNT
void INTERFACE::CreateClient()
{
    system("cls");

    //ENTER NAME AND PASSWORD
    std::string clientFirstName,clientLastName,clientPassword;
    std::cout<<"Enter first name: ";
    getline(std::cin,clientFirstName);
    for(auto& x: clientFirstName)
        x=toupper(x);
    std::cout<<"Enter last name: ";
    getline(std::cin,clientLastName);
    for(auto& x: clientLastName)
        x=toupper(x);
    std::cout<<"Enter password: ";
    char getSign;
    do
    {
        getSign = getch();
        if(getSign == 13)
            continue;
        else if(getSign == 8)
        {
            if(clientPassword.size() == 0)
                continue;
            else
            {
                clientPassword.pop_back();
                std::cout<<"\b \b";
            }
        }
        else
        {
            clientPassword+=getSign;
            std::cout<<getSign;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout<<"\b"<<"*";
        }


    }
    while(getSign != 13);

    //ENTER PASSWORD AGAIN
    std::string checkPassword;
    std::cout<<"\nConfirm password: ";
    do
    {
        getSign = getch();
        if(getSign == 13)
            continue;
        else if(getSign == 8)
        {
            if(checkPassword.size() == 0)
                continue;
            else
            {
                checkPassword.pop_back();
                std::cout<<"\b \b";
            }
        }
        else
        {
            checkPassword+=getSign;
            std::cout<<getSign;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout<<"\b"<<"*";
        }
    }
    while(getSign != 13);

    if(clientPassword != checkPassword)
    {
        std::cout<<"\n\nPASSWORDS ARE NOT THE SAME ! \n\n";
        system("pause");
        return;
    }

    //ADD USER TO VECTOR
    int clientID,accountNumber;
    clientID=client.idCount++;
    std::cout<<"\n\nYour ID: "<<clientID;
    CLIENT tmpClient(clientID,clientFirstName,clientLastName,clientPassword);
    accountNumber=account.numberCount++;
    std::cout<<"\nYour account number: "<<accountNumber;
    ACCOUNT tmpAccount(accountNumber);
    std::vector<ACCOUNT> tmpVectorAccount;
    tmpVectorAccount.push_back(tmpAccount);
    account.clientAndAccount.push_back(make_pair(tmpClient,tmpVectorAccount));

    std::cout<<"\n\nUSER CREATED SUCCESSFULLY !\n\n";
    system("pause");
}

/// LOGIN TO CLIENT
void INTERFACE::LoginToClient()
{
    system("cls");

    //CHECK USER ID
    std::cout<<"ID: ";
    std::string checkUserID;
    int userID;
    int userIndex;
    std::getline(std::cin,checkUserID);
    if(CheckIfCinGood(checkUserID) == true)
    {
        std::stringstream(checkUserID) >> userID;
        try
        {
            userIndex=FindClient(userID);
        }
        catch(std::string error)
        {
            std::cout<<error;
            system("pause");
            return;
        }
    }
    else
    {
        std::cout<<"\nBAD LOGIN INPUT !\n\n";
        system("pause");
        return;
    }

    //CHECK USER PASSWORD
    std::string userPassword;
    std::cout<<"PASSWORD: ";
    int loginCount=0;
    bool loginSuccess=false;
    char getSign;
    do
    {
        do
        {
            getSign = getch();
            if(getSign == 13)
                continue;
            else if(getSign == 8)
            {
                if(userPassword.size() == 0)
                    continue;
                else
                {
                    userPassword.pop_back();
                    std::cout<<"\b \b";
                }
            }
            else
            {
                userPassword+=getSign;
                std::cout<<getSign;
                std::cout<<"\b"<<"*";
            }
        }
        while(getSign != 13);

        if(userPassword.compare(account.clientAndAccount[userIndex].first.password)==0)
        {
            std::cout<<"\n\nACCESS GRANTED !\n\n";
            loginSuccess=true;
        }
        else
        {
            userPassword.erase();
            if(loginCount==2)
            {
                std::cout<<"\n\nACCESS DENIED !\n\n";
                std::cout<<account.clientAndAccount[userIndex].first.password;
                system("pause");
                return;
            }

            std::cout<<"\n\nWRONG PASSWORD !\n\n";
            std::cout<<"PASSWORD: ";
        }
    }
    while(loginCount++<2 && loginSuccess==false);

    system("pause");

    //ACCES TO ACCOUNT
    LoginToAccount(userIndex);

    return;

}

/// LOGIN TO CLIENT'S ACCOUNT
void INTERFACE::LoginToAccount(int userID)
{
    system("cls");

    //LIST OF USER'S ACCOUNTS
    std::cout<<"CHOOSE YOUR ACCOUNT:\n";
    std::cout<<"(choice) -> (account number)\n";
    std::cout<<"0 -> Create another account\n";
    for(int i=0; i<(int)account.clientAndAccount[userID].second.size(); i++)
        std::cout<<i+1<<" -> "<<account.clientAndAccount[userID].second[i].numAcc<<"\n";
    short choice;
    std::string inputToCompare;
    bool check=false;
    do
    {
        std::cout<<"\nYour choice: ";
        std::getline(std::cin,inputToCompare);
        if(CheckIfCinGood(inputToCompare))
        {
            std::stringstream(inputToCompare) >> choice;
            if(choice<0 || choice>(int)account.clientAndAccount[userID].second.size())
            {
                std::cout<<"\nBAD CHOICE !\n";
            }
            else if (choice == 0 )
            {
                check=true;
                std::cout<<"\nAccount has been created !\n\n";
                std::cout<<"Account number: "<<account.numberCount<<"\n\n";
                ACCOUNT VectorAccount(account.numberCount++);
                account.clientAndAccount[userID].second.push_back(VectorAccount);
                system("pause");

            }
            else
            {
                check=true;
                AccountManagement(userID,choice-1);
            }
        }
        else
            std::cout<<"\nBAD INPUT !\n";
    }
    while(check==false);



    return;
}

/// DO ACTIONS ON CLIENT'S ACCOUNT
void INTERFACE::AccountManagement(int userID,int accountIndex)
{
    system("cls");
    int choiceAfterCheck;
    std::string choice;
    bool exitAfterDelete=false;
    do
    {
        system("cls");

        AccountMenu(); //LIST OF ACCOUNT'S MENU CHOICES
        std::cout<<"Your choice: ";
        std::getline(std::cin,choice);
        if(CheckIfCinGood(choice)) //CHECK CHOICE
        {
            std::stringstream(choice) >> choiceAfterCheck;
            if(choiceAfterCheck >=0 && choiceAfterCheck <=6)
                system("cls");
            switch(choiceAfterCheck)
            {
            case 1: //PRINT ACCOUNT BALANCE
            {
                account.BankBalance(userID,accountIndex);
            }
            break;

            case 2: //ADD MONEY TO ACCOUNT
            {
                int moneyToAdd;
                std::cout<<"How much money do you want to add: ";
                std::string checkMoneyToAdd;
                std::getline(std::cin, checkMoneyToAdd);
                if(CheckIfCinGood(checkMoneyToAdd) == 1)
                {
                    std::stringstream(checkMoneyToAdd) >> moneyToAdd;
                    account.AddMoney(userID,accountIndex,moneyToAdd);
                    std::cout<<"\nMoney has been added to your account !\n\n";
                }
                else
                    std::cout<<"\nEntered valid value ! \n\n";
            }
            break;

            case 3: //WITHDRAW MONEY FROM ACCOUNT
            {
                std::cout<<"How much money do you want to withdraw: ";
                int moneyToWithdraw;
                std::string checkMoneyToWithdraw;
                std::getline(std::cin,checkMoneyToWithdraw);
                if(CheckIfCinGood(checkMoneyToWithdraw) == 1 ) //CHECK CIN
                {
                    std::stringstream(checkMoneyToWithdraw) >> moneyToWithdraw;
                    try
                    {
                        account.WithdrawMoney(userID,accountIndex,moneyToWithdraw);
                        std::cout<<"\nMoney has been withdrawed !\n\n";
                    }
                    catch(std::string error)
                    {
                        std::cout<<error;
                    }

                }
                else
                    std::cout<<"\nEntered valid value ! \n\n";
            }
            break;

            case 4: //SEND MONEY TO OTHER ACCOUNT
            {
                try
                {
                    std::cout<<"Enter account number of receiver: ";
                    int receiverNumber;
                    std::string checkReceiverNumber;
                    std::getline(std::cin,checkReceiverNumber);
                    if(CheckIfCinGood(checkReceiverNumber) == 0)
                        throw std::string("\nEntered valid value ! \n\n");
                    else
                    {
                        std::stringstream(checkReceiverNumber) >> receiverNumber;
                        auto [FoundID,FoundAccNumber] = FindAccount(receiverNumber); //TRY TO FIND ACCOUNT
                        std::cout<<"\nFirst Name: "<<account.clientAndAccount[FoundID].first.firstName;
                        std::cout<<"\nLast Name: "<<account.clientAndAccount[FoundID].first.lastName;
                        std::cout<<"\n\nHow much money do you want to send: ";
                        int moneyToSend;
                        std::string checkMoneyToSend;
                        std::getline(std::cin, checkMoneyToSend);
                        if(CheckIfCinGood(checkMoneyToSend) == 1)
                        {
                            std::stringstream(checkMoneyToSend) >> moneyToSend;
                            account.SendMoney(userID,accountIndex,FoundID,FoundAccNumber,moneyToSend);
                            std::cout<<"\nMoney has been sent to entered account !\n\n";
                        }
                        else
                            throw std::string("\nEntered valid value ! \n\n");
                    }
                }
                catch(std::string error)
                {
                    std::cout<<error;
                }
            }
            break;

            case 5: //ADD CO-OWNER TO THIS ACCOUNT
            {
                try
                {
                    std::cout<<"Enter user ID: ";
                    int coownerID;
                    std::string checkCoownerID;
                    std::getline(std::cin,checkCoownerID);
                    if(CheckIfCinGood(checkCoownerID) == 0)
                        throw std::string("\nEntered valid value ! \n\n");
                    else
                    {
                        std::stringstream(checkCoownerID) >> coownerID;
                        int FoundID = FindClient(coownerID); //TRY TO FIND CLIENT
                        std::cout<<"\nFirst Name: "<<account.clientAndAccount[FoundID].first.firstName;
                        std::cout<<"\nLast Name: "<<account.clientAndAccount[FoundID].first.lastName<<"\n\n";
                        account.AddCoowner(coownerID,userID,accountIndex);
                        std::cout<<"Co-owner has beed added ! \n\n";
                    }
                }
                catch(std::string error)
                {
                    std::cout<<error;

                }
            }
            break;

            case 6: //DELETE ACCOUNT OR USER
            {

                if(account.clientAndAccount[userID].second.size()==1) //CHECK IF USER HAS ONE ACCOUNT
                {

                    std::cout<<"If you delete this account, you will also delete client from base";
                    std::cout<<"\n\nAre you sure you want to do this (y/n)? ";
                    std::string userChoice;
                    std::getline(std::cin,userChoice);
                    if(userChoice.length()==1) //VALIDATION OF CHAR INPUT
                    {

                        char userChoiceAfterCheck;
                        std::stringstream(userChoice) >> userChoiceAfterCheck;

                        switch(userChoiceAfterCheck)
                        {
                        case'Y': //DELETE USER
                        case'y':
                        {
                            userChoiceAfterCheck = tolower(userChoiceAfterCheck);
                            account.DeleteAccount(userID,accountIndex,userChoiceAfterCheck);
                            std::cout<<"\nUser deleted successfully !\n\n";
                            exitAfterDelete=true;

                        }
                        break;
                        case'N'://CANCEL DELETE
                        case'n':
                        {
                            std::cout<<"\nDeleting account cancelled !\n\n";
                            exitAfterDelete=false;
                        }
                        break;
                        default:
                            std::cout<<"\nBAD CHOICE !\n\n";
                        }
                    }
                    else
                        std::cout<<"\nTRY AGAIN !\n\n";
                }
                else //DELETE ACCOUNT
                {
                    account.DeleteAccount(userID,accountIndex);
                    std::cout<<"Account deleted successfully !\n\n";
                    exitAfterDelete=true;
                }
            }
            break;

            case 7: // LOG OUT
            {
                std::cout<<"\nLOGGED OUT !\n\n";
            }
            break;
            default:
                std::cout<<"\nBAD CHOICE, TRY AGAIN !\n\n";
            }
            system("pause");
        }
    }
    while(choiceAfterCheck!=7 && exitAfterDelete==false);
}


/// LIST OF BANK MENU OPTIONS
void INTERFACE::BankMenu()
{
    std::cout<<"BANKING SYSTEM \n";
    std::cout<<"------------\n";
    std::cout<<"1. Create user\n\n";
    std::cout<<"2. Login\n\n";
    std::cout<<"3. Exit\n\n";
}

/// LIST OF ACCOUNT MENU OPTIONS
void INTERFACE::AccountMenu()
{
    std::cout<<"ACCOUNT MENU \n";
    std::cout<<"------------\n";
    std::cout<<"1. Bank balance\n\n";
    std::cout<<"2. Add money\n\n";
    std::cout<<"3. Withdraw money\n\n";
    std::cout<<"4. Send money\n\n";
    std::cout<<"5. Add Co-owner\n\n";
    std::cout<<"6. Delete account\n\n";
    std::cout<<"7. Log out\n\n\n";
}
/// BANK BEGINNER
void INTERFACE::RunBankingSystem()
{
    INTERFACE *ifaceManager = new INTERFACE;;
    std::string choice;
    int choiceAfterCheck;

    do
    {
        ifaceManager->BankMenu();
        std::cout<<"Your choice --> ";
        std::getline(std::cin,choice);
        if(CheckIfCinGood(choice)) //VALIDATION OF CIN
        {
            std::stringstream(choice) >> choiceAfterCheck;

            switch(choiceAfterCheck)
            {
            case 1:
                ifaceManager->CreateClient();
                system("cls");
                break;
            case 2:
                ifaceManager->LoginToClient();
                system("cls");
                break;
            case 3:
            {
                std::cout<<"\nBanking system is shutting down ";
                char sign='.';
                for(int i=0; i<3; i++)
                {
                    std::cout<<sign;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
            break;
            default:
                std::cout<<"\nBAD CHOICE, TRY AGAIN !\n\n";
                system("pause");
                system("cls");
            }
        }
        else
        {
            std::cout<<"\nBAD INPUT !\n\n";
            system("pause");
            system("cls");
        }

    }
    while (choiceAfterCheck!=3);

    delete ifaceManager;
    // END OF PROGRAM
}

/// FINDS CLIENT IN VECTOR
int INTERFACE::FindClient(int& userID)
{

    for(int i=0; i<(int)account.clientAndAccount.size(); i++)
    {
        if(userID==account.clientAndAccount[i].first.id)
            return i;
    }
    throw std::string("\nUSER DOES NOT EXIST !\n\n");
}

/// FINDS ACCOUNT IN VECTOR
std::pair<int,int> INTERFACE::FindAccount(int& receiverNumber)
{
    for(int i=0; i<(int)account.clientAndAccount.size(); i++)
        for(int j=0; j<(int)account.clientAndAccount[i].second.size(); j++)
            if(account.clientAndAccount[i].second[j].numAcc == receiverNumber)
                return std::make_pair(i,j);
    throw std::string("\nACCOUNT DOES NOT EXIST !\n\n");
}

/// CHECKS IF CIN IS VALID
bool INTERFACE::CheckIfCinGood(const std::string& userInput)
{
    std::regex searchParameters("[[:digit:]]+");
    if(regex_match(userInput,searchParameters))
        return true;
    else
        return false;
}

