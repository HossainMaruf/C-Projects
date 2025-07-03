#include <stdio.h>

#define MONTHS 12
#define DAYS 7

// Tomohiko Sakamoto’s Algorithm
int getFirstDayOfYear(int y, int m, int d) {
    static int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    if (m < 3) y -= 1;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
    /**
     * 0 = Sunday
     * 1 = Monday
     * 2 = Tuesday
     * 3 = Wednesday
     * 4 = Thursday
     * 5 = Friday
     * 6 = Saturday
     */
}

int isLeapYear(int y) {
    return (y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}

void main() {
    const char *months[MONTHS] = {"January", "February", "March", "April", "May", "June",
        "July", "Augutst", "September", "October", "November", "December"};
    const char *days[DAYS] = {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};
    int daysInMonth[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int year;
    printf("Enter year: ");
    scanf("%d", &year);
    daysInMonth[1] = isLeapYear(year) ? 29 : 28;

    int skip = getFirstDayOfYear(year, 1, 1) + 1, print_counter = 0;
    for(int i=0; i<MONTHS; i++) {
        puts(months[i]);
        for(int j=0; j<DAYS; j++) {
            if(j == DAYS-1) {
                printf("%s\n", days[j]);
            } else printf("%s\t", days[j]);
        }

        // go to start day
        for(int j=1; j<=skip; j++) printf("\t");
        // complete first line
        for(int j=1; j<=(DAYS-skip); j++) printf("%d\t", j);
        printf("\n");

        // printing remaining date
        for(int j=(DAYS-skip+1); j<=daysInMonth[i]; j++) {
            if(j == daysInMonth[i] && print_counter == DAYS-1) {
                // month ends with no more days remaining
                printf("%d", j);
                skip = 0;
                print_counter = 0;
            } else if(j == daysInMonth[i] && print_counter < DAYS-1) {
                // months ends with some days remaining
                printf("%d", j);
                print_counter++;
                // printf("counter = %d\n", print_counter);
                skip = print_counter;
                print_counter = 0;
            }
            else if(j < daysInMonth[i] && print_counter < DAYS-1) {
                printf("%d\t", j);
                print_counter++;
            } else if(j < daysInMonth[i] && print_counter == DAYS-1) {
                printf("%d\n", j);
                print_counter = 0;
            } 
        }
        printf("\n\n");
    }
}