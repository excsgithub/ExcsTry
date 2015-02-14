#pragma once

//extern 
class ListInt;
void print(const ListInt& inList);

class ListInt {
public:
	
	class Node {
		public:
		//-----------------DM----------------
		int data;
		Node * next;		
		Node *prev;
		//-----------------Ctors----------------
		Node(int inData):data(inData),next(0),prev(0)
		{}
	};

	

	//-----------------DM----------------
	Node *head;
	Node *tail;
	int size;
	

	//-----------------Ctors----------------
	

public:
	ListInt(void);
	virtual ~ListInt(void);
	void push_front(int inData);
	void push_back(int inData);
	int getSize(void) const;
	void revarse(void);
	int pop_front(void); 
	bool isEmpty();
	int pop_backLong(void);
	int pop_back(void);
	
};

