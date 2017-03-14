#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

double power(double x, int n) {
	double result = 1.0;
	while (n){
		if (n & 1) result *= x;
		x *= x;
		n >>= 1;
	}
	return result;
}

double my_sinus(double x, double accuracy){
    double answer = 0.0, factorial, augend = accuracy + 1.0;
    int i = 2, n, sign = 1;

    if (x > 0)
        while (x >= 2 * M_PI)
            x -= 2 * M_PI;
    else
        while (x < 0)
            x += 2 * M_PI;

    answer = x;
    factorial = 1;
    while (fabs(augend) >= accuracy){
        n = i / 2;
        factorial *= i * (i + 1);
        sign *= -1;
        augend = sign * power(x, i + 1) / factorial;
        answer += augend;
        i += 2;
    }

    return answer;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    double x, accuracy;

	printf("Введите значение угла: ");
	scanf("%lf", &x);
	x = x * M_PI / 180;
	printf("Введите погрешность: ");
  	scanf("%lf", &accuracy);

	printf("\nВычисленное значение синуса: ");
	printf("%0.7lf", my_sinus(x, accuracy));

	printf("\nЗначение стандартной функции sin: ");
	printf("%0.7lf", sin(x));

    return 0;
}
