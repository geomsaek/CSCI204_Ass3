#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include "Account.h"
#include<cmath>
#include "Date.h"

// constructors

Account::Account(){

	accountNum = 0;
	balance = 0.00;
	dob.setDate();
}

Account::~Account(){
	accountNum = 0;
	balance = 0.00;
}

/**************** PUBLIC FUNCTIONS ****************/

void Account::updateAccountNum(long int newNum){ accountNum = newNum; }

void Account::updateName(const char * newName){ strcpy(name, newName); }

void Account::updateGender(char newGender){ sex = newGender; }

void Account::updateBirth(std::string birthString) { dob.setDate(birthString); }

void Account::updateAddress(const char * newAddress){ strcpy(address, newAddress); }

void Account::updateBalance(double newBal){ balance = newBal; }


/**************** OVERLOADED OPERATORS ****************/

// assignment operator
Account & Account::operator=(const Account & curObject){
	
	accountNum = curObject.accountNum;
	strncpy(name, curObject.name,sizeof(name));
	sex = curObject.sex;
	dob = curObject.dob;
	strncpy(address, curObject.address, sizeof(address));
	balance = curObject.balance;
	
	return *this;
}

// less than operator - must be ordered by account number
bool Account::operator<(const Account & curObject)const {
	
	if(accountNum < curObject.accountNum){
		return true;
	}else {
		return false;
	}
}

// less than equal operator
bool Account::operator<=(const Account & curObject)const {

	if(accountNum <= curObject.accountNum){
		return true;
	}else {
		return false;
	}
}

// equal to operator
bool Account::operator==(const Account & curObject)const {
	
	if(balance == curObject.balance){
		return true;
	}else {
		return false;
	}
}

/********** PRIVATE FUNCTIONS **************/

int Account::getIntLen(long int num)const {

	int start = num;
	int count = 0;
	bool end = false;
	
	while(end == false){
		start = start / 10;
		if(start == 0){
			end = true;
		}
		count = count + 1;
	}
	
	return count;
}


/********** CURRENCY MANIPULATOR **************/

std::ostream & Currency(std::ostream & os, int widthLen, int precisionLen, const Account & curMem){
	
	os << "$";
	float frac = fmod(curMem.balance,1);
	
	if(frac != 0){
		os << std::setprecision(2) << std::setiosflags(std::ios::fixed)  << std::setw(10) << std::setfill('0') << curMem.balance;
	}else {
		os << std::setw(10) << std::setfill('0') << std::setprecision(2)<< std::setiosflags(std::ios::showpoint) <<curMem.balance;
	}
	return os;
}


// insertion operator
std::ostream &operator<<(std::ostream & out, const Account & curObject){
	
	out << std::setprecision(7);
	out << std::setw(10);
	out <<  std::setfill('0') << curObject.accountNum;
	out << " ";
	if(strlen(curObject.name) >= 12 && strlen(curObject.name) < 15){
		out << " " << curObject.name << std::setw(2) << std::setfill('\t') << curObject.sex;
		
	}else if(strlen(curObject.name) > 15){
		out << " " << curObject.name << std::setw(2) << std::setfill('\t') << curObject.sex;
	}else {
		out << " " << curObject.name << std::setw(3) << std::setfill('\t') << curObject.sex;
	}
	
	if(strlen(curObject.address) >= 38){
		// larger strings
		out << " " << curObject.dob.toString() << " " << curObject.address << std::setw(2) << std::setfill('\t');
	}else if(strlen(curObject.address) > 34 || strlen(curObject.address) == 38){
		out << " " << curObject.dob.toString() << " " << curObject.address << std::setw(2) << std::setfill('\t');
	}
	else if(strlen(curObject.address) == 34){
		out << " " << curObject.dob.toString() << " " << curObject.address << std::setw(3) << std::setfill('\t');
	}else {
		out << " " << curObject.dob.toString() << " " << curObject.address << std::setw(3) << std::setfill('\t');
	}
	
	Currency(out, 3,3, curObject);
	
	return out;
}

// extraction operator
std::istream &operator>>(std::istream & in, const Account & curObject){
	
	return in;
}

