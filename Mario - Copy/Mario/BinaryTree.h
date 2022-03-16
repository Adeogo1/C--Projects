#pragma once
#include "Commons.h"
#include <iostream>
using namespace std;




class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	TreeNode* MakeNode(char data);
	TreeNode* MakeTree();
	void preOrderTraverse(TreeNode* t);
	void inOrderTraverse(TreeNode* t);
	void postOrderTraverse(TreeNode* t);
	TreeNode* depthFirstSearch(TreeNode* t, char searchChar);
	TreeNode* BreadthFirstSearch(TreeNode* t, char searchChar);
	void DeleteTree(TreeNode* t);
private:

};


