#include "Header3.h"
/*Static Declartions*/
static void PrintInOrderAux(TreeNode *leaf);                                           //Utillity for printing the tree.
static TreeNode *BuildTreeFromArray(TreeNode *parent, int *arr, int size);             //Build a tree from the array(Q1).
static void AddLeafToTreeAux(TreeNode *leaf, TreeNode *p, int branchSelect, int data); //Utillity for adding leaf to tree.
static TreeNode *findParentAux(TreeNode *leaf, int parentData, int branchSelect);      //Utillity for finding parent.
static TreeNode *findFirstLeaf(TreeNode *root);                                        //Returns the first leaf in tree from left to right.
static void freeTreeAux(TreeNode *leaf);                                               //Utillity for deallocating the tree.
/*Static Declartions*/

Tree BuildTreeFromArrayWithLeafList(int *arr, int size)
{
    Tree tree;
    tree.root = BuildTreeFromArray(NULL, arr, size);
    tree.leafList.head = tree.leafList.tail = NULL;
    insertLeavestoList(&(tree.leafList), tree.root);
    return tree;
}
static TreeNode *BuildTreeFromArray(TreeNode *parent, int *arr, int size) //From question 1.
{
    TreeNode *tree;
    TreeNode *left;
    TreeNode *right;
    tree = (TreeNode *)malloc(sizeof(TreeNode));
    if (tree == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(-1);
    }

    if (size == 1)
    {
        tree->data = arr[0];
        tree->parent = parent;
        tree->left = tree->right = NULL;
    }
    else
    {
        tree->data = arr[size / 2];
        tree->parent = parent;
        if (arr[size / 4] == -1)
        {
            tree->left = NULL;
        }
        else
        {
            left = BuildTreeFromArray(tree, arr, size / 2);
            tree->left = left;
        }
        if (arr[(size / 2) + 1 + (size / 4)] == -1)
        {
            tree->right = NULL;
        }
        else
        {
            right = BuildTreeFromArray(tree, arr + (size / 2) + 1, size / 2);
            tree->right = right;
        }
    }
    return tree;
}
TreeNode *findParent(Tree tree, int parentData, int branchSelect)
{
    return findParentAux(tree.root, parentData, branchSelect);
}
TreeNode *findParentAux(TreeNode *root, int parentData, int branchSelect)
{
    TreeNode *res;
    if (root == NULL)
    { // checks if tree is empty.
        res = NULL;
    }
    else if ((root->data == parentData) && ((root->left == NULL && branchSelect == LEFT) || (root->right == NULL && branchSelect == RIGHT)))
    {
        res = root;
    }
    else
    {
        res = findParentAux(root->left, parentData, branchSelect);
        if (res == NULL)
        {
            res = findParentAux(root->right, parentData, branchSelect);
        }
    }
    return res;
}
Tree AddLeaf(Tree tree, TreeNode *p, int branchSelect, int data)
{ //Insert leaf to tree.
    if (p != NULL)
    { //If p is not empty.
        ListNode *curr;
        int flag = 0;
        if (tree.root == p)
        {

            TreeNode *newNode;
            newNode = (TreeNode *)malloc(sizeof(TreeNode));
            if (newNode == NULL)
            {
                fprintf(stderr, "Memory allocation error!\n");
                exit(-1);
            }
            newNode->parent = p;
            newNode->data = data;
            newNode->left = newNode->right = NULL;

            if (branchSelect == LEFT)
            {
                p->left = newNode;
            }
            else //Right
            {
                p->right = newNode;
            }
        }
        else
        {
            AddLeafToTreeAux(tree.root, p, branchSelect, data);
        }
        //Insert leaf to list.
        curr = tree.leafList.head;
        while ((curr != NULL) && (flag == 0))
        {
            if (curr->data == p->data)
            {
                curr->data = data;
                flag = 1;
            }
            else
            {
                curr = curr->next;
            }
        }
        if (flag == 0)
        { //If data is not found in the list.
            TreeNode *res;
            res = findFirstLeaf(tree.root); //Check where to insert.
            if (res->data != tree.leafList.head->data)
            {
                insertDataToBeginning(&(tree.leafList), data);
            }
            else
            {
                insertDataToEndList(&(tree.leafList), data);
            }
        }
    }
    return tree;
}
static TreeNode *findFirstLeaf(TreeNode *root) //Returns first found leaf from left to right.
{
    TreeNode *res;
    if ((root->left == NULL) && (root->right == NULL))
        res = root;
    else
    {
        res = findFirstLeaf(root->left);
        if (res == NULL)
        {
            res = findFirstLeaf(root->right);
        }
    }
    return res;
}
static void AddLeafToTreeAux(TreeNode *leaf, TreeNode *p, int branchSelect, int data)
{
    if ((leaf->left == NULL) || (leaf->right == NULL))
    { //Checks if it's a leaf.
        if (leaf == p)
        {
            TreeNode *newNode;
            newNode = (TreeNode *)malloc(sizeof(TreeNode));
            if (newNode == NULL)
            {
                fprintf(stderr, "Memory allocation error!\n");
                exit(-1);
            }
            newNode->parent = p;
            newNode->data = data;
            newNode->left = newNode->right = NULL;

            if (branchSelect == LEFT)
            {
                p->left = newNode;
            }
            else //Right
            {
                p->right = newNode;
            }
        }
        else
        {
            if (leaf->left != NULL)
                AddLeafToTreeAux(leaf->left, p, branchSelect, data);
            if (leaf->right != NULL)
                AddLeafToTreeAux(leaf->right, p, branchSelect, data);
        }
    }
    else
    {
        if (leaf->left != NULL)
            AddLeafToTreeAux(leaf->left, p, branchSelect, data);
        if (leaf->right != NULL)
            AddLeafToTreeAux(leaf->right, p, branchSelect, data);
    }
}

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
    freeList(&tree->leafList);
}
static void freeTreeAux(TreeNode *leaf)
{
    if (leaf->right)
        freeTreeAux(leaf->right);
    if (leaf->left)
        freeTreeAux(leaf->left);
    free(leaf);
}
