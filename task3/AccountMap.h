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
		std::multimap<char *, Account,CompareCharArrays>accounts;
		
		// private functions
		bool confirmExt(const char * fileName);
		void fileRead(const char * fileName);

};
