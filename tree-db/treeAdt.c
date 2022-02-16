#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "treeAdt.h"

typedef struct treeNode{
	/* Tree node
	
	:param pKey: void pointer to node data
	:param left: pointer to left node
	:param right: pointer to right node
	*/
    pKey data;
    pTreeNode left;
    pTreeNode right;
}treeNode;

Bool internalFind(pTreeNode root, pElement data, compKeys cmpFunc, getKey getFunc){
	/* Check if data exists in tree
	
	:param root: pointer to tree root
	:param data: data we a searching for inside the tree
	:param cmpFunc: function to compare specific data type
	:param getFunc: function to extract key from data
	*/
    while(root != NULL){
        if(cmpFunc(getFunc(root->data), getFunc(data)) == 0)
            return TRUE;
        if(cmpFunc(getFunc(root->data), getFunc(data)) == 1)
            root = root->left;
        else
            root = root->right;
    }
    return FALSE;
}

int treeHight(pTreeNode root){
	/* Calculate tree hight
	
	:param root: pointer to tree root
	:return: tree hight
	*/
    int right, left;
    if(root == NULL)
        return -1;
    else {
        left = 1 + treeHight(root->left);
        right = 1 + treeHight(root->right);
        return (left > right) ? left : right;
    }
    
}

Bool insertNode(pTreeNode root, pTreeNode *rootOrigin, pElement data, compKeys cmpFunc, getKey getFunc, delElement delFunc){
	/* Insert new data into the tree
	
	:param root: pointer to the tree root
	:param *rootOrigin: pointer to the root pointer in case tree is empty
	:param data: data to insert
	:param cmpFunc: type specific function to compare
	:param getFunc: type specific function to get data key
	:param delFunc: type specific function to delete element
	:return: True if insertion is successful, False otherwise 
	*/
    pTreeNode newNode;
    if(!internalFind(root, data, cmpFunc, getFunc)){
        if((newNode = (pTreeNode)malloc(sizeof(treeNode))) != NULL){
            newNode->data = data;
            newNode->left = NULL;
            newNode->right = NULL;
            if(!root){
                *rootOrigin = newNode;
                return TRUE;
            } else {
                while((cmpFunc(getFunc(root->data),getFunc(data)) == 1 && root->left != NULL) || (cmpFunc(getFunc(root->data), getFunc(data)) == -1 && root->right != NULL)){
                    if(cmpFunc(getFunc(root->data), getFunc(data)) == 1)
                        root = root->left;
                    else
                        root = root->right;
                }
                if(cmpFunc(getFunc(root->data), getFunc(data)) == 1)
                    root->left = newNode;
                else
                    root->right = newNode;
                return TRUE;
            }
        } else {
            printf("\nMemmory allocation for new node failed.");
            return FALSE;
        }
    } else {
        printf("\nNode with such key already in the tree.");
        return FALSE;
    }
}

void printPostorder(pTreeNode root, printElement printFunc){
	/* Output tree in postorder
	
	:param root: tree root
	:param printFunc: type specific function to print element
	*/
    if(!root)
        return;
    printPostorder(root->left, printFunc);
    printPostorder(root->right, printFunc);
    printFunc(root->data);
}

int nodeHight(pTreeNode root, pElement data, compKeys cmpFunc, getKey getFunc, delElement delFunc){
	/* Return node height with passed data
	
	:param root: pointer to tree root
	:param data: pointer to data
	:param compFunc: type specific function to compare data
	:param getFunc: type specific function to extract data key
	:param delFunc: type specific function do delete data
	:return: Height of a node with same data as passed, -1 if not found
	*/
    if(internalFind(root, data, cmpFunc, getFunc)){
        if(root){
            while(cmpFunc(getFunc(root->data),getFunc(data))){
                if(cmpFunc(getFunc(root->data),getFunc(data)) == 1)
                    root = root->left;
                else
                    root = root->right;
            }
            delFunc(data);
            return treeHight(root);
        } else
            delFunc(data);
            return -1;
    } else {
        printf("\nNode with such key not found.");
        delFunc(data);
        return -1;
    }
}

void printSmallK(pTreeNode root, printElement printFunc, int *k){
	/* Print k smallest values in tree
	
	:param root: pointer to tree root
	:param printFunc: type specific function to print element
	:param k: number of elements to print
	*/
    if(!root)
        return;
    printSmallK(root->left, printFunc, k);
    if(*k > 0){
        printFunc(root->data);
        (*k)--;
    }
    printSmallK(root->right, printFunc, k);
}

void freeTree(pTreeNode *root, delElement delFunc){
	/* Empty tree and deallocate memory
	
	:param root: pointer to root pointer
	:delFunc: type specific function to remove node
	*/
    if(*root == NULL)
        return;
    freeTree(&(*root)->left, delFunc);
    freeTree(&(*root)->right, delFunc);
    delFunc((*root)->data);
    free(*root);
    *root = NULL;
}

void displayMenu(void){
    printf("\n\n1:Insert new node.");
    printf("\n2:Output data tree in Postorder.");
    printf("\n3:Calculate height of a node with given key");
    printf("\n4:Output k nodes with smallest keys");
    printf("\n9:Erase current data tree and return to main menu.");
    printf("\n0:End the program");
    printf("\nEnjoy\n");
}
