/******

Name:				Matthew Saliba
Student #:			3284165
Class:				CSCI204
Lab:				Fri 0830 - 1030
Descrip:			Student Class Function Definition File

******/

#include<iostream>
#include<string>
#include "Student.h"

// CONSTRUCTORS AND DESTRUCTORS

Student::Student(){
	//studentNum = 0;
	name = "";
	email = "";
}

Student::~Student(){
	studentNum = 0;
	name = "";
	email = "";
}

// OVERLOADED OPERATORS

bool Student::operator<(const Student & exist)const {

	bool end= false;
	int counter = 0;
	bool less = false;
	
	while(end == false){

		if(exist.email[counter] * 1 > email[counter] * 1){
			less = true;
			end = true;
		}else {
			if(exist.email[counter] != email[counter]){
				less = false;
				end = true;
			}
		}
		counter = counter + 1;
	}
	
	return less;

}

bool Student::operator<=(const Student & exist)const{
	
	bool end = false;
	bool less = true;
	int counter = 0;
	
	while(end == false){
		if(!(exist.email[counter] <= email[counter])){
			less = false;
		}
		counter = counter + 1;
	}
	
	return less;
}

Student & Student::operator=(const Student & exist){
	
	studentNum = exist.studentNum;
	name = exist.name;
	email = exist.email;
	
	return *this;
}

bool Student::operator==(const Student & exist)const {
	
	bool same = false;
	if(exist.email == email){
		same = true;
	}
	
	return same;

}

///// STREAM FUNCTIONS

std::ostream & operator<<(std::ostream & out, const Student & exist){

	out << exist.studentNum << ", " << exist.name << ", " << exist.email;
	return out;
}

std::istream & operator>>(std::istream & in, Student & exist){

	std::cout << "Input a number: ";
	in >> exist.studentNum;
	in.clear();
	in.ignore(1000,'\n');	
	std::cout << "Input a name: ";
	getline(in, exist.name);
	
	std::cout << "Input email: ";
	getline(in, exist.email);
	std::cout << std::endl;
	return in;
}