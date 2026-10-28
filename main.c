
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <locale.h>

#define X_MIN 5.0
#define X_MAX 70.0

#define Q0 50.0
#define DELTA_Q 7.0

#define STATE_NORMAL 0
#define STATE_ALARM  1

int read_input(double *x);
double compute_q(double x);
int control(double q);
void compute_statistics(void);

int main(void)
{
    setlocale(LC_ALL, "");

    double x;
    double q;
    int state;

    printf("Вариант 33. Мониторинг реактора: расход азота\n");
    printf("Программа преобразует показание датчика расхода азота\n");
    printf("в показатель Q и контролирует состояние процесса.\n\n");

    printf("Введите расход азота X (%.0f..%.0f л/мин): ",
           X_MIN, X_MAX);

    if (!read_input(&x))
    {
        printf("Ошибка: необходимо ввести число.\n");
        return 1;
    }

    if (x < X_MIN || x > X_MAX)
    {
        printf("Ошибка: X должен находиться в диапазоне "
               "%.0f..%.0f л/мин.\n", X_MIN, X_MAX);
        return 1;
    }

    q = compute_q(x);

    state = control(q);

    printf("\nРезультаты измерения:\n");
    printf("X = %.2f л/мин\n", x);
    printf("Q = %.2f\n", q);

    if (state == STATE_ALARM)
    {
        printf("Состояние: ТРЕВОГА\n");
    }
    else
    {
        printf("Состояние: НОРМА\n");
    }
 
    compute_statistics();

    return 0;
}

int read_input(double *x)
{
    return scanf("%lf", x) == 1;
}

double compute_q(double x)
{
    if (x < 20.0)
    {
        return (x - 20.0) * (x - 20.0) / 6.0 + 10.0;
    }
    else if (x <= 45.0)
    {
        return 3.0 * (x - 32.5) + 50.0;
    }
    else
    {
        return 2.0 * sqrt(x - 45.0 + 1.0) + 60.0;
    }
}

int control(double q)
{
    if (fabs(q - Q0) > DELTA_Q)
    {
        return STATE_ALARM;
    }

    return STATE_NORMAL;
}

void compute_statistics(void)
{
    
}
