# include<stdio.h>
# include<string.h>
# include<stdlib.h>

void billHead(char name[], char date[], char time[]);
int billBody(char items[], int qty, int price);
void billFoot(int sum);

struct body{
    char items[100];
    int qty;
    int price;
};

int main() {
    system("cls");
    printf("\n\t\t\t   ***WRC RESTRO***");
    printf("\n----------------------------------------------------------------------\n\n");

    printf("1. Generate Invoice\n");
    printf("2. Show all Invoices\n");
    printf("3. Search for Invoice\n");
    printf("4. Exit\n\n");

    int choice; 

    printf("Enter your choice : ");
    scanf("%d", &choice);
    fgetc(stdin);

    switch(choice) {
        case 1: {
            system("cls");
            printf("\n");

            char name[100];
            char date[] = __DATE__;
            char time[] = __TIME__;
            int num;
            int sum=0;
            char yesNo='n';

            printf("Enter name of customer : ");
            fgets(name, 100, stdin);

            struct body goods[100];
            printf("Enter number of items : ");
            scanf("%d", &num);
            fgetc(stdin);

            for(int i=0; i<num; i++) {
                printf("For item %d \n", i+1);
                printf("Enter item name : ");
                fgets(goods[i].items, 100, stdin);
                goods[i].items[strlen(goods[i].items)-1]=0;

                if(goods[i].items[0] >= 'a' && goods[i].items[0] <= 'z') {
                    goods[i].items[0] = goods[i].items[0] - 32;
                }
                
                printf("Enter quantity : ");
                scanf("%d", &goods[i].qty);
                fgetc(stdin);
                printf("Enter price of unit item : ");
                scanf("%d", &goods[i].price);
                fgetc(stdin);
            }

            billHead(name, date, time);

            for (int i=0; i<num; i++) {
                sum += billBody(goods[i].items, goods[i].qty, goods[i].price);
            }

            billFoot(sum);

            printf("Do you want to save this bill[y/n] : ");
            scanf("%c", &yesNo);
            if(yesNo == 'y') {
                int sum=0;
                printf("\nBill Saved Sucessfully !!\n\n");
                freopen("Billing.txt", "a", stdout);

                billHead(name, date, time);

                for (int i=0; i<num; i++) {
                    sum += billBody(goods[i].items, goods[i].qty, goods[i].price);
                }

                billFoot(sum);
            }

            else {
                printf("\nBill Not Saved !!\n\n");
            }
            break;
        }

        case 2: {
            system("cls");
            printf("\n----------------------------------------------------------------------\n\n");
            printf("\t\t\t**==Your Invoices are==**\n");
            
            FILE *fptr;
            fptr = fopen("Billing.txt","r");

            char str[100000];
            while(fgets(str,100000,fptr) != NULL) {
                printf("%s", str);
            }

            fclose(fptr);
            break;
        }

        case 3: {
            system("cls");
            char customerName[100];
            printf("Enter name of customer : ");
            fgets(customerName,100,stdin);
            customerName[strlen(customerName)-1]=0;

            printf("\n----------------------------------------------------------------------\n\n");
            printf("\t\t\t**==Invoice for %s==**\n", customerName);

            char newstr[10000];
            int idx1=-1;
            int idx2=-1;

            FILE *fptr;
            fptr = fopen("Billing.txt", "r");

            char str[100000];
            while (fgets(str, 100000, fptr) != NULL) {
                strcat(newstr, str);
            }

            int str_len = strlen(newstr);
            int customerName_len = strlen(customerName);
            int i, j;

            for (i = 0; i <= str_len - customerName_len; i++) {
                int found = 1;
                for (j = 0; j < customerName_len; j++) {
                    if (newstr[i + j] != customerName[j]) {
                        found = 0;
                        break;
                    }
                }

                if (found) {
                    idx1 = i;
                    break;
                }
            }

            if (idx1 != -1) {
                char Special[] = "~";
                int Special_len = strlen(Special);
                int k, l;

                for (k = idx1 + customerName_len; k <= str_len - Special_len; k++) {
                    int found = 1;
                    for (l = 0; l < Special_len; l++) {
                        if (newstr[k + l] != Special[l]) {
                            found = 0;
                            break;
                        }
                    }

                    if (found) {
                        idx2 = k;
                        break;
                    }
                }
            }
            fclose(fptr);

            for(int i=idx1-154; i<idx2; i++) {
                printf("%c", newstr[i]);
            }

            printf("\n \n");
            break;
        }

        case 4: {
            system("cls");
            printf("\n----------------------------------------------------------------------\n\n");
            printf("\t\t\t\tThank You!!!\n");
            printf("\n----------------------------------------------------------------------\n\n");
            break;
        }

        default : {
            system("cls");
            printf("\n----------------------------------------------------------------------\n\n");
            printf("\t\tWrong input!!! Please correct the input.\n");
            printf("\n----------------------------------------------------------------------\n\n");
            break;
        }

    }

    return 0;
}

void billHead(char name[], char date[], char time[]) {
    printf("\n\t\t\t   ***WRC RESTRO***");
    printf("\n----------------------------------------------------------------------\n\n");
    printf("Date : %s", date);
    printf("\t\t\t\t      Time : %s\n", time);
    printf("Invoice To : %s", name);
    printf("\n----------------------------------------------------------------------\n");
    printf("Items\t\t\t\t");
    printf("Qty\t\t\t\t");
    printf("Total");
    printf("\n----------------------------------------------------------------------\n\n");
}

int billBody(char items[], int qty, int price) {
    int total=price*qty;
    printf("%s           \t\t", items);
    printf("%d\t\t\t\t", qty);
    printf("%.2f\n", total*1.0);
    return total;
}

void billFoot(int sum) {
    printf("\n----------------------------------------------------------------------\n");
    printf("Sub total\t\t\t\t\t\t\t");
    printf("%0.2f\n", sum*1.0);
    printf("Discount @10%c\t\t\t\t\t\t\t", '%');
    printf("%.2f\n", sum*0.1);
    printf("\t\t\t\t\t\t\t\t------\n");
    printf("Net total\t\t\t\t\t\t\t");
    printf("%0.2f\n",sum*1.0-sum*0.1);
    printf("Vat @13%c\t\t\t\t\t\t\t", '%');
    printf("%.2f\n", (sum*1.0-sum*0.1)*0.13);
    printf("\n----------------------------------------------------------------------\n");
    printf("Grand Total\t\t\t\t\t\t\t");
    printf("%0.2f", (sum*1.0-sum*0.1)+((sum*1.0-sum*0.1)*0.13));
    printf("\n----------------------------------------------------------------------~\n\n");
}
