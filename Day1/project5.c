#include <stdio.h>

int main() {
    double num1, num2;
    char operation;

    printf("please enter the first number:\n ");
    scanf("%lf", &num1);
    printf("Please enter the second number:\n ");
    scanf("%lf", &num2);
    
    printf("Choose an operation \n+\n -\n *\n /\n: ");
    scanf(" %c", &operation);
    switch (operation) {
        case '+':
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, num1 + num2);
            break;
        case '-':
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, num1 - num2);
            break;
        case '*':
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, num1 * num2);
            break;
        case '/':
            if (num2 != 0) {
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, num1 / num2);
            } else {
                printf("Error: Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Error: Invalid operation.\n");
    }

    return 0;
}
