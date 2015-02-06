#include<iostream>
#include "Account.h"
#include<fstream>
#include "OrderedList.h"

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
		MYLIB::OrderedList<Account> members;
		
		// private data functions
		
		void breakData(const char *);
		void breakBin(const char *);
		int checkFileType(const char *);
		void addData(int, std::string, Account &);
		int searchIndex(std::string value, char searchChar);
		std::string createSubString(std::string & value, int startIndex, int finish);
	
};
