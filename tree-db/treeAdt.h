#ifndef treeAdt_h
#define treeAdt_h

#include <stdio.h>

typedef struct treeNode* pTreeNode;
typedef void* pKey;//float or Person->id
typedef void* pElement;//struct Person or float
typedef enum{FALSE,TRUE} Bool;

typedef pKey (*getKey)(pElement);
typedef void (*delElement)(pElement);
typedef int (*compKeys)(pKey,pKey);//return 0 if equal, -1 if less, 1 if greater
typedef void (*printElement)(pElement);

Bool insertNode(pTreeNode root, pTreeNode *rootOrigin, pElement node, compKeys cmpfunc, getKey getFunc, delElement delFunc);
void printPostorder(pTreeNode root, printElement printFunc);
int nodeHight(pTreeNode root, pElement data, compKeys cmpFunc, getKey getFunc, delElement delFunc);
void printSmallK(pTreeNode root, printElement printFunc, int *k);
void freeTree(pTreeNode *root, delElement delFunc);
void displayMenu(void);
#endif /* treeAdt_h */
