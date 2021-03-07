#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<iostream>
#include <string.h>
#include <fstream>
using namespace std;


class account
{
public:
	account();
	~account();
	// prototypes of account clcass and public data memebers
	const char* get_account_number();
	double get_balance();
	void process_deposit(double deposit_amount);
	bool process_withdrawal(double withdraw_amount);
	friend ostream & operator << (ostream& out, const account& obj);
private:
	// priviate data members
	double account_balance;
	char account_number[32], Customer_name[16];
	



};




#endif