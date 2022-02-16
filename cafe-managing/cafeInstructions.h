#ifndef cafeInstructions_h
#define cafeInstructions_h
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define TABLE_COUNT 15
#define MAX_LENGTH 256

typedef struct productNode{
    char *name;
    int price, quantinty;
    char premium;
    struct productNode *next;
}productNode;

typedef struct tableNode{
    int quantity;
    char *name;
    struct tableNode *next, *prev;
}tableNode;

typedef struct tableInfo{
    int bill;
    char premium;
    struct tableNode *head, *tail;
}tableInfo;

productNode* createProducts(void);
//return pointer to head of list of products

int existingProduct(productNode *head, char *s);
//*head - pointer to head of list of products
//*s - name of product to check
//return 1 if found product with such name in list. 0 otherwise

void addItems(productNode *head, char *s, int quantityToAdd);
//*head - pointer to head of list of products
//*s - name of product to add quantity
//quantityToAdd - number to increase quantity of product *s by

productNode* findProduct(productNode *head, char *s);
//*head - pointer to head of list of products
//*s - name of product to find
//return pointer to product node with *s name. NULL otherwise

void orderItem(int tableNum, char *pName, int quant, productNode *menuHead, tableInfo tableArr[TABLE_COUNT]);
//function to add number of portions to order
//tableNum - table number, duh
//pName - name of product to add to the table
//quant - quantity of product to add
//*menuHead - pointer to head of product list
//tableArr - array of struct tableInfo. Contains pointer to head of order list and final bill

tableNode* findOrder(tableNode *head, char *s);
//*head - pointer to head of list of orders
//*s - name of product to find
//return pointer to order node with *s name. NULL otherwise

void removeItem(int tableNum, char *pName, int quant, productNode *menuHead, tableInfo tableArr[TABLE_COUNT]);
//function to remove number of portions from order
//tableNum - table number, duh
//pName - name of product to remove to the table
//quant - quantity of product to remove
//tableArr - array of struct tableInfo. Contains pointer to head of order list and final bill

void removeTable(int tableNum, tableInfo tableArr[TABLE_COUNT]);
//function to show ordered items of table tableNum, final bill and free allocated memmory
//tableNum - table number
//tableArr - array of struct tableInfo. Contains pointer to head of order list and final bill

void openCafe(int tableCount, tableInfo tableArr[TABLE_COUNT]);
//function to initialize array of tables
//tableCount - number of tables in cafe

void closeKitchen(productNode *menuHead);
//function to free list of products

void closeCafe(int tableCount, tableInfo tableArr[TABLE_COUNT]);
//function to free all lists in array of structs

void closeTable(tableNode *head);
//function to free list of orders on the table

void showUserMenu(void);
//function to show UI

#endif /* cafeInstructions_h */
