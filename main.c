#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <locale.h>

#define X_MIN 5.0
#define X_MAX 70.0

#define Q0 50.0
#define DELTA_Q 7.0

#define STATE_NORMAL 0
#define STATE_ALARM 1

double read_input(void);
double compute_q(double x);
int control(double q);
void print_state(int code);
void compute_statistics(void);

int main(void)
{
    setlocale(LC_ALL, "");

    double x;
    double q;
    int state;

    printf("Мониторинг реактора: расход азота\n");
    printf("Вариант 33\n\n");

    x = read_input();

    q = compute_q(x);

    state = control(q);

    printf("\nX = %.2f л/мин\n", x);
    printf("Q = %.2f\n", q);

    print_state(state);

    compute_statistics();

    return 0;
}


double read_input(void)
{
    double x;

    printf("Введите расход азота X (%.0f..%.0f л/мин): ",
        X_MIN, X_MAX);

    if (scanf("%lf", &x) != 1)
    {
        printf("Ошибка: введено не число.\n");
        return X_MIN;
    }

    if (x < X_MIN || x > X_MAX)
    {
        printf("Ошибка: значение вне допустимого диапазона.\n");
        return X_MIN;
    }

    return x;
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
        return STATE_ALARM;

    return STATE_NORMAL;
}


void print_state(int code)
{
    if (code == STATE_ALARM)
        printf("Состояние: ТРЕВОГА\n");
    else
        printf("Состояние: НОРМА\n");
}


void compute_statistics(void)
{
    /*
        STATISTICS

        На КТ2 здесь будет реализован анализ
        массива значений Q на участке Q[16..27].
    */
}
