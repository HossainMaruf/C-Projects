#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define STARTING_ROW 3
#define SHOP_NAME "Departmental Store"
#define MAIN_MENU_ITEM 7

/** GLOBAL VARIABLE */
const char* mainMenu[MAIN_MENU_ITEM] = {"Calculate Bill", "Add Goods", "Edit Goods", "Display All", "Search", "Delete Goods", "Exit"};

/** STRUCTURES */
typedef struct {
    int cols, rows, row_counter;
} Console;

typedef struct {

} Product;

/** SCREEN AND ERASING */
void clearBeforeCursor() { printf("\x1b[1J"); }; // cursor will not move
void clearAfterCursor() { printf("\x1b[0J"); }; // cursor will not move
void clearScreen() { printf("\x1b[2J"); } // clearBeforeCursor() + clearAfterCursor()

void clearBeforeCursorOfLine() { printf("\x1b[1K"); }; // cursor will not move
void clearAfterCursorOfLine() { printf("\x1b[0K"); }; // cursow will not move
void clearCursorLine() { printf("\x1b[2K"); } // clearBeforeCursorOfLine() + clearAferCursorOfLine()

/** CURSOR MOVEMENT */
void goUpBy(int n) { printf("\x1b[%dA", n); } // cursor will move
void goDownBy(int n) { printf("\x1b[%dB", n); } // cursor will move
void goRightBy(int n) { printf("\x1b[%dC", n); }// cursor will move
void goLeftBy(int n) { printf("\x1b[%dD", n); }// cursor will move
void goHome() { printf("\x1b[H"); } // cursor will move
void goToAt(int col, int row) { 
    printf("\x1b[%d;%dH", row, col); 
    // OR
    // printf("\x1b[%d;%df", x, y); 
}
/** TEXT ATTRIBUTES (SGR Parameters) */
void startBold() { printf("\x1b[1m"); }
void startDimOrFaint() { printf("\x1b[2m"); }
void startItalic() { printf("\x1b[3m"); }
void startUnderline() { printf("\x1b[4m"); }
void startBlink() { printf("\x1b[5m"); } // not working
void startReverseOrInverse() { printf("\x1b[7m"); } // Background White
void startHidden() { printf("\x1b[8m"); }
void startStrikethrough() { printf("\x1b[9m"); }
void stopTextAttr() { printf("\x1b[0m"); }

/** SAVE RESTORE IS NOT WORKING */
void saveCursorPosition() { printf("\x1b[s"); }
void restoreSavedPosition() { printf("\x1b[u"); }

/** HYBRID */
void clearScreenAndGoHome() { clearScreen(); goHome(); }

/** Utility Methods */
int centerX(Console *console) { return console->cols/2 - strlen(SHOP_NAME)/2; }

// show your shop name in the middle
void showShopName(Console *console) {
    goToAt(centerX(console), console->row_counter++);
    startBold();
    puts(SHOP_NAME);
    stopTextAttr();
}

// get your active console information
void GetConsoleInfo(Console *console) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    BOOL ok = GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE), &csbi
    );
    if (!ok) {
        fprintf(stderr, "Error getting console info\n");
        return;
    }
    console->cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    console->rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}


void calculate_bill(){}
void add_item(){}
void edit_goods(){}
void display_all(){}
void search_item(){}
void delete_item(){}

void showMainMenu(Console *console) {
    for(int i=0; i<MAIN_MENU_ITEM; i++) {
        goToAt(centerX(console), console->row_counter+i);
        printf("%d. %s", i+1, mainMenu[i]);
    }

    goLeftBy(strlen(mainMenu[MAIN_MENU_ITEM-1]) + 3); // 3 for space, dot and serial number
    goUpBy(MAIN_MENU_ITEM-1);
    char ch;
    int count = 1; // already cursor is on number 1 position
    while(1) {
        ch = getch();
        if(ch == 80) { // down arrow key
            if(count == MAIN_MENU_ITEM) { goUpBy(MAIN_MENU_ITEM-1); count=1; }
            else { goDownBy(1); count++; }
        } else if(ch == 72) { // up arrow key
            if(count == 1) { goDownBy(MAIN_MENU_ITEM-1); count=MAIN_MENU_ITEM; }
            else { goUpBy(1); count--; }
        } else if(ch == 13) { // enter key
            system("cls");
            printf("Pressed Enter and Value %d\n", count);
            break;
        }
    }
}

int main(void) {
    system("cls"); // clear the screen
    Console consoleInfo = {0, 0, STARTING_ROW}; // cols, rows, startingRowOfWriting
    GetConsoleInfo(&consoleInfo); // extract and populate console info
    showShopName(&consoleInfo);
    showMainMenu(&consoleInfo);
    
    return 0;
}