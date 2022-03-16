#include "BinaryTree.h"



BinaryTree::BinaryTree()
{
}






TreeNode* BinaryTree::MakeNode(char data) {
	TreeNode* newNode;

	newNode = new TreeNode();

	newNode->output = data;
	newNode->LeftTree = nullptr;
	newNode->RightTree = nullptr;
	return newNode;
}

TreeNode* BinaryTree::MakeTree() {
	TreeNode* head = MakeNode('a');
	head->LeftTree = MakeNode('m');
	head->RightTree = MakeNode('j');
	head->RightTree->RightTree = MakeNode('c');
	head->RightTree->LeftTree = MakeNode('k');
	head->RightTree->LeftTree->LeftTree = MakeNode('b');
	head->RightTree->LeftTree->RightTree = MakeNode('r');
	return head;
}

void BinaryTree::preOrderTraverse(TreeNode* t) {
	printf(" %c", t->output);
	if (t->LeftTree != nullptr)
	{
		preOrderTraverse(t->LeftTree);
	}
	if (t->RightTree != nullptr)
	{
		preOrderTraverse(t->RightTree);
	}
}

void BinaryTree::inOrderTraverse(TreeNode* t) {
	if (t->LeftTree != nullptr)
		inOrderTraverse(t->LeftTree);
	printf(" %c", t->output);
	if (t->RightTree != nullptr)
		inOrderTraverse(t->RightTree);
}

void BinaryTree::postOrderTraverse(TreeNode* t) {
	if (t->LeftTree != nullptr)
	{
		postOrderTraverse(t->LeftTree);
	}
	if (t->RightTree != nullptr)
	{
		postOrderTraverse(t->RightTree);
	}
	printf(" %c", t->output);

}

TreeNode* BinaryTree::depthFirstSearch(TreeNode* t, char searchChar) {
	TreeNode* answer = nullptr;
	printf(" %c", t->output);
	if (t->output == searchChar) {
		return t;
	}
	if (t->LeftTree != nullptr) {
		answer = depthFirstSearch(t->LeftTree, searchChar);
	}
	if (answer == nullptr && t->RightTree != nullptr)
	{
		answer = depthFirstSearch(t->RightTree, searchChar);
	}
	return answer;
}

//TreeNode* BinaryTree::BreadthFirstSearch(TreeNode* t, char searchChar) {
//
//}

//void BinaryTree::DeleteTree(TreeNode** t) {
//	TreeNode* pTemp = *t;
//	TreeNode* next;
//	while (pTemp->LeftTree != nullptr)
//	{
//		next = pTemp->LeftTree;
//		delete pTemp;
//		pTemp = next;
//	}
//	while (pTemp->RightTree != nullptr)
//	{
//		next = pTemp->RightTree;
//		delete pTemp;
//		pTemp = next;
//	}
//	*t = nullptr;
//}
void BinaryTree::DeleteTree(TreeNode* t) {
	if (t == nullptr)
	{
		return;
	}
	//first delete both subtrees
	DeleteTree(t->LeftTree);
	DeleteTree(t->RightTree);

	//then delete the node
	cout << "\n Deleting node: " << t->output;
	delete t;

}

BinaryTree::~BinaryTree()
{
}