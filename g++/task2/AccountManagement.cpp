#include<iostream>
#include "AccountManagement.h"
#include<fstream>

// FUNCTION DEFINITIONS

// constructors and destructors
AccountManagement::AccountManagement(){
	
}

AccountManagement::~AccountManagement(){
	
}

// member functions

void AccountManagement::loadData(const char * file){
	
	std::ifstream readFile;
	readFile.open(file);
	int fileType = 0;
	
	// if the file exists
	if(readFile.good()){
		readFile.close();
		
		fileType = checkFileType(file);
		switch(fileType){
			case 0:
				std::cout << "Please ensure that the file exists" << std::endl;
				readFile.close();
				return;
			break;
			
			case 1:
				// break data for text;
				readFile.close();
				breakData(file);
			break;
			
			case 2:
				readFile.close();
				breakBin(file);
			break;
		}


	}else {
		// if the file doesnt exist
		std::cout << "Please ensure that the file exists" << std::endl;
		readFile.close();
	}

}

void AccountManagement::displayData(){
	
	std::cout << "Output Accounts: " << std::endl;
	MYLIB::OrderedList<Account>::iterator its = members.begin();

	while(its != members.end()) {
        std::cout << *(its) << std::endl;
        its++;
   	}
    std::cout << std::endl;
	
}

void AccountManagement::saveData(const char * file){
	
	std::ofstream output;
	output.open(file, std::ofstream::out | std::ofstream::app | std::ios::binary);

	MYLIB::OrderedList<Account>::iterator its = members.begin();
	Account temp;
	while(its != members.end()) {
		
		temp = *its;
		output.write((char*)&(temp), sizeof(Account));
        its++;
   	}
	output.close();	
}


/******** PRIVATE DATA FUNCTIONS ***********/


void AccountManagement::breakData(const char * fileName){
		
	char separator = ',';
	int comFind = 0, counter = 0;
	
	std::ifstream file;
	file.open(fileName);
	
	std::string tempString, subTemp;
	std::string typeStore = "";	
	Account temp;
	
	
	while(!file.eof()){
		std::getline(file, tempString);

		if(tempString.length() > 20){
			while(tempString != subTemp){
				
				comFind = searchIndex(tempString, separator);

				subTemp = tempString.substr(0, comFind);
				
				addData(counter, subTemp, temp);
				
				tempString = createSubString(tempString, comFind + 1, tempString.length());
				counter = counter + 1;
			}
			members.insert(temp);
		
		}
		counter = 0;
	}
}

void AccountManagement::breakBin(const char * fileName){
	
	// read in from a binary or data file
	
	std::ifstream input;
	input.open(fileName, std::ios::ate | std::ios::binary);
	int length = 0;
	Account temp;
	length = input.tellg() / sizeof(Account);
	input.close();
	
	input.open(fileName, std::ios::binary);
	if(length > 0){
		while(!input.eof()){
			input.read((char *)&(temp), sizeof(Account));
			members.insert(temp);
		}
	}
	
	
}

std::string AccountManagement::createSubString(std::string & value, int startIndex, int finish){

	value = value.substr(startIndex, finish);
	return value;
}

int AccountManagement::searchIndex(std::string value, char searchChar){
	return value.find(searchChar);
}

void AccountManagement::addData(int choice, std::string data, Account & temp){

	switch(choice){
		// add account number
		case 0: {	
				long int tempNum = atol(data.c_str());
				temp.updateAccountNum(tempNum); }
		break;
		
		// add name
		case 1:{
				temp.updateName(data.c_str()); }		
		break;
		
		// add gender
		case 2: {
				temp.updateGender(data[0]); }		
		break;
		
		// add  birthdate
		case 3: {
				temp.updateBirth(data); }
		break;
		
		// update address
		case 4: {
				temp.updateAddress(data.c_str()); }
		break;
		
		// update balance
		case 5: {
				double tempBal = atof(data.c_str());
				temp.updateBalance(tempBal); }
		break;
	}
}

int AccountManagement::checkFileType(const char * file){
	
	int totalLen = strlen(file);
	int startFind = totalLen - 3;
	char ext[4] = { '\0' };
	char txt[] = { "txt" };
	char bin[] = { "bin" };
	char dat[] = { "dat" };
	
	int extCount = 0;
	bool end = false;
	
	while(end == false){
		if(file[startFind] == '\0'){
			end = true;
		}else {
			ext[extCount] = file[startFind];
			extCount = extCount + 1;
		}
		startFind = startFind + 1;
	}
	
	if(strcmp(ext, txt) == 0){
		// return for text
		return 1;
	}else if(strcmp(ext, dat) == 0){
		// return for data
		return 2;
	}else if(strcmp(ext, bin) == 0){
		// return for binary
		return 2;
	}else {
		return 0;
	}
}
