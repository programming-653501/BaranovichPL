#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x, sum = 0, prod = 1, amount = 0;

    printf("Please, enter x: ");
    scanf("%d", &x);

    while (x){
        sum += x % 10;
        prod *= x % 10;
        x /= 10;
        ++amount;
    }
    if (amount == 3)
        printf("The product of the digits: %d", prod);
    else
        printf("The sum of the digits: %d", sum);

    return 0;
}
