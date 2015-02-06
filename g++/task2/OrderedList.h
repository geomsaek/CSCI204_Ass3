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
			
			class iterator {
			
				OrderedList<T> & dl;
				class listNode<T> * pos;
				class listNode<T> * listHead;
				class listNode<T> * listTail;
				bool increment;
				
				public:
					iterator(OrderedList<T> &cur) : dl(cur), pos(cur.head), listHead(cur.head), listTail(cur.tail), increment(false){}
					
					// end of iterator constructor
					iterator(OrderedList<T> &cur, bool end) : dl(cur), pos(cur.tail), increment(false){}
					
					bool operator !=(const iterator & rv)const{
						if(rv.pos != pos){
							return true;
						}else {
							return false;
						}
					}
					bool operator ==(const iterator & rv)const {
						if(rv.pos == pos){
							return true;
						}else {
							return false;
						}
					}
					
					
					// postfix
					iterator operator++(int dum){
						checkIncrement();
						increment = true;						
						return iterator(*this);
					}
					
					T operator*(){
						checkIncrement();
						return pos->value;
					}
					//prefix
					iterator operator++(){
						//checkIncrement();
						if(pos->next != NULL){
							pos = pos->next;
						}else {
							pos= listTail;
						}
						
						return iterator(*this);
					}
					
					// function checks whether the value needs to be incremented due to the post increment	
					void checkIncrement(){
						if(increment){
							if(pos->next != NULL){
								pos = pos->next;
							}else {
								pos= listTail;
							}
							increment = false;
						}
					}
					
			};
			iterator begin() { return iterator(*this); }
			iterator end() { return iterator(*this, true); }
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
	
	/***************************** ORDEREDLIST FUNCTION DECLARATIONS *****************************/
	
	
	// CONSTRUCTORS AND DESTRUCTORS
	template<class T>
	OrderedList<T>::OrderedList(){
		head = NULL;
		tail = NULL;
		DLL = NULL;
	}
	
	template<class T>
	OrderedList<T>::~OrderedList(){}
	
	
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
		sort(store.begin(), store.end());
		
		// output the contents of the vector
//		copy(store.begin(), store.end(), std::ostream_iterator<T>(std::cout, "\n"));

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
	
	
}


/***************************** FRIEND FUNCTIONS *****************************/


// ORDEREDLIST OSTREAM OPERATOR FUNCTION
template<class T>
std::ostream &MYLIB::operator<<(std::ostream & out, const OrderedList<T> & exist){
	
	out << exist;
	
	return out;
}


// INSERTION OPERATOR
template<class T>
std::istream &MYLIB::operator>>(std::istream &in, const listNode<T> & ob){
	
	
	
	return in;
}
