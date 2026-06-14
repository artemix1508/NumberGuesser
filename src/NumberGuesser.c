#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int random_num = (rand() % 100) + 1;
    printf("Hello, This is my first C program for BoredOS!\n");
    printf("Guess the number between 1 and 100: ");
    while (1) {
        int guess = 0;
        if (scanf("%d", &guess) != 1) {
            printf("Invalid input. Please enter a valid number: ");
            while (getchar() != '\n');
            continue;
        }
        if (guess < random_num) {
            printf("Too low! Try again: ");
        } else if (guess > random_num) {
            printf("Too high! Try again: ");
        } else if (guess == random_num) {
            printf("Congratulations! You guessed the number %d correctly!\n", random_num);
            break;
        }
        else {
            printf("Invalid input. Please enter a number between 1 and 100: ");
        }
    }  
}