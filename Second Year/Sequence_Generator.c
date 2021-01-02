#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    unsigned long int i, n;
    double x;

    if (argc != 2) {
        printf("USAGE: genseq <n>\n");
        return 1;
    }

    sscanf(argv[1], "%lu", &n);
    printf("%lu\n", n);
    
    srandom(time(NULL));
    for (i = 0; i < n; ++i) {
        x = 1000.0 * random() / RAND_MAX;
        printf("%.3lf\n", x);
    }

    return 0;
}
