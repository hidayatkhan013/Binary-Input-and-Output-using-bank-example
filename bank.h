#ifndef BANK_H
#define BANK_H
#include "account.h"
#include <string.h>


class bank
{
public:
	bank();
	~bank();
	// prototypes of bank class 
	void read_accounts(const string& Name_of_file);
	void process_transactions(string Name_of_file);
	friend ostream& operator << (ostream& out, const bank& obj);

private:
	// private memebrs of bank class and its declearation
	char bank_name[32];
	account account_obj[20];
	int number_of_account;
	int binarySearch(account a[],int first, int last, char search[]);
};





#endif
