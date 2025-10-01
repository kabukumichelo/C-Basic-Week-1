#include<stdio.h>
#define A 1.8
#define B 32
#define C (5.0/9.0)
int main(){
    int temp1, temp2;
    float celsius, Fahrenheit;

  
    printf("Enter temperature in Celsius: ");
    scanf("%d", &temp1);
    Fahrenheit = ((temp1 * A) + B);
    printf("Temperature in Fahrenheit: %f\n", Fahrenheit);

  
    printf("Enter temperature in Fahrenheit: ");
    scanf("%d", &temp2);
    celsius = (temp2 - B) * C;
    printf("Temperature in Celsius: %f\n", celsius);

    return 0;
