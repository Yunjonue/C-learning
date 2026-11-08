/* Разработать программу, позволяющую выполнять расчет значений для некоторого набора функций в заданной точке с заданной погрешностью за счет разложения этих функций в ряд Тейлора.
Программа должна работать в двух режимах:
1. Однократный расчет функции в заданной точке.
2. Серийный эксперимент.
При работе в режиме 1 пользователь должен иметь возможность:
выбрать функцию,
задать точку x, в которой необходимо вычислить значение,
задать точность вычисления (от 0.000001 и больше),
задать число элементов ряда для выполнения расчета (N - от 1 до 1000).
Расчет оценки значения выбранной функции выполняется либо до достижения заданной точности, либо до исчерпания введенного числа слагаемых. По результатам расчета программа должна вывести следующую информацию:
эталонное значение (полученное с использованием встроенных математических функций языка программирования С),
вычисленную оценку значения функции,
разницу между оценкой и эталонным значением,
количество слагаемых, которое было вычислено. */

#include <stdio.h>
#include <math.h>
#include <float.h>

/* #define DELTA   DBL_TRUE_MIN

double Differential (double (*f)(double), double x0) {
    return (f(x0 + DELTA) - f(x0)) / DELTA;
}

double Factorial (double n) {
    double x = 1;
    for (int iter = 1; iter <= n - 1; iter++)
        x *= iter + 1;
    return x;
} */

struct TaylorRes {
    double sum;
    int n;
};

struct TaylorRes TaylorSin (double x0, double accuracy, int elements) {
    double sum = 0;
    double next_element = x0;
    sum += next_element;

    int n;
    for (n = 1; 2*n + 1 <= elements; n++) {
        next_element = -next_element * (pow(x0, 2) / ((2*n) * (2*n + 1)));
        if ((((next_element > 0) ? 1 : -1) * next_element / accuracy) < 1)
            break;
        sum += next_element;
    }

    struct TaylorRes sin_result = {sum, n};
    return sin_result;
}

int main (void) {
    double x0 = M_PI/3;

    printf("Ref               \tRes               \tDiff              \tTerm\n");
    struct TaylorRes result = TaylorSin(x0, 0.000001, 100);
    double reference = sin(x0);    
    printf("%.16lf\t%.16lf\t%.16lf\t%d", reference, result.sum, result.sum - reference, result.n);

    return 0;
}