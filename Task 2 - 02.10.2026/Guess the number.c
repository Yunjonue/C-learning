/* В программе должно быть предусмотрено два режима.

Режим 1. Программа «загадывает» случайное число из диапазона от 1 до 1000.
Пользователь должен вводить отгадки, на которые программа сообщает: «загаданное число больше», «загаданное число меньше», «угадали».
Работа завершается, когда пользователь угадает число. Также программа должна подсчитывать число попыток и выводить его в конце работы.

Режим 2. Пользователь загадывает число из диапазона от 1 до 1000 и вводит его.
Программа пытается «угадать» число, выводя на экран отгадки, на которые пользователь вводит >, < или =.
Работа завершается, когда программа угадает число. Также программа должна подсчитывать число попыток и выводить его в конце работы. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clear_input() {
    while (getchar() != '\n'); // выбросить мусор до конца строки
}

void first_mode() {
    int number, guess;
    number = rand() % 1000 + 1;

    printf("I set a number from 1 to 1000. Good luck :)\nYour guess >>> ");
    do {
        scanf("%d", &guess);

        if (guess < number)
            printf("The set number is greater\n>>> ");
        
        else if (guess > number)
            printf("The set number is smaller\n>>> ");

        else if (guess == number) {
            printf("Guessed! Press enter to enter the main menu\n");
            clear_input();
            getchar();
            clear_input();
        }
        
        else
            printf("Try again");
    } while (guess != number);
}

void second_mode() {
    int number, guess;
    int minimum = 1;
    int maximum = 1000;
    printf("You'll set a number from 1 to 1000 and I'll try to guess it.\nHelp me by replying \">\", \"<\" or \"=\".\nIt's, literally, \"set number is greater\", \"set number is smaller\" and \"set number is guessed\".\nSet a number from 1 to 1000 >>> ");
    
    scanf("%d", &number);
    while (number < 1 || number > 1000) {
        printf("Set a number from 1 to 1000 >>> ");
        clear_input();
        scanf("%d", &number);
    }

    do {
        guess = minimum + rand() % (maximum - minimum + 1);

        printf("%d. Is it right? >>> ", guess);

        clear_input();
        switch (getchar()) {
            case '>':
                minimum = guess + 1;
                break;

            case '<':
                maximum = guess - 1;
                break;
            
            case '=':
                printf("Guessed! Press enter to enter the main menu\n");
                clear_input();
                getchar();
                clear_input();
                goto main_menu;
            
            default:
            printf("Can't understand your input :(\nLet's try again\n");
                break;
        }
    } while (1);

    main_menu:
}

int main(void) {
    int mode;

    srand((unsigned int)time(NULL));

    while (1) {
        printf("Choose a game mode\n1 - you are guessing a number\n2 - the progam is guessing a number\nOther inputs close the program\nYour choice is >>> ");
        
        switch (getchar()) {
            case '1':
                first_mode();
                break;
            
            case '2':
                second_mode();
                break;
            
            default:
                goto exiting;
        }
    }

    exiting:
    return 0;
}
