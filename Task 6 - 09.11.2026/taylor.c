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
#include <math.h>
#include <string.h>
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

double Inaccuracy (double t1, double t2, double accuracy) {
    double res = fabs(t2)/(1 - fabs(t2/t1));
    if ((fabs(t2/t1) < 1) && (res < accuracy))
        return 1;
    return 0;
};

struct TaylorRes {
    double sum;
    int n;
};

struct TaylorRes TaylorSin (double x0, double accuracy, int elements) {
    double sum = 0;
    double element = x0;
    double next_element;
    sum += element;

    int n;
    for (n = 1; 2*n + 1 <= elements; n++) {
        next_element = -element * (pow(x0, 2) / ((2*n) * (2*n + 1)));
        //if ((((next_element > 0) ? 1 : -1) * next_element) < accuracy)
        if (Inaccuracy(element, next_element, accuracy))
            break;
        element = next_element;
        sum += element;
    }

    struct TaylorRes result = {sum, n};
    return result;
}

struct TaylorRes TaylorCos (double x0, double accuracy, int elements) {
    double sum = 0;
    double element = 1;
    double next_element;
    sum += element;

    int n;
    for (n = 1; 2*n <= elements; n++) {
        next_element = -element * (pow(x0, 2) / ((2*n - 1) * (2*n)));
        //if ((((next_element > 0) ? 1 : -1) * next_element) < accuracy)
        if (Inaccuracy(element, next_element, accuracy))
            break;
        element = next_element;
        sum += element;
    }

    struct TaylorRes result = {sum, n};
    return result;
}

struct TaylorRes TaylorExp (double x0, double accuracy, int elements) {
    double sum = 0;
    double element = 1;
    double next_element;
    sum += element;

    int n;
    for (n = 1; 2*n <= elements; n++) {
        next_element = element * x0 / n;
        //if ((((next_element > 0) ? 1 : -1) * next_element) < accuracy)
        if (Inaccuracy(element, next_element, accuracy))
            break;
        element = next_element;
        sum += element;
    }

    struct TaylorRes result = {sum, n};
    return result;
}

struct TaylorRes TaylorAsinh (double x0, double accuracy, int elements) {
    double sum = 0;
    double next_element;
    int n;

    if (((x0 >= 0) ? x0 : -x0) <= 1) {
        double element = x0;
        sum += element;
        
        for (n = 1; 2*n + 1 < elements; n++) {
            next_element = -element * (pow(x0, 2) * pow((2*n - 1), 2) / ((2*n) * (2*n + 1)));
            if (Inaccuracy(element, next_element, accuracy))
                break;
            element = next_element;
            sum += element;
        }
    } else {
        double element = 1 / (4*pow(x0, 2));
        sum += log(2*x0) + element;

        for (n = 1; 2*n + 1 < elements; n++) {
            next_element = -element * (n * (2*n + 1) / (2 * pow((n + 1), 2) * pow(x0, 2)));
            if (Inaccuracy(element, next_element, accuracy))
                break;
            element = next_element;
            sum += element;
        }
    }

    struct TaylorRes result = {sum, n};
    return result;
}

int main (void) {
    char func[6];
    double x0, accuracy, max_term;

    while (1) {
        struct TaylorRes result;
        double reference;

        printf("Choose a mode:\n1. Calculate once\n2. Serial experiment\nAny other - exit\n> ");
        char answer = getchar();
        if (answer == '1') {
            do {
                printf("Choose a function that you need to count: sin, cos, exp, asinh\nType 'exit' to quit the program\n> ");
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
                result = TaylorSin(x0, accuracy, max_term);
                reference = sin(x0);
            } else if (strcmp(func, "cos") == 0) {
                result = TaylorCos(x0, accuracy, max_term);
                reference = cos(x0);
            } else if (strcmp(func, "exp") == 0) {
                result = TaylorExp(x0, accuracy, max_term);
                reference = exp(x0);
            } else if (strcmp(func, "asinh") == 0) {
                result = TaylorAsinh(x0, accuracy, max_term);
                reference = asinh(x0);
            } else {
                printf("Error occured. Please press any key to exit the program and try to run again");
                getchar(); getchar();
                return 1;
            }

            printf("%s\t\t%.16lf\t%.16lf\t%.16lf\t%d\nPress any key to continue\n", func, reference, result.sum, result.sum - reference, result.n);
            getchar();
        }
    }
        
    return 0;
}