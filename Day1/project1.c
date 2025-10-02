#include <stdio.h>

int main() {
    int age;
    char name[21];

    printf("NAME: Michelo\n AGE:19\n HOBBY:Reading\n");

    printf("Please enter your name: ");
    scanf("%20s", name);

    printf("How old are you? ");
    scanf("%d", &age);

    printf("Hi %s, of %d years!\n", name, age);

    return 0;
}
