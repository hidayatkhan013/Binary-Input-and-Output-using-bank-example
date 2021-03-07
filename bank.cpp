#include "bank.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
using namespace std;
//bank class decleartion.
bank::bank()
{
	// to assign ban_name a none value we can not directoly assign value to char array.
	strcpy_s(bank_name, "None");
	number_of_account = 0;
}

bank::~bank()
{

}

void bank::read_accounts(const string& file_name)
{

	// reading account.bin file

	ifstream in_file;
	in_file.open(file_name);
	// if file not found it will generate error
	if (!in_file)
	{
		cerr << "Error - unable to open input file " << file_name << endl;
		exit(1);
	}
	// if file open successfully then it will continuoue its flow
	// to read the bank name from file we read function which will read binary data
	in_file.read((char*)& bank_name, sizeof(bank_name));
	while (in_file)
	{
		// this loop will read the details of bank account holder from binary file untill the end of file
		in_file.read((char*)& account_obj[number_of_account], sizeof(account));
		// it will tell that program read how many persons from file.
		number_of_account++;
	}
	
	in_file.close();


	 //bubble sort to sort the array of account according to its account number
	int size = sizeof(account_obj) / sizeof(account_obj[0]);
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++)
		{
			//strcmp return value are -1 0 1
			//if 0 then the bith strings are equl
			//if -1 mean the first string is less than the 2nd
			// if +1 then the case 2 is in reverse order.
			if (strcmp(account_obj[i].get_account_number(), account_obj[j].get_account_number()) >0) {
				account temp = account_obj[i];
				account_obj[i] = account_obj[j];
				account_obj[j] = temp;
			}
		}
	}

}

void bank::process_transactions(string Name_of_file)
{
	// this function will read the transection file 

	ifstream in_file;
	char date[10], account_num[32], status;
	double amount;
	in_file.open(Name_of_file);
	if (!in_file)
	{
		// if file not found then raise error
		cerr << "Error unable to open input file " << Name_of_file << endl;
		exit(1);
	}
	else {
		// if no error 
		cout << "Transaction Report" << endl;
		
		cout << "Date	" << "Account	" << "Type	" << "Amount	" << "New Balance " << endl;
		
		// read file untill end of the file
		while (in_file)
		{
			in_file >> date;
			in_file >> account_num;
			in_file >> status;
			in_file >> amount;
			
			int first = 0;
			cout << std::fixed;
			cout.precision(3);
			// to calcuate the lenght of array of account type
			int last = sizeof(this->account_obj) / sizeof(this->account_obj[0]);
			// this function will perform binary search if acount number present 
			//it will return index otherwise it will return -1
			int index = binarySearch(this->account_obj,first, last, account_num);
			
			if (index >0)
			{
				index = index - 1;
				// if status of transection is deposite
				if (status == 'D') {
					// if D then then despoite in acount 
					cout << date << "	" << account_num << "	" << status << "	" << amount << "	" << this->account_obj[index].get_balance() << "	" << endl;
					this->account_obj[index].process_deposit(amount);
				}
				else if (status == 'W') {
					// if withdrawl then perform withdrawl 
					bool s= this->account_obj[index].process_withdrawal(amount);
					cout << date << "	" << account_num << "	" << status << "	" << amount << "	" << this->account_obj[index].get_balance() << "	" << endl;
					if (!s) { 
						// if account blanace is less than withdrawl then raise error
						cout << date << "	" << account_num << "	" << status << "	" << amount << "	" << "*** Insufficient funds ***" << endl;
					}
				}
			}
			else
			{
				// if account number not found in database
				cout << date << "	" << account_num << "	" << status << "	" << amount << "	" << "*** Invalid account number ***" << endl;
			}
		}

	}

	in_file.close();// closing file


}

int bank::binarySearch(account a[], int first, int last, char search[])
{
	int middle;
	// binary search function
	if (last >= first)
	{
		middle = (first + last) / 2;
		//Checking if the element is present at middle loc
		if (strcmp(a[middle].get_account_number(), search) == 0)
		{
			return middle + 1;
		}
		//Checking if the search element is present in greater half
		else if (strcmp(a[middle].get_account_number(), search) <0)
		{
			return binarySearch(a,middle + 1, last, search);
		}

		//Checking if the search element is present in lower half
		else
		{
			return binarySearch(a,first, middle - 1, search);
		}

	}
	return -1;
}

ostream& operator<<(ostream& out, const bank& obj)
{
	// overloaded insertion  for bank 
	out << "Account Listing for " << obj.bank_name << endl;
	for (size_t i = 0; i < 20; i++)
	{
		// using account overloaded insertion  function here
		 out<<obj.account_obj[i];

	}

	return out;
}
