#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fp, *temp;
    char prod_code[80], prod_desc[80];
    int avl_qty, found;
    char choice;
    char tcode[80], tdesc[80], trans[10];
    int q, tqty;
    char confirm;

    fp=fopen("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\productt.txt", "r");
        fprintf(fp, "prod000010,paper,100\n");
        fprintf(fp, "prod000100,ballpen,300\n");
        fprintf(fp, "prod000110,notebook,140\n");
        fprintf(fp, "prod000050,crayons,90\n");
        fprintf(fp, "prod000008,pencil,75\n");
    fclose(fp);

    do{
    	printf("\nPRODUCT MANAGEMENT\n");
        printf("\n[A]dd\n[E]dit\n[D]elete\n[V]iew\nE[X]it\n");
        printf("Please select one: ");
        scanf(" %c", &choice);

    switch(choice){

    case 'A':
    case 'a':
        fp=fopen("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\productt.txt", "a");
        if (!fp){
            printf("Error opening file\n");
            break;
        }
        printf("Enter Product Code: ");
        scanf("%s", prod_code);
        printf("Enter Product Description: ");
        scanf("%s", prod_desc);
        printf("Enter Initial Quantity: ");
        scanf("%d", &avl_qty);
        fprintf(fp, "%s,%s,%d\n", prod_code, prod_desc, avl_qty);
        fclose(fp);
        printf("Product Added!\n");
    break;

    case 'V':
    case 'v':
        fp=fopen("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\productt.txt", "r");
        if (!fp){
            printf("Error opening file!\n");
            break;
        }
        printf("%-16s %-23s %s\n", "Product Code", "Product Description", "Available Quantity");
        while(fscanf(fp, " %[^,],%[^,],%d", prod_code, prod_desc, &avl_qty) != EOF){
            printf("%-16s %-23s %d\n", prod_code, prod_desc, avl_qty);
        }
        fclose(fp);
    break;

    case 'E':
    case 'e':
        fp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\productt.txt", "r");
        temp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\temp.txt", "w");
        if(!fp||!temp){
            printf("Error opening file!\n");
            break;
        }
        printf("Enter product code to edit: ");
        scanf("%s", prod_code);
        found = 0;

        while(fscanf(fp, " %[^,],%[^,],%d", tcode, tdesc, &q) != EOF){
            if(strcmp(tcode, prod_code) == 0){
                found = 1;
                printf("Product Code: %s\nProduct Name: %s\nAvailable Quantity: %d\n", tcode, tdesc, q);
                printf("Transaction [Purchase/Sold]: ");
                scanf("%s", trans);
                printf("Quantity to Purchase/Sold: ");
                scanf("%d", &tqty);

                if (strcmp(trans, "Purchase") == 0 || strcmp(trans, "purchase") == 0){
                    q += tqty;
                }
                if (strcmp(trans, "Sold") == 0 || strcmp(trans, "sold") == 0){
                    q -= tqty;
                }
                printf("Updated Quantity: %d\n", q);
            }
            fprintf(temp, "%s,%s,%d\n", tcode, tdesc, q);
        }
        fclose(fp);
        fclose(temp);
        remove("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\productt.txt");
        rename("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\temp.txt", "C:\\Users\\Kaisha Inocencio\\Documents\\g7\\productt.txt");

        if(!found){
            printf("Record not found!\n");
        } else {
            printf("Product updated.\n");
        }
    break;

    case 'D':
    case 'd':
        fp=fopen("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\productt.txt","r");
        temp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\temp.txt", "w");
        if (!fp || !temp){
            printf("Error opening file\n");
            break;
        }

        printf("Enter Product code to delete: ");
        scanf("%s", prod_code);
        found = 0;

        while(fscanf(fp, " %[^,],%[^,],%d", tcode, tdesc, &q) != EOF){
            if(strcmp(tcode, prod_code) == 0){
                found = 1;
                printf("Product Name: %s\n", tdesc);
                printf("Available Quantity: %d\n", q);
                printf("Do you really want to delete [y/n]? ");
                scanf(" %c", &confirm);

                if(confirm == 'y' || confirm == 'Y'){
                    printf("Record deleted successfully\n");
                    continue;
                } else {
                    fprintf(temp, "%s,%s,%d\n", tcode, tdesc, q);
                    printf("Record not deleted.\n");
                }
            } else {
                fprintf(temp, "%s,%s,%d\n", tcode, tdesc, q);
            }
        }
        fclose(fp);
        fclose(temp);
        remove("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\productt.txt");
        rename("C:\\Users\\Kaisha Inocencio\\Documents\\g7\\temp.txt", "C:\\Users\\Kaisha Inocencio\\Documents\\g7\\productt.txt");

        if(!found){
            printf("Record not found\n"); 	
        }
        break;

    case 'X':
    case 'x':
        printf("Are you sure you want to exit? [y/n] ");
        scanf(" %c", &confirm);
        if(confirm == 'y' || confirm == 'Y'){
            printf("Thank you!\n");
            exit(0);
        } else {
            printf("Exit cancelled\n");
            continue;
        }
        break;

    }//switch

    }while(confirm != 'Y' && choice != 'y'); //do

return 0;
}