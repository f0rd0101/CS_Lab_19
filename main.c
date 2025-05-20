#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void inputArray(double *arr, int size, const char *name) {
    for (int i = 0; i < size; i++) {
        printf("%s[%d] = ", name, i + 1);
        scanf("%lf", &arr[i]);
    }
}


void processX(double *x, int n, double *A, double *B) {
    double s = 0, p = 1, sumSin = 0, sumCos = 0;

    for (int i = 0; i < n; i++) {
        s += x[i];
        p *= x[i];
        sumSin += x[i] * sin(x[i]);
        sumCos += x[i] * cos(x[i]);
    }

    *A = p * sumSin;
    *B = s * sumCos;
}


void processY(double *y, int m, double *C, double *D) {
    double s = 0, p = 1, sumTan = 0, sumAbsSin = 0;

    for (int i = 0; i < m; i++) {
        s += y[i];
        p *= y[i];
        sumTan += y[i] * tan(y[i]);
        sumAbsSin += fabs(sin(y[i]));
    }

    *D = p * sumTan;
    *C = s * sumAbsSin;
}

int main() {
    int n, m;
    double *x, *y;

    printf("Введіть кількість елементів масиву x: ");
    scanf("%d", &n);
    x = (double *)malloc(n * sizeof(double));
    if (x == NULL) {
        printf("Помилка виділення памʼяті для x.\n");
        return 1;
    }
    inputArray(x, n, "x");

    printf("Введіть кількість елементів масиву y: ");
    scanf("%d", &m);
    y = (double *)malloc(m * sizeof(double));
    if (y == NULL) {
        printf("Помилка виділення памʼяті для y.\n");
        free(x);
        return 1;
    }
    inputArray(y, m, "y");

    double A, B, C, D;
    processX(x, n, &A, &B);
    processY(y, m, &C, &D);

    double denominator = sin(D) + fabs(cos(D));
    double eta;

    printf("\nРезультати:\n");
    printf("A = %.4lf\n", A);
    printf("B = %.4lf\n", B);
    printf("C = %.4lf\n", C);
    printf("D = %.4lf\n", D);

    if (fabs(denominator) < 1e-6) {
        printf("Помилка: знаменник дорівнює нулю! Неможливо обчислити η.\n");
    } else {
        eta = (A + B * cos(C)) / denominator;
        printf("η = %.4lf\n", eta);
    }

   
    free(x);
    free(y);

    return 0;
}
