#include<iostream>
#include "AccountMap.h"
#include<cstring>
#include<fstream>
#include<map>
#include<algorithm>

using namespace MYLIB;

AccountMap::AccountMap(){
	std::multimap<char *, Account,CompareCharArrays>accounts;
}

AccountMap::~AccountMap(){
	accounts.clear();
}

void AccountMap::loadData(const char * fileName){
	
	bool check = false;
	
	check = confirmExt(fileName);
	if(check){
		fileRead(fileName);
	}else {
		std::cout << "Please enter a valid extension type" << std::endl;
	}
}

bool AccountMap::confirmExt(const char * file){
	
	int totalLen = strlen(file);
	int startFind = totalLen - 3;
	char ext[4] = { '\0' };
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
	
	if(strcmp(ext, dat) == 0 || (strcmp(ext, bin) == 0)){
		// return for data
		return true;
	}else {
		return false;
	}
}

void AccountMap::fileRead(const char * fileName){

	// read in from a binary or data file
	

	std::ifstream input;
	input.open(fileName, std::ios::ate | std::ios::binary);
	
	if(!input.good()){
		std::cout << "Bad Reading File" << std::endl;
		input.close();
		return;
	}else {
		int length = 0;
		Account temp;

		length = input.tellg() / sizeof(Account);
		input.close();
		char * tempName = NULL;
		
		input.open(fileName, std::ios::binary);
		if(length > 0){		

			while(!input.eof()){
				input.read((char *)&(temp), sizeof(Account));
				
				tempName = new char[strlen(temp.name) + 1];
				strcpy(tempName, temp.name);
				
				accounts.insert(std::pair<char *, Account>(tempName, temp));
		
			}
		}
		
		delete [] tempName;
		tempName = NULL;
	}

}

void AccountMap::displayData(){

	std::multimap<char *, Account, CompareCharArrays>::iterator i = accounts.begin();
	
	std::cout << std::endl;	
	while(i != accounts.end()){
		std::cout << i->second << std::endl;
		i++;
	}
	std::cout << std::endl;
}

