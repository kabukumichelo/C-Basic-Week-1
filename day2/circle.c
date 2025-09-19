#include <stdio.h>
#include <stdlib.h>

int main() {
    float radius, Pi, Area;
    Pi = 3.14;
    printf("Please enter the radius of your circle: ");
    scanf("%f", &radius);
    Area = Pi * radius * radius;
    printf("The Area of your circle is: %f square units\n", Area);
    return 0;
}
