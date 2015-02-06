/******

Name:				Matthew Saliba
Student #:			3284165
Class:				CSCI204
Lab:				Fri 0830 - 1030
Descrip:			Account Management Class Header File

******/

#include<iostream>
#include "Account.h"
#include<fstream>
#include "OrderedList.h"

using namespace MYLIB; 

class AccountManagement{
	
	public:
	
		// constructors and destructors
		AccountManagement();
		~AccountManagement();
	
		// required functions
		void loadData(const char *);
		void displayData();
		void saveData(const char *);

	private:
		
		// private data members
		OrderedList<Account> members;
		
		// private data functions
		
		void breakData(const char *);
		void breakBin(const char *);
		int checkFileType(const char *);
		void addData(int, std::string, Account &);
		int searchIndex(std::string value, char searchChar);
		std::string createSubString(std::string & value, int startIndex, int finish);
	
};
