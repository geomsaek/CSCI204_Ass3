#include<iostream>

class IntStack {
	enum { ssize = 100 };
	int stack[ssize];
	int top;
	
	public:
		IntStack() : top(0) {}
		void push(int i) { if(top < ssize) stack[top++] = i; }
		int pop() {
		
			if(top > 0)
				return stack[--top];
			else
				return 0;
		}
		
		class iterator;
		friend class iterator;
		
		class iterator {
			IntStack& s;
			int index;
			
			public:
				iterator(IntStack& is) : s(is), index(0) {}
				
				// To create the "end sentinel" iterator:
				iterator(IntStack& is, bool) : s(is), index(s.top) {}
				int current() const { return s.stack[index]; }
				int operator++() { // Prefix
					if(index < s.top)
						return s.stack[++index];
					else
						return 0;
				}
				
				int operator++(int) { // Postfix
					if (index < s.top)
						return s.stack[index++];
					else 
						return 0;
					
				}
				
				// Jump an iterator forward
				iterator& operator+=(int amount) {
					if(index + amount < s.top)
						index += amount;
					return *this;
				}
				
				// To see if you're at the end:
				bool operator==(const iterator& rv) const {
					return index == rv.index; }
				
				bool operator!=(const iterator& rv) const {
					return index != rv.index; }
				
				friend std::ostream& operator<<(std::ostream& os, const iterator& it) {
					return os << it.current(); }
		};
				
		iterator begin() { return iterator(*this); }
				
		// Create the "end sentinel":
		iterator end() { return iterator(*this, true); }

};

int main(){

	IntStack is;
	for(int i = 0; i < 20; i++)
		is.push(i);
	
	std::cout << "Traverse the whole IntStack\n";
	IntStack::iterator it = is.begin();
	
	while(it != is.end())
		std::cout << it++ << std::endl;
	
	std::cout << "Traverse a portion of the IntStack\n";

	IntStack::iterator start = is.begin(), end = is.begin();
	start += 5, end += 15;
	std::cout << "start = " << start << std::endl;
	std::cout << "end = " << end << std::endl;

	while(start != end)
		std::cout << start++ << std::endl;
	return 0;
}