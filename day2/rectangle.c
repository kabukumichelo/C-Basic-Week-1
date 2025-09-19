#include <stdio.h>
#include <stdlib.h>

int main() {
    float length, width, Area;

    printf("Please enter length: ");
    scanf("%f", &length);

    printf("Please enter width: ");
    scanf("%f", &width);

    Area = length * width;

    printf("The area of your Rectangle is: %f\n", Area);

    return 0;
}
