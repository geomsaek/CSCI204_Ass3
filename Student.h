/******

Name:				Matthew Saliba
Student #:			3284165
Class:				CSCI204
Lab:				Fri 0830 - 1030
Descrip:			Student Class Header File

******/

#include<iostream>
#include<string>

class Student{
	
	friend std::ostream &operator<<(std::ostream &, const Student &);
	friend std::istream &operator>>(std::istream &, Student &);
	
	public:
		bool operator<(const Student &)const;
		bool operator<=(const Student &)const;
	 	Student & operator=(const Student &);
		bool operator==(const Student &) const;

		Student();
		~Student();
	
	private:
		int studentNum;
		std::string name;
		std::string email;
		
		
};
