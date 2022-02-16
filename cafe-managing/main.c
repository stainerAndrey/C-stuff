#include "cafeInstructions.h"

int main() {
    FILE *in;
    char productName[MAX_LENGTH];
    int tableNum, quantity;
    tableInfo tableArr[TABLE_COUNT];
    productNode *kitchenListHead = NULL;
    char command, line[MAX_LENGTH];
    if((in = fopen("Instructions.txt", "r")) != NULL){
        openCafe(TABLE_COUNT, tableArr);
        do {
            showUserMenu();
            printf("\nPlease enter 0 to proceed to next command:  ");
            command = _getche();
            putchar('\n');
            if(command == '0'){
                if((command = fgetc(in)) != EOF){
                    fgets(line, MAX_LENGTH, in);
                    switch (command) {
                        case '1':
                            closeKitchen(kitchenListHead);//free previous menu list if it existed
                            kitchenListHead = createProducts();//create new menu list
                            break;
                        case '2':
                            if(sscanf(line, "%s %d", productName, &quantity) == 2)
                                addItems(kitchenListHead, productName, quantity);
                            else printf("\nInstructions are not right.");
                            break;
                        case '3':
                            if(sscanf(line, "%d %s %d", &tableNum, productName, &quantity) == 3)
                                orderItem(tableNum, productName, quantity, kitchenListHead, tableArr);
                            else printf("\nInstructions are not right.");
                            break;
                        case '4':
                            if(sscanf(line, "%d %s %d", &tableNum, productName, &quantity) == 3)
                                removeItem(tableNum, productName, quantity, kitchenListHead, tableArr);
                            else printf("\nInstructions are not right.");
                            break;
                        case '5':
                            if(sscanf(line, "%d", &tableNum) == 1)
                                removeTable(tableNum, tableArr);
                            else printf("\nInstructions are not right.");
                            break;
                        default:
                            printf("\nInstructions are not right.");
                            break;
                    }
                }
            } else printf("\nPlease enter '0' to procceed to next instruction.");
        } while (!feof(in));
        closeCafe(TABLE_COUNT, tableArr);
        closeKitchen(kitchenListHead);
    } else printf("/Failed to open instructions file.");
    return 0;
}
