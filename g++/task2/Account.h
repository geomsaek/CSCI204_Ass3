#include<iostream>
#include<string>
#include<cstring>
#include<iomanip>
#include<cstdlib>
#include "Date.h"

class Account{

	friend std::ostream & Currency(std::ostream & os, int, int, const Account &);
	friend std::ostream &operator<<(std::ostream &, const Account &);
	friend std::istream &operator>>(std::istream &, Account &);
	
	public:
		Account();
		~Account();
		
		Account &operator=(const Account &);
		bool operator<(const Account &)const;
		bool operator<=(const Account &)const;
		bool operator==(const Account &) const;
		void updateAccountNum(long int);
		void updateName(const char *);
		void updateGender(char);
		void updateBirth(std::string);
		void updateAddress(const char *);
		void updateBalance(double);
	
	private:
	
		// private functions
		int getIntLen(long int)const;
	
		// private data members
		long int accountNum;
		char name[80];
		char sex;
		MYLIB::Date dob;
		char address[100];
		double balance;
	
};
