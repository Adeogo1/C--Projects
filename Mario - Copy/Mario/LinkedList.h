#pragma once
#include "Commons.h"
#include <iostream>
using namespace std;



class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	ListNode* MakeNode(ListNode** head, int d);
	ListNode* InsertFirst(ListNode** head, int d);
	void InsertAfter(ListNode* lastNode, int d);
	void DeleteList(ListNode** node);
	void DeleteAfter(ListNode* node);
	void DeleteNodeAtPos(ListNode* node, int pos);
	ListNode* GetNode(ListNode* node, int pos);
	ListNode* FindNode(ListNode* node, int pos);
	ListNode* Find(ListNode* node, int val);
	void PrintList(ListNode* node);
	void PrintListBackwards(ListNode* node);

private:
	ListNode* head = nullptr;
	//ListNodeTexture* headTex = nullptr;
	//ListNodeMaps* headMap = nullptr;

};
