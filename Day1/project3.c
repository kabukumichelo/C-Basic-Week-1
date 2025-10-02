#include<stdio.h>
int main(){
    int num1, num2, sum, product, difference;
    float quotient;
    printf("please your first value\n");
    scanf("%d", &num1);
    printf("please enter your second value\n");
    scanf("%d", &num2);
    sum=num1+num2;
    difference=num1-num2;
    product=num1*num2;
    quotient=num1/num2;
    printf("sum=%d\n", sum);
    printf("difference=%d\n", difference);
    printf("product=%d\n", product);
    if(num2 !=0) {
        printf("quotient=%f\n", quotient);} else {printf("divission by zero is not allowed!\n");}
    return 0;
}
