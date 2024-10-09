#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main() {

    int a[SIZE], i;
    long sum = 0;
    long sum2 = 0;
    
    #pragma omp parallel for private(i) shared(a)
    for (i = 0; i < SIZE; i++) {
        a[i] = i;
    }

    #pragma omp parallel for reduction(+:sum) private(i)
    for (i = 0; i < SIZE; i++) {
        sum += a[i];
    }

    #pragma omp parallel for shared(sum2)
    for (i = 0; i < SIZE; i++) {
        #pragma omp critical
        sum2 += i;
    }

    printf("Total sum = %ld\n", sum);
    printf("Total sum2 = %ld\n", sum2);

    return 0;
}