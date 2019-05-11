#include "Header3.h"
#define SIZE 100

int main()

{
    int size, i;
    int arr[SIZE];
    Tree tr;
    TreeNode * p;
    int parentData, data, branchSelect;
    printf("Please enter the number of items: ");
    scanf("%d", &size);
    for(i=0; i<size; i++)
        scanf("%d", &arr[i]);
    scanf("%d%d%d", &parentData, &data, &branchSelect);
    tr = BuildTreeFromArrayWithLeafList(arr, size);//the array is given as described in question 1
    //scan the tree inorder (LDR) and find the first parent (a node with parentData as data) that has no child in branchSelect

    p = findParent(tr, parentData, branchSelect);
    tr = AddLeaf(tr, p, branchSelect, data);
    printTreeInorder(tr); //Print the tree in-order (LDR)
    printf("\n");
    printLeafList(tr); //Print the leaves from left to right
    freeTree(&tr);
}

