/******

Name:				Matthew Saliba
Student #:			3284165
Class:				CSCI204
Lab:				Fri 0830 - 1030
Descrip:			AccountMap Class Header File

******/

#include<iostream>
#include "Account.h"
#include<map>
#include<cstring>
#include<algorithm>

using namespace MYLIB;

struct CompareCharArrays{
	
	bool operator()(const char* a, const char* b) const {
		return string(a) < string(b);
	}
};

class AccountMap {

	public:
		AccountMap();
		~AccountMap();
		
		void loadData(const char *);
	    void displayData();
	
	// private data members
	private:
		std::multimap<const char*, Account,CompareCharArrays>accounts;
		
		// private functions
		bool confirmExt(const char * fileName);
		void fileRead(const char * fileName);

};
