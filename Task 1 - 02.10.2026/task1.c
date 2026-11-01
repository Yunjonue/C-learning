/* Фирма «Умелые ручки» выпускает двухдверные одежные шкафы.
Состав шкафа:
накладная задняя стенка из ДВП высотой h от 180 до 220 см, шириной w от 80 до 120 см и толщиной 5 мм,
две боковины из ДСП высотой h, глубиной d от 50 до 90 см и толщиной 15 мм,
накладные верхняя и нижняя крышки из ДСП шириной w, глубиной d и толщиной 15 мм,
две накладные двери из дерева высотой h, общей шириной w и толщиной 1 см,
внутренние полки в шкафу через каждый 40 см из ДСП.
Считая, что известны плотности ДСП, ДВП и дерева, найти массу шкафа. */

#include <stdio.h>

// Все плотности в кг/м^3
#define FIBERBOARD_DENSITY      900 // плотность ДВП
#define PARTICLEBOARD_DENSITY   700 // плотность ДСП
#define WOOD_DENSITY            700 // плотность дерева

double calculate(double height, double width, double depth) {
    // Поправки на толщину материала не делаем, т. к. в условии даны указания на h, w, d.
    double mass;
    mass += (height * width * 5 / 1000000000) * FIBERBOARD_DENSITY;
    mass += 2 * (height * depth * 15 / 1000000000) * PARTICLEBOARD_DENSITY;
    mass += 2 * (width * depth * 15 / 1000000000) * PARTICLEBOARD_DENSITY;
    mass += (height * width * 10 / 1000000000) * WOOD_DENSITY;
    mass += (double)(int)(height / 400 - 1) * (width * depth * 15 / 1000000000) * PARTICLEBOARD_DENSITY;
    // Толщину полок допускаем 15 мм, как остальные детали из ДСП
    return mass;
}

int main(void) {
    // Высота, ширина, глубина шкафа соответственно
    double height, width, depth;
    printf("Height, width and depth in mm: ");
    scanf("%lf %lf %lf", &height, &width, &depth);
    printf("Result: %lf kg\n", calculate(height, width, depth));
    return 0;
}
