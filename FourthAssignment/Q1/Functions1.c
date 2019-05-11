#include "Header.h"
/*Static Declartions*/
static TreeNode *allocateTreeNode(int data);
static void PrintInOrderAux(TreeNode *leaf);
static void freeTreeAux(TreeNode *leaf);
//Utillity functions.
/*Static Declartions*/
void printTreeInorder(Tree tree)
{
	if (tree.root)
		PrintInOrderAux(tree.root);
}
static void PrintInOrderAux(TreeNode *leaf)
{
	if (leaf != NULL)
	{
		PrintInOrderAux(leaf->left);
		printf("%d ", leaf->data);
		PrintInOrderAux(leaf->right);
	}
}
void freeTree(Tree *tree)
{
	if (tree->root)
	{
		freeTreeAux(tree->root);
		tree->root = NULL;
	}
}
static void freeTreeAux(TreeNode *leaf)
{
	if (leaf->right)
		freeTreeAux(leaf->right);
	if (leaf->left)
		freeTreeAux(leaf->left);
	free(leaf);
}
static TreeNode *allocateTreeNode(int data)
{
	TreeNode *node;
	node = (TreeNode *)malloc(sizeof(TreeNode));
	if (node == NULL)
	{
		fprintf(stderr, "Memory allocation error!\n");
		exit(-1);
	}
	node->data = data;
	node->left = node->right = NULL;
	return node;
}
Tree BuildTreeFromArray(int *arr, int size)
{
	Tree tree;
	Tree left;
	Tree right;
	tree.root = (TreeNode *)malloc(sizeof(TreeNode));
	if (tree.root == NULL)
	{
		fprintf(stderr, "Memory allocation error!\n");
		exit(-1);
	}

	if (size == 1)
	{
		tree.root->data = arr[0];
		tree.root->left = tree.root->right = NULL;
	}
	else
	{
		tree.root->data = arr[size / 2];
		if (arr[size /4] == -1)
		{
			tree.root->left = NULL;
		}
		else
		{
			left = BuildTreeFromArray(arr, size / 2);
			tree.root->left = left.root;
		}
		if (arr[(size/2) + 1 + (size / 4)] == -1)
		{
			tree.root->right = NULL;
		}
		else
		{
			right = BuildTreeFromArray(arr + (size / 2) + 1, size / 2);
			tree.root->right = right.root;
		}
	}
	return tree;
}
