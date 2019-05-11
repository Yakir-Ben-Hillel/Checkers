#pragma once
#ifndef __TREE__
#define __TREE__
#define FALSE 0
#define TRUE 1
#define SIZE 100

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*INCLUDES*/
typedef int BOOL;
/*STRUCTS*/
typedef struct __TreeNode
{
    char data;
    struct __TreeNode *left;
    struct __TreeNode *right;
} TreeNode;
/*STRUCTS*/
typedef struct __tree
{
    struct __TreeNode *root;
} Tree;
/*Declations*/
BOOL isVaildExpression(char *str);//Checks if Expression is Vaild.
BOOL isAnOperator(char c);//Checks if char is an operator.
BOOL isAnumber(char c);//Checks if char is a number.
BOOL buildExpressionTree(char *str,Tree *tree);
void freeTree(Tree *tree);//Deallocate the Tree.
double calcExpression(Tree tr);//Calculate the given equation.
/*Declations*/

#endif // !__TREE__
