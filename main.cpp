#include<iostream>
#include <fstream>
#include "account.h"
#include "bank.h"

using namespace std;


int main() {
	// making instance of bank class
	bank a;
	// calling read acount function with the help of bank class object
	a.read_accounts("accounts.bin");
	cout << a << endl;
	cout << endl << endl;
	// initiating transection file and 
	a.process_transactions("trans.txt");
	//outputting the bank class object again
	cout << a << endl;



	return 0;
}