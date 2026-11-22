#include <math.h>
#include "inaccuracy.c"

struct TaylorRes {
    double reference;
    double sum;
    int n;
};

struct TaylorRes TaylorSin (double x0, double accuracy, int elements, char printall) {
    double reference = sin(x0);
    double sum = 0;
    double element = x0;
    double next_element;
    
    sum += element;
    if (printall)
        printf("    1\t%.16lf\t%.16lf\t%.16lf\n", sum, reference, sum - reference);

    int n;
    for (n = 1; 2*n + 1 <= elements; n++) {
        next_element = -element * (pow(x0, 2) / ((2*n) * (2*n + 1)));
        //if ((((next_element > 0) ? 1 : -1) * next_element) < accuracy)
        if (Inaccuracy(element, next_element, accuracy))
            break;
        element = next_element;
        sum += element;

        if (printall)
            printf("%5d\t%.16lf\t%.16lf\t%.16lf\n", 2*n+1, sum, reference, sum - reference);
    }

    struct TaylorRes result = {reference, sum, (2*n + 1) - 1};
    return result;
}

struct TaylorRes TaylorCos (double x0, double accuracy, int elements, char printall) {
    double reference = cos(x0);
    double sum = 0;
    double element = 1;
    double next_element;
    
    sum += element;
    if (printall)
        printf("    1\t%.16lf\t%.16lf\t%.16lf\n", sum, reference, sum - reference);

    int n;
    for (n = 1; 2*n <= elements; n++) {
        next_element = -element * (pow(x0, 2) / ((2*n - 1) * (2*n)));
        //if ((((next_element > 0) ? 1 : -1) * next_element) < accuracy)
        if (Inaccuracy(element, next_element, accuracy))
            break;
        element = next_element;
        sum += element;

        if (printall)
            printf("%5d\t%.16lf\t%.16lf\t%.16lf\n", 2*n+1, sum, reference, sum - reference);
    }

    struct TaylorRes result = {reference, sum, (2*n) - 1};
    return result;
}

struct TaylorRes TaylorExp (double x0, double accuracy, int elements, char printall) {
    double reference = exp(x0);
    double sum = 0;
    double element = 1;
    double next_element;
    
    sum += element;
    if (printall)
        printf("    1\t%.16lf\t%.16lf\t%.16lf\n", sum, reference, sum - reference);

    int n;
    for (n = 1; 2*n <= elements; n++) {
        next_element = element * x0 / n;
        //if ((((next_element > 0) ? 1 : -1) * next_element) < accuracy)
        if (Inaccuracy(element, next_element, accuracy))
            break;
        element = next_element;
        sum += element;

        if (printall)
            printf("%5d\t%.16lf\t%.16lf\t%.16lf\n", 2*n+1, sum, reference, sum - reference);
    }

    struct TaylorRes result = {reference, sum, (2*n) - 1};
    return result;
}

struct TaylorRes TaylorAsinh (double x0, double accuracy, int elements, char printall) {
    double reference = asinh(x0);
    double sum = 0;
    double next_element;
    int n;
    struct TaylorRes result;

    if (((x0 >= 0) ? x0 : -x0) <= 1) {
        double element = x0;
        sum += element;

        if (printall)
            printf("    2\t%.16lf\t%.16lf\t%.16lf\n", sum, reference, sum - reference);
        
        for (n = 1; 2*n + 1 < elements; n++) {
            next_element = -element * (pow(x0, 2) * pow((2*n - 1), 2) / ((2*n) * (2*n + 1)));
            if (Inaccuracy(element, next_element, accuracy))
                break;
            element = next_element;
            sum += element;

            if (printall)
                printf("%5d\t%.16lf\t%.16lf\t%.16lf\n", 2*n+2, sum, reference, sum - reference);
        }

        result.reference = reference;
        result.sum = sum;
        result.n = (2*n + 1) - 1;
    } else {
        double element = 1 / (4*pow(x0, 2));
        
        sum += log(2*x0);
        if (printall)
            printf("    1\t%.16lf\t%.16lf\t%.16lf\n", sum, reference, sum - reference);
        sum += element;
        if (printall)
            printf("    2\t%.16lf\t%.16lf\t%.16lf\n", sum, reference, sum - reference);

        for (n = 1; 2*n + 1 < elements; n++) {
            next_element = -element * (n * (2*n + 1) / (2 * pow((n + 1), 2) * pow(x0, 2)));
            if (Inaccuracy(element, next_element, accuracy))
                break;
            element = next_element;
            sum += element;

            if (printall)
                printf("%5d\t%.16lf\t%.16lf\t%.16lf\n", 2*n+2, sum, reference, sum - reference);
        }

        result.reference = reference;
        result.sum = sum;
        result.n = (2*n + 1 + 1) - 1; // засчёт ln +1 слагаемое
    }

    return result;
}
