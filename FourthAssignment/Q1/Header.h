#pragma once
#ifndef __TREE__
#define __TREE__
/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
/*INCLUDES*/
/*STRUCTS*/
typedef struct __TreeNode
{
	unsigned int data;
	struct __TreeNode* left;
	struct __TreeNode* right;
}TreeNode;
/*STRUCTS*/
typedef struct __tree
{
	struct __TreeNode* root;
}Tree;

/*Declarations*/
Tree BuildTreeFromArray(int* arr, int  size);//Build tree from an array every leaf is an avrage of a semi-array.
void printTreeInorder(Tree tree);//Prints the tree In-order.
void freeTree(Tree *tree);//Deallocate a tree.
/*Declarations*/
#endif // !__TREE__
