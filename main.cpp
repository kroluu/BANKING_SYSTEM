#include "ACCOUNT.HPP"
#include "CLIENT.HPP"
#include "INTERFACE.HPP"

int main(int argc, char** argv)
{
	INTERFACE *begin = new INTERFACE;
	begin->RunBankingSystem(); // RUN BANK SYSTEM
	delete begin;
}
