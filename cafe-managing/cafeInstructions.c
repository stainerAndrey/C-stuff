#include "cafeInstructions.h"

productNode* createProducts(void){
	/* Read file "Manot.txt" and create list of courses in stock
	
	:return: pointer to list HEAD
	*/
    FILE *menu;
    char name[MAX_LENGTH] = { 0 }, premium, line[MAX_LENGTH] = { 0 };
    int price, quantity, i = 0;
    productNode *head = NULL, *temp = NULL;
    
    if ((menu = fopen("Manot.txt", "r")) != NULL) {//if unable to open input file return NULL pointer
        while (!feof(menu)){
            fgets(line, MAX_LENGTH, menu);
            if (sscanf(line, "%s %d %d %c", name, &quantity, &price, &premium) == 4) {
                if (price > 0 && quantity > 0) {//if product price or quantity is negative display error message. proceed to next row of input file
                    if ((temp = (productNode*)malloc(sizeof(productNode))) != NULL) {
                        if ((temp->name = (char*)malloc(sizeof(char) * (strlen(name) + 1))) != NULL) {
                            strcpy(temp->name, name);
                            if (!existingProduct(head, temp->name)) {//search list for product with same name
                                i++;
                                temp->price = price;
                                temp->quantinty = quantity;
                                temp->premium = premium;
                                temp->next = head;
                                head = temp;
                                printf("\n%d portions of %s added to product list.", quantity, temp->name);
                            }
                            else printf("\nProduct already exists.");
                        }
                        else printf("\nFailed to allocate memmory for product name.");
                    }
                    else printf("\nFailed to allocate memmory for product node.");
                }
                else printf("\nPrice and quantity cannot have negative value.");
            }
            else printf("\nProblem with product data.");
        }
        printf("\nSuccessfully added %d products to menu list.", i);
        return head;
    } else {
        printf("\nUnable to open input file.");
        return head;
    }
}

int existingProduct(productNode *head, char *s){
	/* Check if product is in stock
	
	:param head: pointer to stock list HEAD
	:param s: name of the product we search
	
	:return: 1 if found
	*/
    int flag = 0;
    
    while (head != NULL) {
        if(!strcmp(s, head->name))//search for product with name *s in list *head
            flag = 1;
        head = head->next;
    }
    return flag;//if found return 1, otherwise 0
}

void addItems(productNode *head, char *s, int quantityToAdd){
	/* Add to quantity of product in stock if it exists
	
	:param head: pointer to stock list head
	:param s: product name
	:param quantityToAdd: quantity to add
	*/
    if(quantityToAdd > 0){//if quantity of product user wants to add is positive
        if(existingProduct(head, s)){//and product exists in list
            if((head = findProduct(head, s)) != NULL){
                head->quantinty += quantityToAdd;//increase it's quantity
                printf("\nKitchen prepared %d more portions of %s.", quantityToAdd, head->name);
            }
        }else printf("\nProduct doesn't exist.");//otherwise display error message
    } else printf("\nQuantity can't be negative.");
}

productNode* findProduct(productNode *head, char *s){
	/* Search for product in stock
	
	:param head: pointer to stock list head
	:param s: product name
	:return: pointer to product node
	*/
    while (head != NULL) {//search through list *head
        if (!strcmp(head->name, s))
            return head;//return pointer to product node with name *s
        head = head->next;
    }
    return head;//if not found return NULL
}

void orderItem(int tableNum, char *pName, int quant, productNode *menuHead, tableInfo tableArr[TABLE_COUNT]){
	/* Order items to the table and remove corresponding amount from the stock
	
	:param tableNum: table that made the order
	:param pName: name of the product
	:param quant: quantity of the product
	:param menuHead: list of products in stock
	:param tableArr: array of tables in cafe
	*/
    tableNode *orderHead = tableArr[tableNum - 1].head, *newNode = NULL;
    
    if(tableNum <= TABLE_COUNT){//talble number is relevant?
        if((menuHead = findProduct(menuHead, pName)) != NULL){//desired product exists in menu?
            if(quant > 0){//quantity desired to order is positive?
                if(menuHead->quantinty >= quant){//enough of product in the kitchen to order?
                    if((orderHead = findOrder(orderHead, pName)) == NULL){//product with name *s hasn't been ordered earlier?
                        if((newNode = (tableNode*)malloc(sizeof(tableNode))) != NULL){//memmory allocation for new order node was successfull?
                            if((newNode->name = (char*)malloc(sizeof(char) * (strlen(pName) + 1))) != NULL){//memmory allocation for name of the product ordered was successfull?
                                //fill new node with relevant data, change table bill and premium status if needed
                                strcpy(newNode->name, pName);
                                newNode->quantity = quant;
                                tableArr[tableNum - 1].bill += quant * menuHead->price;
                                //update product quantity in the kitchen
                                menuHead->quantinty -= quant;
                                if(menuHead->premium == 'Y')
                                    tableArr[tableNum - 1].premium = 'Y';
                                if(tableArr[tableNum - 1].head != NULL)
                                    tableArr[tableNum - 1].head->prev = newNode;
                                newNode->next = tableArr[tableNum - 1].head;
                                newNode->prev = NULL;
                                if(tableArr[tableNum - 1].head == NULL)
                                    tableArr[tableNum - 1].tail = newNode;
                                tableArr[tableNum - 1].head = newNode;
                                printf("\nTable %d ordered %d portions of %s", tableNum, quant, pName);
                            } else printf("\nFailed to allocate memmory for order name.");
                        } else printf("\nFailed to allocate memmory for table node.");
                    } else {
                        //update quantity of ordered product and updatate table bill
                        orderHead->quantity += quant;
                        menuHead->quantinty -= quant;
                        tableArr[tableNum - 1].bill += quant * menuHead->price;
                        printf("\nTable %d ordered %d portions of %s", tableNum, quant, pName);
                    }
                } else printf("\n%d portions of %s left in the kitchen. Not enough to carry out the order.", menuHead->quantinty, pName);
            } else printf("\nImpossible to order negative number of product.");
        } else printf("\nProduct %s is missing in the menu", pName);
    } else printf("\nTable doesn't existed.");
}

tableNode* findOrder(tableNode *head, char *s){
	/* Find order of specific table
	
	:param head: pointer to list of table orders
	:param s: product name to search
	:return: pointer to order node, NULL if order not found
	*/
    while (head != NULL) {//search throush list of orders
        if (!strcmp(head->name, s))
            return head;//return pointer to order node with name *s
        head = head->next;
    }
    return head;//otherwise return NULL
}

void removeItem(int tableNum, char *pName, int quant, productNode *menuHead, tableInfo tableArr[TABLE_COUNT]){
	/* Table returns product
	
	:param tableNum: table number
	:param pName: product to return
	:param quant: quantity to return
	:param menuhead: pointer to stock list
	:param tableArr: array of tables in cafe
	*/
    tableNode *orderHead = tableArr[tableNum - 1].head;
    
    if(tableNum <= TABLE_COUNT){//table number is relevant?
        if(orderHead != NULL){//table ordered anything earlier?
            if(quant > 0){//quantity table want to return is positive?
                if((orderHead = findOrder(orderHead, pName)) != NULL){//table ordered product with name *s?
                    if(orderHead->quantity >= quant){//table isn't trying to return more than ordered?
                        //update product quantity and table bill
                        orderHead->quantity -= quant;
                        menuHead = findProduct(menuHead, pName);
//                         menuHead->quantinty -= quant;
                        tableArr[tableNum - 1].bill -= quant * menuHead->price;
                        printf("\nTable %d returned %d portions of %s", tableNum, quant, pName);
                    }else printf("\nQuantity of %s in order is lower than you want to remove.", pName);
                } else printf("\n%s is not in the order.", pName);
            } else printf("\nCan't remove negative number of portions.");
        } else printf("\nTable is empty.");
    } else printf("\nTable doesn't existed.");
}

void removeTable(int tableNum, tableInfo tableArr[TABLE_COUNT]){
	/* Close the table, calculate total bill to charge
	
	:param tableNum: table number
	:param tableArr: array of tables
	*/
    tableNode *orderHead = tableArr[tableNum - 1].head, *temp;
    float finalSum;
    if(tableNum <= TABLE_COUNT){//table number is relevant?
        if(orderHead != NULL){//table ordered something?
            printf("\nTable %d order:", tableNum);
            while (orderHead != NULL) {
                //output order data and free allocated memmory till list is empty
                temp = orderHead;
                printf("\n%s: %d", orderHead->name, orderHead->quantity);
                orderHead = orderHead->next;
                free(temp->name);
                free(temp);
            }
            //calculate final bill based on it's premium status
            finalSum = (tableArr[tableNum - 1].premium == 'Y') ? (float)(tableArr[tableNum - 1].bill) * 1.1 : (float)(tableArr[tableNum - 1].bill);
            printf("\nFinal bill: %g USD tax included.", finalSum);
            //set table to 'empty' state
            tableArr[tableNum - 1].head = NULL;
            tableArr[tableNum - 1].tail = NULL;
            tableArr[tableNum - 1].bill = 0;
            tableArr[tableNum - 1].premium = 'N';
        } else printf("\nThis table is empty");
    } else printf("\nTable doesn't existed.");
}

void openCafe(int tableCount, tableInfo tableArr[TABLE_COUNT]){
	/* Reset all table info to default
	
	:param tableCount: number of tables in cafe
	:param tableArr: array of tables
	*/
    int i;
    for (i = 0; i < tableCount; i++) {
        //set all tables in cafe to 'empty' state
        tableArr[i].head = NULL;
        tableArr[i].tail = NULL;
        tableArr[i].bill = 0;
        tableArr[i].premium = 'N';
    }
}

void closeKitchen(productNode *menuHead){
	/* Remove all items from stock, deallocate memory
	
	:param menuHead: pointer to stock list
	*/
    productNode *temp;
    while (menuHead != NULL) {
        //free kitchen menu
        temp = menuHead;
        menuHead = menuHead->next;
        free(temp->name);
        free(temp);
    }
}

void closeCafe(int tableCount, tableInfo tableArr[TABLE_COUNT]){
	/* Remove records from all tables, deallocate memory
	
	:param tableCount: number of tables in cafe
	:param tableArr: array of tables
	*/
    int i;
    for (i = 0; i < tableCount; i++) {
        closeTable(tableArr[i].head);
    }
}

void closeTable(tableNode *head){
    tableNode *temp;
    while (head != NULL) {
        //free list of orders
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
}

void showUserMenu(void){
    printf("\n\n1: Get kitchen status. 2: Update kitchen status");
    printf("\n3: Add oredr. 4: Return order. 5: Close table.");
}
