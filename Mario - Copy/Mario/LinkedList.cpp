#include "LinkedList.h"



LinkedList::LinkedList()
{
}




ListNode* LinkedList::MakeNode(ListNode** head, int d) {
	ListNode* newNode = new ListNode();
	ListNode* last = *head;
	newNode->data = d;
	newNode->next = nullptr;
	if (*head == nullptr)
	{
		*head = newNode;
		return newNode;
	}

	while (last->next != nullptr)
	{
		last = last->next;
	}
	last->next = newNode;
	return newNode;
}
ListNode* LinkedList::InsertFirst(ListNode** head, int d)//we create a new node, assign it a data value the the pointers around so our new node become the new head node and the old head node becomes the new head node's next
{
	ListNode* newNode = new ListNode;// create a node
	newNode->data = d; //assign data
	newNode->next = *head;// set next of newNode as head
	*head = newNode; //move the head to point to newNode at the front
	return newNode;
}
void LinkedList::InsertAfter(ListNode* lastNode, int d)//
{
	if (lastNode == nullptr)
	{
		cout << "Last node cannot be null ";
		return;
	}
	ListNode* newNode = new ListNode;
	newNode->data = d;
	newNode->next = lastNode->next;
	lastNode->next = newNode;
}
void LinkedList::DeleteList(ListNode** node)
{
	ListNode* pTemp = *node;
	ListNode* next;
	while (pTemp != nullptr)
	{
		next = pTemp->next;
		delete pTemp;
		pTemp = next;
	}
	*node = nullptr;
}
void LinkedList::DeleteAfter(ListNode* node) {
	ListNode* pTemp;
	if (node != nullptr && node->next != nullptr)
	{
		pTemp = node->next;
		node->next = pTemp->next;
		delete pTemp;
	}
}
ListNode* LinkedList::GetNode(ListNode* node, int pos)//to find a node at at given position wre initialise a count and loop through until said count equals the position we wish to find and print the data held within
{
	int count = 0;
	while (node != nullptr)
	{
		if (count == pos)
		{
			cout << "Data stored at position " << pos << " is: " << node->data << endl;
			return node;
		}
		count++;
		node = node->next;
	}
	cout << pos << " was not a valid position... " << endl;
	return nullptr;
}

ListNode* LinkedList::FindNode(ListNode* node, int pos)
{
	int count = 0;
	while (node != nullptr)
	{
		if (count == pos)
		{
			return node;
		}
		count++;
		node = node->next;
	}
	return nullptr;
}

ListNode* LinkedList::Find(ListNode* node, int val) {

	int pos = 0;
	while (node != nullptr)
	{
		if (node->data == val)
		{
			cout << "The value " << val << " exist at position " << pos << endl;
			return node;
		}
		pos++;
		node = node->next;
	}
	cout << val << " does not exist... " << endl;
	return nullptr;
}
void LinkedList::PrintList(ListNode* node) {
	while (node != nullptr)
	{
		cout << setw(5) << "| " << node->data << " |-->";
		node = node->next;

	}

	if (node == nullptr)
	{
		cout << "| NULL |" << endl;
	}
	cout << endl;
}


void LinkedList::PrintListBackwards(ListNode* node) {


	if (node != nullptr)
	{
		PrintListBackwards(node->next);
		//if ()
		//{
		//	cout << setw(5) << "| " << node->data;
		//}
		cout << setw(5) << "| " << node->data << " |-->";

	}

	if (node == nullptr)
	{
		cout << "| NULL |-->";

	}
}


void LinkedList::DeleteNodeAtPos(ListNode* node, int pos) {
	int count = 0;
	ListNode* pTemp;
	while (node != nullptr)
	{
		if (count == pos - 1)
		{
			if (node->next != nullptr)
			{
				pTemp = node->next;
				node->next = pTemp->next;
				delete pTemp;
			}
			return;

		}
		count++;
		node = node->next;
	}
	cout << pos << " was not a valid position... " << endl;
}

LinkedList::~LinkedList()
{
}
