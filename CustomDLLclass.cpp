// Assignment 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class intNode
{
	public:
		intNode* const getNext();
		intNode* const getPrev();
		int const getValue();
		void setNext(intNode* next);
		void setPrev(intNode* prev);
		void setValue(int val);
		void const print();
		intNode(int dataInput, intNode* nextptr, intNode* prevptr);
	private:
		intNode* nextNodeptr;
		intNode* prevNodeptr;
		int dataVal;
};
intNode::intNode(int dataInput, intNode* nextptr, intNode* prevptr) 
{
	this->dataVal = dataInput;
	this->nextNodeptr = nextptr;
	this->prevNodeptr = prevptr;
}
void const intNode::print()
{
	std::cout << dataVal << std::endl;
}
intNode* const intNode::getNext() 
{
	return this->nextNodeptr;
}
intNode* const intNode::getPrev()
{
	return this->prevNodeptr;
}
int const intNode::getValue()
{
	return this->dataVal;
}
void intNode::setNext(intNode* next) 
{
	nextNodeptr = next;
}
void intNode::setPrev(intNode* prev)
{
	prevNodeptr = prev;
}
void intNode::setValue(int val) 
{
	dataVal = val;
}
class dll
{
	public:
		void push(int data);
		void pop();
		void set(int data, int pos);
		int const getSize();
		void const print();
		int at(int index);
		void insert(int data, int pos);
		void remove(int index);
		dll& operator=(const dll& copiedList);
		~dll();
		dll();
		dll(const dll& copiedList);
	private:
		intNode* tail;
		intNode* head;
		int size;
};
dll::dll()
{
	tail = nullptr;
	head = nullptr;
	size = 0;
}
dll& dll::operator=(const dll& copiedList)
{
	std::cout << "Assignment Op Called" << std::endl;
	if (this != &copiedList)
	{
		intNode* deleter = nullptr;
		size = 0;
		do
		{
			deleter = head->getNext();
			head->setValue(0);
			delete head;
			head = deleter;

		} while (deleter != nullptr); // Clear the old list
		intNode* temp = copiedList.head;
		while (temp != nullptr)
		{
			this->push(temp->getValue());
			temp = temp->getNext();
		}
	}
	return *this;
}
void dll::insert(int data, int pos) 
{
	intNode* temp = head;
	if (pos > this->getSize() || pos < 0)
	{
		std::cout << "Invalid Index in Insert function, counting starts at 0" << std::endl;
	}
	else if (pos == 0) // Special handling for index 0
	{
		intNode* newNode = new intNode(data, head, nullptr);
		head->getNext()->setPrev(newNode);
		head = newNode;
		size++;
	}
	else if (pos == this->getSize()) // Inserting at the end is just the push function
	{
		this->push(data);
	}
	else { // Normal functionality
		for (int i = 0; i < pos - 1; i++) 
		{
			temp = temp->getNext();
		}
		intNode* temp2 = temp->getNext();
		intNode* newNode = new intNode(data, temp2, temp);
		temp->setNext(newNode);
		temp2->setPrev(newNode);
		size++;
	}
}
void dll::remove(int pos)
{
	intNode* temp = head;
	if (pos >= this->getSize() || pos < 0)
	{
		std::cout << "Invalid Index in Remove function, counting starts at 0" << std::endl;
	}
	else if (pos == 0) // Special handling for index 0
	{
		temp = head->getNext();
		head->setValue(0);
		delete head;
		head = temp;
		head->setPrev(nullptr);
		size--;
	}
	else if (pos == this->getSize() - 1) // Removing from the end is just the pop function
	{
		this->pop();
	}
	else { // Normal functionality
		for (int i = 0; i < pos - 1; i++) 
		{
			temp = temp->getNext();
		}
		intNode* temp2 = temp->getNext();
		intNode* temp3 = temp2->getNext();
		temp->setNext(temp3);
		temp3->setPrev(temp);
		temp2->setValue(0);
		delete temp2;
		size--;
	}
}
void dll::set(int data, int pos)
{
	intNode* temp = head;
	for (int i = 0; i < pos - 1; i++)
	{
		temp = temp->getNext();
	}
	temp->setValue(data);
}
int dll::at(int index)
{
	if (index >= this->getSize() || index < 0)
	{
		std::cout << "Invalid Index in At function, counting starts at 0" << std::endl;
		return 0;
	}
	intNode* temp = head;
	for (int i = 0; i < index; i++)
	{
		temp = temp->getNext();
	}
	return temp->getValue();
}
dll::dll(const dll& copiedList)
{
	intNode* temp = copiedList.head;
	while (temp != nullptr)
	{
		this->push(temp->getValue());
		temp = temp->getNext();
	}
}
void dll::pop()
{
	intNode* temp = tail->getPrev();
	tail->setValue(0);
	delete tail;
	tail = temp;
	tail->setNext(nullptr);
	size--;
}
void dll::push(int data)
{
	if (size == 0)
	{
		intNode* newNode = new intNode(data, nullptr, nullptr);
		tail = newNode;
		head = newNode;
	}
	else {
		intNode* newNode = new intNode(data, nullptr, tail);
		tail->setNext(newNode);
		tail = newNode;
	}
	size++;
}
int const dll::getSize()
{
	return size;
}
void const dll::print()
{
	intNode* temp = head;
	while (temp != nullptr) 
	{
		temp->print();
		temp = temp->getNext();
	}
}
dll::~dll()
{
	intNode* temp = nullptr;
	do
	{
		temp = head->getNext();
		head->setValue(0);
		delete head;
		head = temp;

	} while (temp != nullptr);
}

int main()
{
	dll doubleLL;
	doubleLL.push(1);
	doubleLL.push(2);
	doubleLL.push(3);

	dll copydll = doubleLL;

	copydll.push(4);
	copydll.remove(1);
	copydll.remove(0);
	copydll.insert(5, 1);

	doubleLL.print();
	copydll.print();

	doubleLL = copydll;
	doubleLL.print();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
