#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>


#define NAME_LENGTH 10

typedef struct {
    char name[NAME_LENGTH];
    int code, quantity;
    float rate;
}rec;
rec item;

COORD coord = {0,0};
const char* head[] = {"*****_____FASHION WEAR_____*****", "Departmental Store"};
const char* operation[] = {"Edit Code","Edit Name","Edit Quantity","Edit Rate","Exit"};
const char* search[] = {"Using Code","Using Name","Using Quantity","Using Price","Exit"};
const char* menu[] = {"Calculate Bill", "Add Goods", "Edit Goods", "Display All", "Search", "Delete Goods", "Exit"};

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

// Major Functions

void mainMenu();
void header_show(int,int);
void window(int,int,int,int);
void title_setter(int,int,char*);
void cursor(int);
void highlight(int,int);

// Menu Driven Functions

void calculate_bill();
void add_item();
void edit_goods();
void display_all();
void display_one(int,int);
void display_some(rec,int,int);
void search_item();
void delete_item();
int exist_code(int);
float display_customerBill(int,int,int,int);


// Edit Operation Functions

void editCode(int);
void editName(int);
void editQuantity(int);
void editPrice(int);


// Searching Functions

void code_search();
void name_search();
void quantity_search();
void price_search();


char* main()
{
    mainMenu();

    return "Maruf Hossain (ICE,PUST)";
}

void mainMenu() {
    int i;
    system("cls");
    header_show(30,100);
    // window(30,100,19,40);
    // title_setter(30,100,"MAIN MENU");
    // for(i=0; i<7; i++) {
    //     gotoxy((30+80)/2-strlen("MAIN MENU"),21+i);
    //     printf("%s",menu[i]);
    // }
    cursor(7);
    getch();
}

void window(int a, int b, int c, int d) {
    int i;
    for(i=a; i<=b; i++) {
        gotoxy(i,15);
        printf("\xcd");
        gotoxy(i,17);
        printf("\xcd");
        gotoxy(i,c);
        printf("\xcd");
        gotoxy(i,d);
        printf("\xcd");
    }
    gotoxy(a-1,15);
    printf("\xc9"); // top left
    gotoxy(a-1,16);
    printf("\xba"); // vertical double bar
    gotoxy(a-1,17);
    printf("\xc8"); // bottom left
    gotoxy(b+1,15);
    printf("\xbb"); // right top
    gotoxy(b+1,16);
    printf("\xba"); // vertical double bar
    gotoxy(b+1,17);
    printf("\xbc"); // right bottom
    for(i=c+1; i<d; i++) {
        gotoxy(a-1,i);
        printf("\xba");
        gotoxy(b+1,i);
        printf("\xba");
    }
    gotoxy(a-1,c);
    printf("\xc9");
    gotoxy(a-1,d);
    printf("\xc8");
    gotoxy(b+1,c);
    printf("\xbb");
    gotoxy(b+1,d);
    printf("\xbc");
}

void header_show(int a, int b) {
    int i;
    gotoxy((a+b)/2 - strlen(head[0])/2,10);
    printf("%s",head[0]);
    gotoxy((a+b)/2 - strlen(head[1])/2,12);
    printf("%s",head[1]);
    for(i=a; i<=b; i++) {
      gotoxy(i,13);
      printf("_");
    }
}

void title_setter(int a, int b, char *title) {
    gotoxy((a+b)/2 - strlen(title)/2,16);
    printf("%s",title);
}

void cursor(int n) {
    int count = 1;
    char ch = '0';
    while(1) {
        switch(ch) {
        case 80:
            count++;
            if(count == n+1) count = 1;
            break;
        case 72:
            count--;
            if(count == 0) count = n;
            break;
        }
        highlight(n,count);
        ch = getch();
        if(ch == '\r') {
            if(n == 7) {
                if(count == 1) calculate_bill();
                else if(count == 2) add_item();
                else if(count == 3) edit_goods();
                else if(count == 4) display_all();
                else if(count == 5) search_item();
                else if(count == 6) delete_item();
                else exit(0);
            }
            if(n == 5) {
                if(count == 1) code_search();
                else if(count == 2) name_search();
                else if(count == 3) quantity_search();
                else if(count == 4) price_search();
                else mainMenu();
            }
        }
    }
}

void highlight(int n, int count) {
    int X_pos = (30+80)/2-strlen("MAIN MENU");
    if(n == 7) {
        gotoxy(X_pos,21+count-1);
        printf("%s",menu[count-1]);
    }
    if(n == 5) {
        X_pos = (20+80)/2 - strlen("Search Product")/2;
        gotoxy(X_pos,22+count-1);
        printf("%s",search[count-1]);
    }
}

// Menu Driven Functions Area

void calculate_bill() {
    int code, how_many, serial = 1, y_pos = 27;
    float total = 0;
    system("cls");
    header_show(20,100);
    window(20,100,19,50);
    title_setter(20,100,"CUSTOMER BILL");
    gotoxy(25,25);
    printf("SL. No.\tCode\tName\tUnit Price\tQuantity\tTotal");
    while(1) {
        gotoxy(25,21);
        printf("Enter Code ( 0 for ending ) :  ");
        scanf("%d",&code);
        if(code == 0) break;
        if(!exist_code(code)) continue;
        gotoxy(25,23);
        printf("How Many? :  ");
        scanf("%d",&how_many);
        total += display_customerBill(code,how_many,serial,y_pos);
        serial++; y_pos++;
    }
    gotoxy(25,y_pos+3);
    printf("Total amount = %f TK.",total);

    getch();
    mainMenu();
}

void add_item() {
    int new_code;
    FILE *file = fopen("record.txt","a");
    system("cls");
    header_show(20,80);
    gotoxy(25,15);
    printf("Enter new record (Y/N)? : ");
    while(toupper(getche()) == 'Y') {
        system("cls");
        header_show(30,100);
        window(30,100,19,45);
        title_setter(30,100,"ADD RECORD");

        gotoxy(35,22);
        printf("Enter new code :  ");
        scanf("%d",&new_code);

        if(exist_code(new_code)) {
            /// code exist
            gotoxy(35,25);
            printf("Code already exist!");

        } else {
            /// code not exist
            if(!file) {
                gotoxy(35,25);
                printf("Something went wrong!");
            } else {
                item.code = new_code;
                gotoxy(35,24);
                printf("Enter name :  ");
                scanf("%s",item.name);
                gotoxy(35,26);
                printf("Enter quantity :  ");
                scanf("%d",&item.quantity);
                gotoxy(35,28);
                printf("Enter rate :  ");
                scanf("%f",&item.rate);
                fprintf(file,"\n%d %s %d %f",item.code,item.name,item.quantity,item.rate);
            }
        }

        gotoxy(35,32);
        printf("Enter new record (Y/N)? : ");
    }
    fclose(file);
    mainMenu();
}

void edit_goods() {
    int i, code, choise;
    system("cls");
    header_show(20,100);
    window(20,100,19,50);
    title_setter(20,100,"EDIT PRODUCT");
    gotoxy(25,22);
    printf("Enter code :  ");
    scanf("%d",&code);
    if(exist_code(code)) {
        /// exist code
        display_one(code,25);
        for(i=0; i<5; i++) {
            gotoxy(25,30+i);
            printf("%d. %s",i+1,operation[i]);
        }
        gotoxy(25,37);
        printf("Enter choise :  ");
        scanf("%d",&choise);

        switch(choise) {
            case 1:
                /// Edit Code
                editCode(code);
                break;
            case 2:
                /// Edit Name
                editName(code);
                break;
            case 3:
                /// Edit Quantity
                editQuantity(code);
                break;
            case 4:
                /// Edit Price
                editPrice(code);
                break;
            default:
                /// Otherwise mainMenu() function
                mainMenu();
        }

    } else {
        /// not exist
        gotoxy(25,25);
        printf("Code not exist!");
    }
    getch();
    mainMenu();
}


void display_all() {
    int serial_no = 1, y_pos = 23;
    FILE *file = fopen("record.txt","r");
    system("cls");
    header_show(20,100);
    window(20,100,19,50);
    title_setter(20,100,"ALL RECORDS");
    if(!file) {
        gotoxy(30,25);
        printf("Something went wrong!");
    } else {
        gotoxy(26,21);
        printf("SL. No.\tProduct Code\tProduct Name\tQuantity\tRate");

        while(fscanf(file,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
            gotoxy(26,y_pos);
            printf("%d\t\t%d\t\t%s\t\t%d\t\t%f",serial_no,item.code,item.name,item.quantity,item.rate);

            if(serial_no % 20 == 0) {
                gotoxy(26,y_pos+5);
                printf("Press any key to see more...");
                getch();
                system("cls");
                header_show(20,100);
                window(20,100,19,50);
                title_setter(20,100,"ALL RECORDS");
                gotoxy(26,21);
                printf("SL. No.\tProduct Code\tProduct Name\tQuantity\tRate");
                y_pos = 23;
            }
            serial_no++; y_pos++;
        }
    }

    if(serial_no == 1) {
        gotoxy(26,25);
        printf("No Records Found! Please Add Item.");
    }

    fclose(file);
    getch();
    mainMenu();
}

void search_item() {
    int i, choise;
    system("cls");
    header_show(20,80);
    window(20,80,19,40);
    title_setter(20,80,"SEARCH PRODUCT");
    for(i=0; i<5; i++) {
        gotoxy((20+80)/2 - strlen("Search Product")/2,22+i);
        printf("%s",search[i]);
    }
    cursor(5);
}

void delete_item() {
    int code;
    FILE *fr = NULL, *fw = NULL;
    system("cls");
    header_show(20,100);
    window(20,100,19,40);
    title_setter(20,100,"DELETE RECORD");
    gotoxy(25,22);
    printf("Enter code :  ");
    scanf("%d",&code);
    if(exist_code(code)) {
        /// code exist

        display_one(code,25);

        gotoxy(25,30);
        printf("Are you sure to delete (Y/N)? :  ");

        if(toupper(getche()) == 'Y') {

            fr = fopen("record.txt","rb");
            fw = fopen("temp.txt","ab");
            if(!fr || !fw) {
                gotoxy(25,25);
                printf("Something went wrong!");
            } else {
                /// Both File Opened

                while(fscanf(fr,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
                    if(item.code == code) continue;
                    else fprintf(fw,"\n%d %s %d %f",item.code,item.name,item.quantity,item.rate);
                }
                fclose(fr);
                fclose(fw);
                remove("record.txt");
                rename("temp.txt","record.txt");
                gotoxy(25,32);
                printf("Delete Successfully!");
                gotoxy(25,34);
                printf("Delete more (Y/N)? :  ");
                if(toupper(getche()) == 'Y') delete_item();
            }
        }

    } else {
        gotoxy(25,25);
        printf("Item doesn't exist!");
    }

    mainMenu();
}

void display_one(int code, int y_pos) {
    FILE *file = fopen("record.txt","r");
    if(!file) {
        gotoxy(25,25);
        printf("Something went wrong!");
    } else {
        while(fscanf(file,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
            if(item.code == code) {
                gotoxy(33,y_pos);
                printf("Product Code\tProduct Name\tQuantity\tRate");
                gotoxy(35,y_pos+2);
                printf("%d\t\t  %s\t\t%d\t\t%f",item.code,item.name,item.quantity,item.rate);
                break;
            }
        }
    }
    fclose(file);
    return;
}

void display_some(rec item,int serial,int y_pos) {
    gotoxy(25,y_pos);
    printf("%d\t\t%d\t\t%s\t\t%d\t\t%f",serial,item.code,item.name,item.quantity,item.rate);
}

int exist_code(int new_code) {
    FILE *file = fopen("record.txt","r");
    if(!file) {
        gotoxy(35,24);
        printf("Something went wrong!");
    } else {
        while(fscanf(file,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
            if(item.code == new_code) {
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

/// Edit Operation Functions Area

void editCode(int code) {
    char extract_name[NAME_LENGTH];
    int new_code, extract_quantity;
    float extract_rate;

    FILE *fr = fopen("record.txt","rb");
    FILE *fw = fopen("temp.txt","ab");
    system("cls");
    header_show(20,100);
    window(20,100,19,40);
    title_setter(20,100,"EDIT CODE");

    if(!fr || !fw) {
        gotoxy(25,25);
        printf("Something went wrong!");
    } else {
        gotoxy(25,22);
        printf("Enter new code :  ");
        scanf("%d",&new_code);
        while(fscanf(fr,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
            if(item.code == code) {
                strcpy(extract_name,item.name);
                extract_quantity = item.quantity;
                extract_rate = item.rate;
                continue;
            }
            else fprintf(fw,"\n%d %s %d %f",item.code,item.name,item.quantity,item.rate);
        }
        fprintf(fw,"\n%d %s %d %f",new_code,extract_name,extract_quantity,extract_rate);
        fclose(fr);
        fclose(fw);
        remove("record.txt");
        rename("temp.txt","record.txt");
        gotoxy(25,25);
        printf("Code Edited!");
        gotoxy(25,28);
        printf("Edit More (Y/N)? :  ");
    }

    if(toupper(getche()) == 'Y') edit_goods();
    else mainMenu();
}

void editName(int code) {
    char new_name[NAME_LENGTH];
    int extract_code, extract_quantity;
    float extract_rate;

    FILE *fr = fopen("record.txt","rb");
    FILE *fw = fopen("temp.txt","ab");
    system("cls");
    header_show(20,100);
    window(20,100,19,40);
    title_setter(20,100,"EDIT NAME");

    if(!fr || !fw) {
        gotoxy(25,25);
        printf("Something went wrong!");
    } else {
        gotoxy(25,22);
        printf("Enter new name :  ");
        scanf("%s",new_name);
        while(fscanf(fr,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
            if(item.code == code) {
                extract_code = item.code;
                extract_quantity = item.quantity;
                extract_rate = item.rate;
                continue;
            }
            else fprintf(fw,"\n%d %s %d %f",item.code,item.name,item.quantity,item.rate);
        }
        fprintf(fw,"\n%d %s %d %f",extract_code,new_name,extract_quantity,extract_rate);
        fclose(fr);
        fclose(fw);
        remove("record.txt");
        rename("temp.txt","record.txt");
        gotoxy(25,25);
        printf("Name Edited!");
        gotoxy(25,28);
        printf("Edit More (Y/N)? :  ");
    }

    if(toupper(getche()) == 'Y') edit_goods();
    else mainMenu();
}

void editQuantity(int code) {
    char extract_name[NAME_LENGTH];
    int extract_code, new_quantity;
    float extract_rate;

    FILE *fr = fopen("record.txt","rb");
    FILE *fw = fopen("temp.txt","ab");
    system("cls");
    header_show(20,100);
    window(20,100,19,40);
    title_setter(20,100,"EDIT QUANTITY");

    if(!fr || !fw) {
        gotoxy(25,25);
        printf("Something went wrong!");
    } else {
        gotoxy(25,22);
        printf("Enter new quantity :  ");
        scanf("%d",&new_quantity);
        while(fscanf(fr,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
            if(item.code == code) {
                strcpy(extract_name,item.name);
                extract_code = item.code;
                extract_rate = item.rate;
                continue;
            }
            else fprintf(fw,"\n%d %s %d %f",item.code,item.name,item.quantity,item.rate);
        }
        fprintf(fw,"\n%d %s %d %f",extract_code,extract_name,new_quantity,extract_rate);
        fclose(fr);
        fclose(fw);
        remove("record.txt");
        rename("temp.txt","record.txt");
        gotoxy(25,25);
        printf("Quantity Edited!");
        gotoxy(25,28);
        printf("Edit More (Y/N)? :  ");
    }

    if(toupper(getche()) == 'Y') edit_goods();
    else mainMenu();
}

void editPrice(int code) {
    char extract_name[NAME_LENGTH];
    int extract_code, extract_quantity;
    float new_rate;

    FILE *fr = fopen("record.txt","rb");
    FILE *fw = fopen("temp.txt","ab");
    system("cls");
    header_show(20,100);
    window(20,100,19,40);
    title_setter(20,100,"EDIT RATE");

    if(!fr || !fw) {
        gotoxy(25,25);
        printf("Something went wrong!");
    } else {
        gotoxy(25,22);
        printf("Enter new rate :  ");
        scanf("%f",&new_rate);
        while(fscanf(fr,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
            if(item.code == code) {
                strcpy(extract_name,item.name);
                extract_code = item.code;
                extract_quantity = item.quantity;
                continue;
            }
            else fprintf(fw,"\n%d %s %d %f",item.code,item.name,item.quantity,item.rate);
        }
        fprintf(fw,"\n%d %s %d %f",extract_code,extract_name,extract_quantity,new_rate);
        fclose(fr);
        fclose(fw);
        remove("record.txt");
        rename("temp.txt","record.txt");
        gotoxy(25,25);
        printf("Rate Edited!");
        gotoxy(25,28);
        printf("Edit More (Y/N)? :  ");
    }

    if(toupper(getche()) == 'Y') edit_goods();
    else mainMenu();
}


float display_customerBill(int code, int quantity, int serial, int y_pos) {
    FILE *file = fopen("record.txt","r");
    float extract_rate;
    while(fscanf(file,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
        if(item.code == code) {
            gotoxy(25,y_pos);
            printf("  %d\t\t%d\t%s\t%f\t   %d\t\t%f",serial,item.code,item.name,item.rate,quantity,(item.rate * quantity));
            extract_rate = item.rate;
        }
    }
    fclose(file);
    return extract_rate * quantity;
}

/// Searching Functions Area

void code_search() {
    int code;
    system("cls");
    header_show(20,100);
    window(20,100,19,40);
    title_setter(20,100,"SEARCHING USING CODE");
    gotoxy(25,22);
    printf("Enter code :  ");
    scanf("%d",&code);
    if(exist_code(code)) {
        display_one(code,25);
    } else {
        gotoxy(25,27);
        printf("Code not exist! Try again.");
    }
    gotoxy(25,30);
    printf("Search More Using Code (Y/N)? :  ");
    if(toupper(getche()) == 'Y') code_search();
    else search_item();
}

void name_search() {
    int flag = 0, serial = 1, y_pos = 26;
    char name[NAME_LENGTH];
    FILE *file = fopen("record.txt","r");
    system("cls");
    header_show(20,100);
    window(20,100,19,40);
    title_setter(20,100,"SEARCHING USING NAME");
    gotoxy(25,22);
    printf("Enter name :  ");
    scanf("%s",name);
    gotoxy(25,24);
    printf("SL. No.\tProduct Code\tProduct Name\tQuantity\tRate");
    while(fscanf(file,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
        if(strcmp(item.name,name) == 0) {
            display_some(item,serial++,y_pos++);
            flag = 1;
        }
    }

    if(!flag) {
        gotoxy(25,y_pos+1);
        printf("Item not exist! Try again.");
    }
    fclose(file);
    gotoxy(25,y_pos+4);
    printf("Search More Using Name (Y/N)? :  ");
    if(toupper(getche()) == 'Y') name_search();
    else search_item();
}

void quantity_search() {
    int i,l_quan,h_quan, serial = 1, y_pos = 26, flag = 0;
    FILE *file = NULL;
    system("cls");
    header_show(20,100);
    window(20,100,19,40);
    title_setter(20,100,"SEARCHING USING QUANTITY");
    gotoxy(25,21);
    printf("Enter low quantity :  ");
    scanf("%d",&l_quan);
    gotoxy(25,22);
    printf("Enter high quantity :  ");
    scanf("%d",&h_quan);
    gotoxy(25,24);
    printf("SL. No.\tProduct Code\tProduct Name\tQuantity\tRate");
    for(i=l_quan; i<=h_quan; i++) {
        file = fopen("record.txt","r");
        while(fscanf(file,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
            if(i == item.quantity) {
                display_some(item,serial++,y_pos++);
                flag = 1;
            }
        }
        fclose(file);
    }
    if(!flag) {
        gotoxy(25,y_pos+1);
        printf("No items found!");
    }
    gotoxy(25,y_pos+4);
    printf("Search More (Y/N)? :  ");
    if(toupper(getche()) == 'Y') quantity_search();
    else search_item();
}

void price_search() {
    int serial = 1, y_pos = 26, flag = 0;
    float l_rate,h_rate;
    FILE *file = fopen("record.txt","r");
    system("cls");
    header_show(20,100);
    window(20,100,19,40);
    title_setter(20,100,"SEARCHING USING RATE");

    gotoxy(25,21);
    printf("Enter low rate :  ");
    scanf("%f",&l_rate);
    gotoxy(25,22);
    printf("Enter high rate :  ");
    scanf("%f",&h_rate);

    gotoxy(25,24);
    printf("SL. No.\tProduct Code\tProduct Name\tQuantity\tRate");

    while(fscanf(file,"%d%s%d%f",&item.code,item.name,&item.quantity,&item.rate) != EOF) {
        if(item.rate >= l_rate && item.rate <= h_rate) {
            display_some(item,serial++,y_pos++);
            flag = 1;
        }
    }
    fclose(file);
    if(!flag) {
        gotoxy(25,y_pos+1);
        printf("No items found!");
    }

    gotoxy(25,y_pos+4);
    printf("Search More (Y/N)? :  ");
    if(toupper(getche()) == 'Y') price_search();
    else search_item();
}
