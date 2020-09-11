#include <stdio.h>
 
int main(int argc, char *argv[]) {
    int x = atoi(argv[1]);
    printf("Result: %d\n", f(x));
    return 0;
}

int f(int x) {
    int n = 1;
    int acc = 1;
    while (acc < x) {
        acc = acc + n;
        n++;
    };
    return n;
}
