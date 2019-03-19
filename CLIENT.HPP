#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>


class CLIENT
{
private:
    int id; // CLIENT'S ID
    std::string firstName; // CLIENT'S FIRST NAME
    std::string lastName; // CLIENT'S LAST NAME
    std::string password; // CLIENT'S PASSWORD
public:
    friend class INTERFACE;
    int idCount=0; // COUNTER OF CLIENT'S ID
    CLIENT() {};
    CLIENT(int id,std::string fname,std::string lname,std::string password);
    ~CLIENT() {};
};



#endif


