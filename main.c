#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <locale.h>

#define X_MIN 5.0
#define X_MAX 70.0

#define X_LOW 20.0
#define X_HIGH 45.0
#define X_CENTER 32.5

#define Q_LOW_OFFSET 10.0
#define Q_MID_OFFSET 50.0
#define Q_HIGH_OFFSET 60.0

#define Q_LOW_DIVISOR 6.0
#define Q_MID_FACTOR 3.0
#define Q_HIGH_FACTOR 2.0
#define SQRT_OFFSET 1.0

#define Q0 50.0
#define DELTA_Q 7.0

#define STATE_NORMAL 0
#define STATE_ALARM 1

int read_input(double *x);
double compute_q(double x);
int control(double q);
void compute_statistics(void);

int main(void)
{
    double x;
    double q;
    int state;

    setlocale(LC_ALL, "");

    printf("Курсовой проект. Вариант 33\n");
    printf("Мониторинг реактора: расход азота\n");
    printf("Программа преобразует показание датчика ");
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
        printf("Ошибка: X вне допустимого диапазона.\n");
        return 1;
    }

    q = compute_q(x);
    state = control(q);

    printf("\nX = %.2f л/мин\n", x);
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
    if (x < X_LOW)
    {
        return (x - X_LOW) * (x - X_LOW)
               / Q_LOW_DIVISOR + Q_LOW_OFFSET;
    }
    else if (x <= X_HIGH)
    {
        return Q_MID_FACTOR * (x - X_CENTER)
               + Q_MID_OFFSET;
    }
    else
    {
        return Q_HIGH_FACTOR * sqrt(x - X_HIGH + SQRT_OFFSET)
               + Q_HIGH_OFFSET;
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

// Заглушка статистики для КТ2
void compute_statistics(void)
{
   
}
