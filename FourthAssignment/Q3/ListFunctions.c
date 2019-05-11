#include "Header3.h"
/*Static Declartions*/
static void beginningInsertTool(List *list, ListNode *cell);
static ListNode *createListNode(int num, ListNode *next);
/*Static Declartions*/

 void insertDataToBeginning(List *list, int num)//Inserts data to beggining of list.
{
    ListNode *cell;
    cell = createListNode(num, list->head);
    beginningInsertTool(list, cell);//Utillity tool.
}
static void beginningInsertTool(List *list, ListNode *cell)
{
    if ((list->head == NULL) && (list->tail == NULL))
    {
        list->head = cell;
        list->tail = cell;
    }
    else
    {
        list->head = cell;
    }
}
static ListNode *createListNode(int num, ListNode *next)//Creates a listNode.
{
    ListNode *cell;
    cell = (ListNode *)malloc(sizeof(ListNode));
    if (cell == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(1);
    }
    cell->data = num;
    cell->next = next;
    return cell;
}
void printLeafList(Tree tree)//Prints the list.
{
    ListNode *curr;
    curr = tree.leafList.head;
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
}

void freeList(List *list) //Deallocating list.
{
    ListNode *curr;
    ListNode *next;
    curr = list->head;
    while (curr)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = list->tail = NULL;
}
 void insertLeavestoList(List *list, TreeNode *leaf)//Inserts the leaves from the tree into the list.
{
    if ((leaf->left == NULL) && (leaf->right == NULL))
    {
        insertDataToEndList(list, leaf->data);
    }
    else
    {
        if (leaf->left != NULL)
            insertLeavestoList(list, leaf->left);
        if (leaf->right != NULL)
            insertLeavestoList(list, leaf->right);
    }
}
void insertDataToEndList(List *list, int num) //inserts a Node into list.
{
    ListNode *cell;
    cell = (ListNode *)malloc(sizeof(ListNode));
    if (cell == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(1);
    }

    cell->data = num;
    cell->next = NULL;
    if ((list->head == NULL) && (list->tail == NULL)) //if list is empty.
        list->head = list->tail = cell;
    else
    {
        list->tail->next = cell;
        list->tail = cell;
    }
}

