#include "Header2.h"
/*Static Declartions*/
static Tree buildAux(char *str, int size);
static void freeTreeAux(TreeNode *leaf);
double calcAux(TreeNode *leaf);
/*Static Declartions*/

BOOL buildExpressionTree(char *str, Tree *tree)
{
    if (!isVaildExpression(str))//Does not build a tree if expression is not vaild.
        return FALSE;
    else
    {
        *tree = buildAux(str, strlen(str));
        return TRUE;
    }
}
static Tree buildAux(char *str, int size)
{
    Tree tree;
    Tree left;
    Tree right;
    BOOL flag = FALSE;
    int barrackOpen_counter = 0;
    int i = 0;
    tree.root = (TreeNode *)malloc(sizeof(TreeNode));
    if (tree.root == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(-1);
    }
    if ((size == 1) || ((size = 2) && (str[i + 1] == ')')))
    {//checks only 1 value left or 2 values and the last is ')'.
        tree.root->data = str[0];
        tree.root->left = tree.root->right = NULL;
    }
    else
    {
        while ((flag == FALSE) && (str[i] != '\0'))
        {
            if (str[i] == '(')
                barrackOpen_counter++;
            if (str[i] == ')')
                barrackOpen_counter--;
            if (barrackOpen_counter == 1)
            {//enters only the needed operator.
                if (isAnOperator(str[i]))
                {
                    flag = TRUE;
                    tree.root->data = str[i];
                    i--;
                }
            }
            i++;
        }
        left = buildAux(str + 1, i - 1);
        tree.root->left = left.root;
        right = buildAux(str + i + 1, i - 1);
        tree.root->right = right.root;
    }
    return tree;
}
double calcExpression(Tree tree)
{
    return calcAux(tree.root);
}
double calcAux(TreeNode *leaf)
{
    switch (leaf->data)
    {//case for each option.
    case '+':
        return (calcAux(leaf->left) + (calcAux(leaf->right)));
        break;
    case '-':
        return (calcAux(leaf->left) - (calcAux(leaf->right)));
        break;
    case '*':
        return (calcAux(leaf->left) * (calcAux(leaf->right)));
        break;
    case '/':
        return (calcAux(leaf->left) / (calcAux(leaf->right)));
        break;
    case '%':
        return ((int)(calcAux(leaf->left)) % ((int)(calcAux(leaf->right))));
        break;

    default:
    {
        return (leaf->data) - '0';
        break;
    }
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
