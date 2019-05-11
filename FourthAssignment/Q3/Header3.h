#pragma once
#ifndef __TREE__
#define __TREE__
#define LEFT 0
#define RIGHT 1

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
/*INCLUDES*/

/*Structs*/
typedef struct __listNode
{
    int data;
    struct __listNode *next;
} ListNode;

typedef struct __list
{
    ListNode *head;
    ListNode *tail;
} List;

typedef struct __treeNode
{
    int data;
    struct __treeNode *parent;
    struct __treeNode *left;
    struct __treeNode *right;
} TreeNode;

typedef struct __tree
{
    TreeNode *root;
    List leafList; 
} Tree;
/*Structs*/

/*Declartions*/
Tree BuildTreeFromArrayWithLeafList(int *arr, int size);//Builds the tree and the list.
TreeNode *findParent(Tree tree,int parentData,int branchSelect);//Finds the parent from the user input.
Tree  AddLeaf(Tree tree,TreeNode *p,int branchSelect,int data);//Adds a leaf into the tree.
void freeTree(Tree *tree);//Deallocate the tree.
void printTreeInorder(Tree tree);//Prints the tree in order.
void printLeafList(Tree tree);//Prints the list.
void insertDataToBeginning(List *list, int num);//Inserts a Node into beggining of list.
void insertDataToEndList(List *list, int num); //Inserts a Node into list.
void insertLeavestoList(List *list, TreeNode *leaf);//Inserts the leaves into the list.
void freeList(List *list); //Deallocating list.
/*Declartions*/
#endif