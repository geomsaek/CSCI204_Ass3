/******

Name:				Matthew Saliba
Student #:			3284165
Class:				CSCI204
Lab:				Fri 0830 - 1030
Descrip:			OrderedList Header File and Function Defs

******/

#include<iostream>
#include<vector>
#include<algorithm>

namespace MYLIB {

	////// LIST NODE CLASS //////
	
	// list node prototypes
	template<class T>class OrderedList;
	template<class T>class listNode;
	template<class T>
	std::istream& operator>>(std::istream&, const listNode<T> &);
	
	
	// ordered list template forward declaration
	template<class T>class OrderedList;
	class Iterator;
	
	
	// list node template class declaration
		
	template<class T>
	class listNode {
		friend std::istream&MYLIB::operator>> <T>(std::istream &, const listNode<T> &);
		friend class OrderedList<T>;
		public:
			listNode();
			~listNode();
			T * curVal;

			listNode * getPrev();
			listNode * getNext();
			
		private:
			// previous next pointers of DLL
			listNode * previous;
			listNode * next;
			T value;
	};
	
	
	////// ORDERED LIST CONTAINER CLASS //////
	
	template<class T>
	std::ostream & operator<<(std::ostream &, const OrderedList<T> &);
	
	template<class T>
	class OrderedList {
		friend class Iterator;
		
		friend std::ostream&MYLIB::operator<< <T>(std::ostream &, const OrderedList<T> &);
		
		private:
		
			// private data members
			class listNode<T> * head;
			class listNode<T> * tail;
			class listNode<T> * DLL;

			// private functions
			void sortList();
			
			///// ITERATOR CLASS
			
		public:
			OrderedList();
			~OrderedList();
			
			void insert(const T &);
			void deleteList();
			
			/////// iterator class ////////
			class iterator {
			
				OrderedList<T> & dl;
				class listNode<T> * pos;
				
				public:
				
					iterator(OrderedList<T> &cur);
					// end of iterator constructor
					iterator(OrderedList<T> &cur, bool end);
					
					bool operator !=(const iterator & rv)const;
					bool operator ==(const iterator & rv)const;
					
					// postfix
					iterator operator++(int dum);
					
					//prefix
					iterator operator++();
					
					T operator*();
					
					
			};
			iterator begin();
			iterator end();
	};
	
	/***************************** LISTNODE FUNCTION DECLARATION *****************************/

	// CONSTRUCTORS AND DECONSTRUCTORS 
	template<class T>
	listNode<T>::listNode(){
		previous = NULL;
		next = NULL;
		
	}

	template<class T>
	listNode<T>::~listNode(){
		
	}
	
	template<class T>
	listNode<T> * listNode<T>::getPrev(){
		return this->previous;
	}
	
	template<class T>
	listNode<T> * listNode<T>::getNext(){
		return this->next;
	}
	
	/***************************** ITERATOR CLASS *****************************/
	
	template<class T>
	OrderedList<T>::iterator::iterator(OrderedList<T> &cur): dl(cur), pos(cur.DLL){}
	
	template<class T>
	OrderedList<T>::iterator::iterator(OrderedList<T> &cur, bool end) : dl(cur), pos(NULL){}
	
	template<class T>
	bool OrderedList<T>::iterator::operator !=(const iterator & rv)const{
		if(rv.pos != pos){
			return true;
		}else {
			return false;
		}
	}
	
	template<class T>
	bool OrderedList<T>::iterator::operator ==(const iterator & rv)const {
		if(rv.pos == pos){
			return true;
		}else {
			return false;
		}
	}
	
	template<class T>
	typename OrderedList<T>::iterator OrderedList<T>::iterator::operator++(int dum){
		iterator temp(*this);
		++(*this);
	    return temp;
	}
	
	template<class T>
	typename OrderedList<T>::iterator OrderedList<T>::iterator::operator++(){

		if(pos->next != NULL){
			pos = pos->next;
		}else {
			pos= NULL;
		}						
		return *this;
	}
	
	template<class T>
	T OrderedList<T>::iterator::operator*(){
		return pos->value;
	}
	
	/***************************** ORDEREDLIST FUNCTION DECLARATIONS *****************************/
	
	// CONSTRUCTORS AND DESTRUCTORS
	template<class T>
	OrderedList<T>::OrderedList(){
		head = NULL;
		tail = NULL;
		DLL = NULL;
	}
	
	template<class T>
	OrderedList<T>::~OrderedList(){
		deleteList();
	}
	
	
	////////// Member function declarations ////////////
	
	// insert new value to linked list
	
	template<class T>
	void OrderedList<T>::insert(const T & newValue){
		
		class listNode<T> * tmp = new listNode<T>;
				
		if(DLL == NULL){
			tmp->previous = NULL;
			tmp->next = NULL;
			tmp->value = newValue;
			
			DLL = tmp;
			tail = tmp;
			head = tmp;
		}else {

			class listNode<T> * cur = head;	

			while(cur->next != NULL){
				cur = cur->next;
			}
			
			tmp->value = newValue;
			tmp->next = cur->next;
			tmp->previous = cur;
			cur->next = tmp;
			tail = cur->next;
			sortList();
		}
		
	}
	
	template<class T>
	void OrderedList<T>::sortList(){

		class listNode<T> * cur = head;
		int count = 0;
		
		std::vector<T>store;

		while(cur->next != NULL){
			store.push_back(cur->value);
			cur = cur->next;
		}
		store.push_back(cur->value);
		std::sort(store.begin(), store.end());

		cur = head;
		
		// copy the contents of the vector to the existing list structure
		while(cur->next != NULL){
			cur->value = store[count];
			count = count + 1;
			cur = cur->next;
		}
		cur->value = store[count];

		// erase the vector
		store.erase(store.begin(), store.end());

	}
	
	template<class T>
	void OrderedList<T>::deleteList(){
		if(DLL != NULL){
			bool removeComplete = false;
	
			class listNode<T> * curDelete = DLL;
	
			while(removeComplete == false){
		
		
				if(DLL->next == NULL){
					removeComplete = true;
				}else {
					curDelete = DLL->next;
					delete DLL;
		
					DLL = NULL;
					DLL = curDelete;
				}
			}
	
			delete DLL;
			DLL = NULL;
			tail = NULL;
			head = NULL;
		}
	}
	
	template<class T>
	typename OrderedList<T>::iterator OrderedList<T>::begin() {
		return iterator(*this);
	}
	
	template<class T>
	typename OrderedList<T>::iterator OrderedList<T>::end(){ 
		return iterator(*this, true); 
	}
	
	
}

/***************************** FRIEND FUNCTIONS *****************************/

// ORDEREDLIST OSTREAM OPERATOR FUNCTION
template<class T>
std::ostream &MYLIB::operator<<(std::ostream & out, const OrderedList<T> & exist){
	
	out << exist;
	
	return out;
}
