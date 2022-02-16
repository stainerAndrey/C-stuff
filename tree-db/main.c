#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "treeAdt.h"

typedef struct Person{
    int id;
    char *name;
}Person, *pPerson;

pKey personGetKey(pElement pers){
    pPerson pTemp = (Person*)pers;
    return &(pTemp->id);
}

void personDelete(pElement pers){
	/* Delete function specific to Person data
	
	:param pers: pointer to Person data
	*/
    pPerson pTemp = (pPerson)pers;
    free(pTemp->name);
    free(pTemp);
}

int personKeyCmp(pKey key1, pKey key2){
	/* Compare function specific to Person data
	
	:param key1: Person data key
	:param key2: Person data key
	:return: key1 bigger -> 1; equal -> 0; key1 smaller -> -1 
	*/
    if(*(int*)key1 == *(int*)key2)
        return 0;
    else if(*(int*)key1 < *(int*)key2)
        return -1;
    else
        return 1;
}

void personPrint(pElement pers){
	/* Print function specific for Person data
	*/
    pPerson pTemp = (pPerson)pers;
    printf("\nName: %s ID: %d", pTemp->name, pTemp->id);
}

pPerson personCreate(char *name, int id){
	/* Create Person data structure
	
	:param name: Name string
	:param id: id
	:return: pointer to Person data
	*/
    pPerson pPers;
    if((pPers = (pPerson)malloc(sizeof(Person))) != NULL){
        pPers->id = id;
        if((pPers->name = (char*)malloc(sizeof(char) * (strlen(name) + 1))) != NULL){
            strcpy(pPers->name, name);
            return pPers;
        } else {
            printf("\nMemmory allocation for peraon's name failed.");
            free(pPers);
            return NULL;
        }
    } else {
        printf("\nMemmory allocation for new person failed.");
        return NULL;
    }
}

pKey floatGetKey(pElement number){
    return number;
}

void floatDelete(pElement number){
    free(number);
}

int floatKeyCmp(pKey key1, pKey key2){
    if(*(float*)key1 == *(float*)key2)
        return 0;
    else if(*(float*)key1 < *(float*)key2)
        return -1;
    else
        return 1;
}

void floatPrint(pElement number){
    printf("\nNumber: %g", *(float*)number);
}

float* floatCreate(float number){
    float *key;
    if (key = (float*)malloc(sizeof(float))) {
        *key = number;
        return key;
    }
    else {
        return NULL;
    }
}

int main(){
    pTreeNode personTree = NULL, floatTree = NULL;
    char name[256], ans;
    int k, height, id;
    float number;
    do {
        printf("\n\nPlease choose data type you want to operate.\nf - float numbers, p - person info, 0 - end the program\n");
        ans = _getch();
        switch (ans) {
            case 'f':
                do {
                    displayMenu();
                    ans = _getch();
                    switch (ans) {
                    case '1':
                        printf("\nPlease enter number: ");
                        if (scanf("%f", &number) == 1)
                            insertNode(floatTree, &floatTree, floatCreate(number), floatKeyCmp, floatGetKey, floatDelete);
                        else
                            printf("\nWrong input.");
                        break;
                    case '2':
                        if (floatTree != NULL) {
                            printf("\nFloat tree in postorder:");
                            printPostorder(floatTree, floatPrint);
                        }
                        else
                            printf("\nTree is still empty.");
                        break;
                    case '3':
                        if (floatTree != NULL) {
                            printf("\nPlease enter key of the node: ");
                            if (scanf("%f", &number) == 1) {
                                height = nodeHight(floatTree, floatCreate(number), floatKeyCmp, floatGetKey, floatDelete);
                                printf("\nHeight of a node with given key is: %d", height);
                            }
                            else
                                printf("\nWrong input.");
                        }
                        else
                            printf("\nTree is still empty.");
                        break;
                    case '4':
                        if (floatTree != NULL) {
                            printf("\nPlease enter number of nodes with smallest key you want to output: ");
                            if (scanf("%d", &k) == 1)
                                printSmallK(floatTree, floatPrint, &k);
                            else
                                printf("\nWrong input.");
                        }
                        else
                            printf("\nTree is still empty");
                        break;
                    case '9':
                    case '0':
                        if (floatTree == NULL)
                            printf("\nTree is still empty.");
                        else {
                            freeTree(&floatTree, floatDelete);
                            if (floatTree == NULL)
                                printf("\nTree was successfully erased");
                        }
                        break;
                    default:
                        printf("\nUnsupported command.");
                        break;
                    }
                } while (ans != '0' && ans != '9');
                break;
            case 'p':
                do {
                    displayMenu();
                    ans = _getch();
                    switch (ans) {
                    case '1':
                        printf("\nPlease enter person's id and name: ");
                        if (scanf("%d %s", &id, name) == 2)
                            insertNode(personTree, &personTree, personCreate(name, id), personKeyCmp, personGetKey, personDelete);
                        else
                            printf("\nWrong input.");
                        break;
                    case '2':
                        if (personTree != NULL) {
                            printf("\nPerson tree in postorder: ");
                            printPostorder(personTree, personPrint);
                        }
                        else
                            printf("\nTree is still empty");
                        break;
                    case '3':
                        if (personTree != NULL) {
                            printf("\nPlease enter key of the node(id): ");
                            if (scanf("%d", &id) == 1) {
                                height = nodeHight(personTree, personCreate(" ", id), personKeyCmp, personGetKey, personDelete);
                                printf("\nHeight of a node with given key is: %d", height);
                            } printf("\nWrong iput.");
                        }
                        else
                            printf("\nTree is still empty");
                        break;
                    case '4':
                        if (personTree != NULL) {
                            printf("\nPlease enter number of nodes with smallest key(id) you want to output: ");
                            if (scanf("%d", &k) == 1)
                                printSmallK(personTree, personPrint, &k);
                            else
                                printf("\nWrong input.");
                        }
                        else
                            printf("\nTree is still empty");
                        break;
                    case '9':
                    case '0':
                        if (personTree == NULL)
                            printf("\nTree is still empty.");
                        else {
                            freeTree(&personTree, personDelete);
                            if (personTree == NULL)
                                printf("\nTree was successfully erased.");
                        }
                        break;
                    default:
                        printf("\nUnsupported command.");
                        break;
                    }
                } while (ans != '0' && ans != '9');
                break;
            case '0':
                break;
            default:
                printf("\nUnsupported data type.");
                break;
        }
        
    } while (ans != '0');
    return 0;
}
