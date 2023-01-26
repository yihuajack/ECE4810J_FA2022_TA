#include <stdio.h>
#include "dct.h"

int main() {
    // short a[N][N], b[N][N], b_expected[N][N];
    short a[N], b[N], c[N];
    int i, tmp;
    FILE *fp;

    fp = fopen("input.dat", "r");
    for (i = 0; i < N; i++) {
        // for (j = 0; j < N; j++) {
        fscanf(fp, "%d", &tmp);
        //     a[i][j] = tmp;
        // }
        a[i] = tmp;
    }
    fclose(fp);
    dct(a, b);
    // idct(b, c);

#if 0
    fp = fopen("output.golden.dat", "r");
    for (i = 0; i < N; i++) {
        // for (j = 0; j < N; j++) {
        fscanf(fp, "%d", &tmp);
        //     b_expected[i][j] = tmp;
        // }
        b_expected[i] = tmp;
    }
    fclose(fp);

    for (i = 0; i < N; ++i) {
        if (b[i] != b_expected[i]){
            printf("Incorrect output on sample %d. Expected %d, Received %d \n", i, b_expected[i], b[i]);
            retval = 2;
        }
    }
#endif

#if 1 // Optionally write out computed values
    fp = fopen("output.dat", "w");
    for (i = 0; i < N; i++) {
        // for (j = 0; j < N; j++) {
        fprintf(fp, "%d\n", b[i]);
        // }
        // fprintf(fp, "\n");
    }
    fclose(fp);
#endif

#if 0
    if (retval != 2) {
        printf("    *** *** *** *** \n");
        printf("    Results are good \n");
        printf("    *** *** *** *** \n");
    } else {
        printf("    *** *** *** *** \n");
        printf("    BAD!! \n");
        printf("    *** *** *** *** \n");
    }
#endif

    return 0;
}
