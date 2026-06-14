#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned int seed = 12345;

static int my_rand() {
    seed = seed * 1103515245 + 12345;
    return (seed >> 16) & 0x7fff;
}

int main() {
    seed = (unsigned int)time(NULL);
    int random_num = (my_rand() % 100) + 1;
    printf("Hello, This is my first C program for BoredOS!\n");
    printf("Guess the number between 1 and 100: ");
    int guess = 0;
    while (1) {
        char buf[16];
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("Invalid input. Please enter a valid number: ");
            continue;
        }
        if (sscanf(buf, "%d", &guess) != 1) {
            printf("Invalid input. Please enter a valid number: ");
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

    }  
}