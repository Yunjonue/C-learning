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
количество слагаемых, которое было вычислено.


При работе в режиме 2 пользователь должен иметь возможность:
выбрать функцию,
задать точку x, в которой необходимо вычислить значение,
задать число экспериментов (NMax - от 1 до 25).
По результатам расчета программа должна вывести следующую информацию:
эталонное значение (полученное с использованием встроенных математических функций языка программирования С),
таблицу из NMax строк со следующими столбцами: кол-во слагаемых (от 1 до NMax), вычисленную оценку значения функции, разницу между оценкой и эталонным значением.*/

#include <stdio.h>
#include <string.h>
#include "taylor.c"
// #include <float.h>

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

int main (void) {
    char func[6];
    double x0, accuracy, max_term;

    while (1) {
        struct TaylorRes result;

        printf("Choose a mode:\n1. Calculate once\n2. Serial experiment\nAny other - exit\n> ");
        char answer = getchar();
        if (answer == '1') {
            do {
                printf("Choose a function that you need to count: sin, cos, exp, asinh\n> ");
                scanf("%s", &func);
            } while ((strcmp(func, "sin") != 0) && (strcmp(func, "cos") != 0) && (strcmp(func, "exp") != 0) && (strcmp(func, "asinh") != 0));
            printf("Set an X that you want to count a function value for\n> ");
            scanf("%lf", &x0);
            printf("Set an accuracy that you need\n> ");
            scanf("%lf", &accuracy);
            printf("Set a limit of terms\n> ");
            scanf("%lf", &max_term);
            getchar();

            printf("Func\t\tRef               \tRes               \tDiff              \tTerm (without 0-s)\n");

            if (strcmp(func, "sin") == 0) {
                result = TaylorSin(x0, accuracy, max_term, 0);
            } else if (strcmp(func, "cos") == 0) {
                result = TaylorCos(x0, accuracy, max_term, 0);
            } else if (strcmp(func, "exp") == 0) {
                result = TaylorExp(x0, accuracy, max_term, 0);
            } else if (strcmp(func, "asinh") == 0) {
                result = TaylorAsinh(x0, accuracy, max_term, 0);
            } else {
                printf("Error occured. Please press any key to exit the program and try to run again");
                getchar(); getchar();
                return 1;
            }

            printf("%s\t\t%.16lf\t%.16lf\t%.16lf\t%d\nPress any key to continue\n", func, result.reference, result.sum, result.sum - result.reference, result.n);
            getchar();
        } else if (answer == '2') {
            accuracy = -1;

            do {
                printf("Choose a function that you need to count: sin, cos, exp, asinh\nType 'exit' to quit the program\n> ");
                scanf("%s", &func);
            } while ((strcmp(func, "sin") != 0) && (strcmp(func, "cos") != 0) && (strcmp(func, "exp") != 0) && (strcmp(func, "asinh") != 0));
            printf("Set an X that you want to count a function value for\n> ");
            scanf("%lf", &x0);
            printf("Set an experiments number\n> ");
            scanf("%lf", &max_term);
            getchar();
            
            printf("Terms\tRes               \tRef               \tDiff              \n");
            
            if (strcmp(func, "sin") == 0) {
                TaylorSin(x0, accuracy, max_term, 1);
            } else if (strcmp(func, "cos") == 0) {
                TaylorCos(x0, accuracy, max_term, 1);
            } else if (strcmp(func, "exp") == 0) {
                TaylorExp(x0, accuracy, max_term, 1);
            } else if (strcmp(func, "asinh") == 0) {
                TaylorAsinh(x0, accuracy, max_term, 1);
            } else {
                printf("Error occured. Please press any key to exit the program and try to run again");
                getchar(); getchar();
                return 1;
            }

            printf("Press any key to continue\n");
            getchar();
        } else {
            return 0;
        }
    }
}