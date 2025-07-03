#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h> // for usleep()

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void main() {
    float A=0, B=0;
    float z[1760];
    char b[1760];
    printf("\x1b[2J"); // clean screen
    for(;;) {
        memset(b, ' ', 1760);
        memset(z, 0, sizeof z);
        for(float j=0; j<2*M_PI; j+=0.07) {
            for(float i=0; i<2*M_PI; i+=0.02) {
                float c = sin(i), d = cos(j), e = sin(A);
                float f = sin(j), g = cos(A);
                float h = d+2;
                float D = 1/(c*h*e + f*g + 5);
                float l = cos(i), m=cos(B), n=sin(B);
                float t = c*h*g - f*e;
                int x = 40 + 30*D*(l*h*m - t*n);
                int y = 12 + 15*D*(l*h*n + t*m);
                int o = x + 80*y;
                int N = 8*((f*e - c*d*g)*m - c*d*e - f*g - l*d*n);
                if(y>=0 && y<22 && x>=0 && x<80 && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N>0 ? N : 0];
                }
            
            }
        }
        printf("\x1b[H");
        for(int k=0; k<1761; k++) 
            putchar(k%80 ? b[k] : '\n');
        A += 0.04;
        B += 0.02;
        usleep(35000);
    }
}