#include"account.h"

account::account()
{
	// constructor of account class
	strcpy_s(account_number, "None");
	strcpy_s(Customer_name, "None");
	account_balance = 0.0;
}

account::~account()
{

}

const char* account::get_account_number() {
	// to return account number
	return account_number;
}
double account::get_balance() {
	// to return account balance
	return account_balance;
}

void account::process_deposit(double deposit_amount)
{
	// to deposite balance in account
	this->account_balance = this->account_balance + deposit_amount;
}

bool account::process_withdrawal(double withdraw_amount)
{
	// to withdraw amount from account
	if (this->account_balance < withdraw_amount)
		return false;
	else { 
		this->account_balance = this->account_balance - withdraw_amount; 
		return true; 
	}
}

ostream& operator<<(ostream& out, const account& obj)
{
	//overloaded insertion   function for account class
	out <<"Account Number : " << obj.account_number << endl;
	out<<"Name : " << obj.Customer_name << endl;
	out<<"Balance : $" << obj.account_balance << endl;
	cout << endl;
	return out;
}

