#include <stdio.h>
#include <conio.h>

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
void goToAt(int x, int y) { 
    printf("\x1b[%d;%dH", x, y); 
    // OR
    // printf("\x1b[%d;%df", x, y); 
}
/** SAVE RESTORE IS NOT WORKING */
void saveCursorPosition() { printf("\x1b[s"); }
void restoreSavedPosition() { printf("\x1b[u"); }

/** HYBRID */
void clearScreenAndGoHome() { clearScreen(); goHome(); }

void main() {

    clearScreenAndGoHome();
    puts("Bangladesh");
    puts("Bangladesh");
    // goUpBy(1);
    // goDownBy(2);
    puts("Bangladesh");
    // goUpBy(1);
    // goLeftBy(5);
    // goRightBy(4);
    printf("Dhaka");
    // clearBeforeCursor();
    // goLeftBy(3);
    // clearAfterCursor();

    getch();

}