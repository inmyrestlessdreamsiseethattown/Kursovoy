#include <stdio.h>
#include <math.h>
#include <locale.h>
#define _CRT_SECURE_NO_DEPRECATE

#define N 50
#define X_MIN 5.0
#define X_MAX 70.0
#define Q0 50.0
#define DELTA_Q 7.0
#define STAT_FIRST 16
#define STAT_LAST 27

double Q(double x);
const char* state_name(double q);

int main(void) {
    setlocale(LC_ALL, "RUS");

    double x[N], q[N];
    int i;

    printf("Мониторинг реактора: расход азота (вариант 33)\\n");
    printf("Введите %d измерений X (л/мин), каждое в диапазоне %.0f..%.0f.\\n",
        N, X_MIN, X_MAX);

    for (i = 0; i < N; ++i) {
        printf("X[%d] = ", i + 1);
        if (scanf("%lf", &x[i]) != 1) {
            fprintf(stderr, "Ошибка: ожидалось числовое значение.\\n");
            return 1;
        }
        if (x[i] < X_MIN || x[i] > X_MAX) {
            fprintf(stderr, "Ошибка: X[%d] вне допустимого диапазона %.0f..%.0f.\\n",
                i + 1, X_MIN, X_MAX);
            return 1;
        }
        q[i] = Q(x[i]);
    }

    printf("\\n%-6s %-12s %-12s %-22s\\n", "№", "X, л/мин", "Q(X)", "Состояние");
    printf("----------------------------------------------------------\\n");
    for (i = 0; i < N; ++i) {
        printf("%-6d %-12.2f %-12.4f %-22s\\n",
            i + 1, x[i], q[i], state_name(q[i]));
    }

    printf("\\nСтатистический анализ Q[16..27] (индексация с 1):\\n");
    {
        int min_i = STAT_FIRST - 1;
        int max_i = STAT_FIRST - 1;
        for (i = STAT_FIRST; i < STAT_LAST; ++i) {
            if (q[i] < q[min_i]) min_i = i;
            if (q[i] > q[max_i]) max_i = i;
        }
        printf("Минимум: Q[%d] = %.4f (X = %.2f л/мин)\\n",
            min_i + 1, q[min_i], x[min_i]);
        printf("Максимум: Q[%d] = %.4f (X = %.2f л/мин)\\n",
            max_i + 1, q[max_i], x[max_i]);
        printf("Индекс расположения минимума: %d\\n", min_i + 1);
        printf("Индекс расположения максимума: %d\\n", max_i + 1);
    }

    return 0;
}

double Q(double x) {
    if (x < 20.0) {
        double d = x - 20.0;
        return d * d / 6.0 + 10.0;
    }
    else if (x <= 45.0) {
        return 3.0 * (x - 32.5) + 50.0;
    }
    else {
        return 2.0 * sqrt(x - 45.0 + 1.0) + 60.0;
    }
}

const char* state_name(double q) {
    if (fabs(q - Q0) > DELTA_Q) {
        return "ТРЕВОГА";
    }
    return "НОРМА";
}
