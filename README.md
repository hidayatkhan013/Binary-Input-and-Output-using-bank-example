# Binary-Input-and-Output-using-bank-example

**Input**

Input for this program consists of two files.

The first file, named accounts.bin, contains a single bank object written out in binary format. This object will be read by the read\_accounts() member function of the bank class (see the member function description below for additional details). See the lectures and notes on the course website covering [Binary Input and Output / Object Serialization](http://faculty.cs.niu.edu/~winans/CS501/Notes/binary_io.html) for a description of the technique you will need to use to read this file. Note that reading an entire bank object using ifstream::read() will be **very** similar to the code in the notes that reads an entire Course object in the course notes.

The second file, named transactions.txt, contains a series of transaction records in ASCII character format, which means that you can use the \&gt;\&gt; operator to read the fields of these records. A typical transaction is shown below. The first field on the transaction record is the date of the transaction, followed by an account number, then the transaction type (&#39;D&#39; for deposit or &#39;W&#39; for withdrawal), and finally a transaction amount.

06/19 1111111111 D 430.00

You will need to declare variables to hold the data read for each of these fields. To read transaction records until end of file is reached, use a loop like the following:

while (trans\_file \&gt;\&gt; date)

{

// Read remaining data of the transaction record.

trans\_file \&gt;\&gt; account\_number;

trans\_file \&gt;\&gt; type;

trans\_file \&gt;\&gt; amount;

// Process this transaction.

. . .

}

where trans\_file is the name of the ifstream variable opened for the transaction file.

You may assume that the transaction file is properly formatted in that the above simplistic logic will not result in a premature EOF or other error.

**Files We Give You**

There are four files on hopper in the directory: /home/hopper/winans/501. Copy them into your assignment 5 project directory.

With the provided Makefile you can build the entire project for Assignment 5 simply by typing the command make.

Running the command make clean will remove all of the object and executable files created by the make command.

You will also receive the two data files named accounts.bin and transactions.txt described in the section: **Input** and a copy of the correct output so you can use it to compare against yours withoput trusting a copy &amp; paste from this web page.

**Files You Must Write**

You will write five files for this assignment:

**account.h**

This header file will contain the class definition for a class called account. The account class represents information about a person&#39;s bank account. The header file must include an appropriate set of [header guards](https://en.wikipedia.org/wiki/Include_guard) to prevent it from being included more than once in the same source file.

_Data Members_

The account class must have the following private data members:

- A current account balance (a double variable)
- An account number (a char array with 32 elements)
- A customer name (a char array with 16 elements)

**Note: Make that sure you code your data members in THE EXACT ORDER LISTED ABOVE and with THE EXACT SAME DATA TYPES.** If you use float instead of double or only make the name array 20 characters long instead of 16, your program will not work correctly.

The above given lengths of the account number and customer name fields includes the space needed for a null-terminator: &#39;\0&#39;

_Member Functions_

The account class definition must contain public prototypes for all of the member functions in the account.cpp source code file described below.

**account.cpp**

This source code file will contain the member function definitions for the account class. The required member functions are described below:

- Default constructor

The default constructor must set the account number and customer name data members to the string literal &quot;None&quot;. The account balance data member must be set to 0.

- get\_account\_number()

This must be a const member function with no parameters. It must return a pointer to a const account number.

- get\_balance()

This must be a const member function with no parameters. It must return the current account balance by value.

- process\_deposit()

This member function must take a double deposit amount and add it to the balance for the bank account. It returns nothing.

- process\_withdrawal()

This member function must take a double withdrawal amount. If the bank account&#39;s balance is less than the withdrawal amount, the member function must return false. Otherwise, subtract the withdrawal amount from the balance of the bank account and return true.

- An overloaded insertion operator to use to print the object. When invoked, it must render the values of the data members for the account on exactly three lines of text in the format shown below:
- Account Number: 0003097439
- Name: John Smith
- Balance: $5234.50

Consult the course notes on [Output Formatting](http://faculty.cs.niu.edu/~winans/CS501/Notes/output_formatting.html) for information on how to ensure that numeric values are rendered properly with two decimal places.

**bank.h**

This header file will contain the class definition for a class called bank. The bank class represents information about a collection of bank accounts. The header file must include an appropriate set of header guards to prevent it from being included more than once in the same source file.

_Data Members_

The bank class must have the following three private data members:

- A bank name (a char array of 32 characters)
- An array of 20 account objects
- An integer that specifies the number of account array elements that are filled with valid data.

Note: Once again, make sure that you code your data members in **the exact order listed above** and with **the exact same data types and sizes.**

_Member Functions_

The bank class definition must contain public prototypes for all of the member functions in the bank.cpp source code file described below.

**bank.cpp**

This source code file will contain the member function definitions for the bank class. The required member functions are described below:

- Default constructor

The default constructor must set the bank name data member to the string literal &quot;None&quot;. The number of accounts data member must be set to 0. No initialization is necessary for the array of account objects, since the account default constructor will automatically be called for every object in the array.

- read\_accounts()

This member function takes one parameter, a string that contains the name of a file. This string parameter can be a C++ string or a C string (your choice). It should not be passed by value and be declared as const since this method has no reason to alter it. The function returns nothing.

This method must do the following:

1. Declare and open an input file stream variable for the file name string passed in as a parameter.
2. Check to make sure the file was opened successfully. If not, print an error message and exit the program.
3. Read the database file into your bank object using the ifstream::read() member function for binary input.
4. Close the file stream variable.
5. Sort the account objects in the array in ascending order by account number using a sorting algorithm of your choice. Note that the account numbers are C strings, which means that you will not be able to compare them using the standard relational operators. The account number is also private data of the account class, so code in the bank will need to call get\_account\_number() for an account object rather than accessing the object&#39;s account number directly. You might find the strcmp() function to be useful here.

Note that the code described above will read data into **all** of the account data members. That includes the bank name, the array of 20 account objects, and the number of array elements filled with valid data. No further initialization of the data members will be needed.

- process\_transactions()

This member function takes one parameter, a string that contains the name of a file of transaction data. This string parameter can be a C++ string or a C string (your choice). The function returns nothing.

The member function must open the specified transaction file for input. Make sure to test that the file was opened successfully; if it wasn&#39;t, print an error message and exit the program.

Before reading any transactions, the function must print a report header and column headers. The function must then read transaction data from the file until end of file is reached.

Each time all of the fields for a given transaction have been read, perform a binary search of the accounts array for the account number given in the transaction. If the account number from the transaction record is present in the accounts array, then the transaction may be processed. For a deposit, simply call the process\_deposit() member function for the object that contains the matching account number, passing it the transaction amount. For a withdrawal, call the process\_withdrawal() member function for the object that contains the matching account number, passing it the transaction amount.

For each transaction record processed, print a line in a transaction report with the data from the record and the updated balance for that account. If the transaction account number was not found in the account array or if a charge exceeded the account&#39;s credit limit (i.e., if the process\_withdrawal() member function returned false), print an appropriate error message instead of the account balance. See the section on **Output** below for the required formatting and messages.

After all transactions have been processed, close the transaction file.

- An overloaded insertion operator to use to print the object. When invoked, this function must first print a descriptive header line that includes the bank name (e.g., &quot;Account Listing for XYZ National Bank&quot;). It must then loop through the array of account objects and print each of the elements that contains account data (i.e., element 0 up to but not including element number of accounts), with one blank line between each account.

Since the account class also has an overloaded insertion operator, you can use it to print each element of the account array.

You are welcome to write additional private member functions for the bank class as you see fit. For example, you may want to put your sorting algorithm code in its own member function and call it from read\_accounts() or place the binary search code in its own member function and call it from process\_transactions().

**main.cpp**

This file will contain the program&#39;s main() function. The logic for this function is quite short:

- Declare a bank object. For this discussion, we&#39;ll call it b.
- Use the bank object to call the member function read\_accounts(), passing the file name &quot;accounts.bin&quot; as an argument to the function.
- Do this: std::cout \&lt;\&lt; b \&lt;\&lt; std::endl; to print all of the accounts for the bank and then skip a blank line.
- Call the process\_transactions() member function for the bank object. Pass the file name &quot;transactions.txt&quot; as an argument to the function.
- Call std::cout \&lt;\&lt; std::endl \&lt;\&lt; b; to skip a blank and print the accounts again.

**Output**

A copy of some sample test output to compare against your own program&#39;s output using the diff command is available on hopper at the pathname: /home/hopper/winans/501/bank.output.txt.

Note: We will change the data when we grade your program. You should make sure that your program can work with difference numbers of accounts. You can easily simulate fewer accounts with the data we provide by hard-coding the number of account elements in your read\_accounts()_after_ you have read in the binary data and set it to different numbers. **IF YOU DO THIS THEN YOU MUST REMOVE IT BEFORE HANDING IN YOUR PROGRAM OR YOU WILL LOSE CREDIT!!!**.

Getting the spacing right can be cumbersome. Points will be removed if your spacing and blank lines differ from the official correct output file on hopper.

A copy of that file has been pasted below for reference (if any discrepancies exist, the file on hopper should be considered authoritative):

Account Listing for Last National Bank

Account Number: 1132264809

Name: Joanna Madsen

Balance: $2805.65

Account Number: 1132774809

Name: Benton Quest

Balance: $87968.23

Account Number: 1202480997

Name: Johnny Quest

Balance: $97733272.23

Account Number: 1234567890-xx

Name: John Smith

Balance: $234234.95

Account Number: 1277480923

Name: Race Bannon

Balance: $234577.23

Account Number: 22795674524-ac

Name: Ima Bum

Balance: $1.50

Account Number: 234202472332-sd

Name: Velma Dinkly

Balance: $277872.23

Account Number: 234534599234-sd

Name: Fred Jones

Balance: $23453272.95

Account Number: 324535543345-sd

Name: Shaggy Rogers

Balance: $3453472.25

Account Number: 327992234-ac

Name: Bill Johnson

Balance: $72.95

Account Number: 435347929234-sd

Name: Daphne Blake

Balance: $10000000.00

Account Number: 5540853032

Name: Trey Donner

Balance: $4850.75

Account Number: 5745734564

Name: Karin Hunt

Balance: $4476.00

Account Number: 6379094723

Name: Blake Reynolds

Balance: $2703.62

Account Number: 7307830409

Name: Jon Mitchell

Balance: $207.45

Account Number: 7415949234

Name: Susan Garcia

Balance: $3738.64

Account Number: 9858542030

Name: Keiko Tanaka

Balance: $11343.82

Account Number: 988736434578-sd

Name: Scoobert Doo

Balance: $34572.00

Account Number: 9916512354-jz

Name: Bill Jefferson

Balance: $2345.72

Transaction Report

Date Account Type Amount New Balance

10/1 1234567890-xx D 1.01 234235.96

10/1 1234567890-xx D 1.00 234236.96

10/1 1234567890-xx D 1.00 234237.96

10/1 1234567890-xx D 1.00 234238.96

10/1 1234567890-xx D 0.01 234238.97

10/1 1234567890-xx D 0.01 234238.98

10/1 1234567890-xx D 0.01 234238.99

10/2 42 D 10000000000.00 \*\*\* Invalid account number \*\*\*

10/2 988736434578-sd W 1000.00 33572.00

10/2 435347929234-sd D 1000.00 10001000.00

10/3 988736434578-sd W 1000.00 32572.00

10/3 435347929234-sd D 1000.00 10002000.00

10/5 22795674524-ac W 100000.00 \*\*\* Insufficient funds \*\*\*

10/5 1277480923 W 0.23 234577.00

10/5 1234567890-xx W 1.99 234237.00

10/6 1202480997 W 97733272.23 0.00

Account Listing for Last National Bank

Account Number: 1132264809

Name: Joanna Madsen

Balance: $2805.65

Account Number: 1132774809

Name: Benton Quest

Balance: $87968.23

Account Number: 1202480997

Name: Johnny Quest

Balance: $0.00

Account Number: 1234567890-xx

Name: John Smith

Balance: $234237.00

Account Number: 1277480923

Name: Race Bannon

Balance: $234577.00

Account Number: 22795674524-ac

Name: Ima Bum

Balance: $1.50

Account Number: 234202472332-sd

Name: Velma Dinkly

Balance: $277872.23

Account Number: 234534599234-sd

Name: Fred Jones

Balance: $23453272.95

Account Number: 324535543345-sd

Name: Shaggy Rogers

Balance: $3453472.25

Account Number: 327992234-ac

Name: Bill Johnson

Balance: $72.95

Account Number: 435347929234-sd

Name: Daphne Blake

Balance: $10002000.00

Account Number: 5540853032

Name: Trey Donner

Balance: $4850.75

Account Number: 5745734564

Name: Karin Hunt

Balance: $4476.00

Account Number: 6379094723

Name: Blake Reynolds

Balance: $2703.62

Account Number: 7307830409

Name: Jon Mitchell

Balance: $207.45

Account Number: 7415949234

Name: Susan Garcia

Balance: $3738.64

Account Number: 9858542030

Name: Keiko Tanaka

Balance: $11343.82

Account Number: 988736434578-sd

Name: Scoobert Doo

Balance: $32572.00

Account Number: 9916512354-jz

Name: Bill Jefferson

Balance: $2345.72
