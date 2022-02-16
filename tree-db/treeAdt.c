#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "treeAdt.h"

typedef struct treeNode{
    pKey data;
    pTreeNode left;
    pTreeNode right;
}treeNode;

Bool internalFind(pTreeNode root, pElement data, compKeys cmpFunc, getKey getFunc){
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
    int right, left;
    if(root == NULL)
        return -1;
    else {
        left = 1 + treeHight(root->left);
        right = 1 + treeHight(root->right);
        return (left > right) ? left : right;
    }
    
}

Bool insertNode(pTreeNode root, pTreeNode *rootOrigin, pElement data, compKeys cmpfunc, getKey getFunc, delElement delFunc){
    pTreeNode newNode;
    if(!internalFind(root, data, cmpfunc, getFunc)){
        if((newNode = (pTreeNode)malloc(sizeof(treeNode))) != NULL){
            newNode->data = data;
            newNode->left = NULL;
            newNode->right = NULL;
            if(!root){
                *rootOrigin = newNode;
                return TRUE;
            } else {
                while((cmpfunc(getFunc(root->data),getFunc(data)) == 1 && root->left != NULL) || (cmpfunc(getFunc(root->data), getFunc(data)) == -1 && root->right != NULL)){
                    if(cmpfunc(getFunc(root->data), getFunc(data)) == 1)
                        root = root->left;
                    else
                        root = root->right;
                }
                if(cmpfunc(getFunc(root->data), getFunc(data)) == 1)
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
    if(!root)
        return;
    printPostorder(root->left, printFunc);
    printPostorder(root->right, printFunc);
    printFunc(root->data);
}

int nodeHight(pTreeNode root, pElement data, compKeys cmpFunc, getKey getFunc, delElement delFunc){
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
