#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
    int months;
    double contribution;
    double rate_of_return;
};
typedef struct _retire_info retire_info;

double printBalanceInfo(retire_info info, double balance, int startAge) {
    int ageYear = startAge / 12;
    int ageMonth = startAge % 12;

    for (int i = 0; i < info.months; ++i) {
        printf("Age %3d month %2d you have $%.2lf\n", ageYear, ageMonth, balance);
        balance += balance * info.rate_of_return + info.contribution;
        ageMonth = (ageMonth + 1) % 12;
        if (ageMonth == 0) ++ageYear;
    }
    return balance;
}

void retirement(int startAge, double initial, retire_info working,
                retire_info retired) {
    double balanceBeforeRetirement =  printBalanceInfo(working, initial, startAge);
    int ageBeforeRetirement = startAge + working.months;
    printBalanceInfo(retired, balanceBeforeRetirement, ageBeforeRetirement);
}

int main () {
    retire_info working;
    working.months = 489;
    working.contribution = 1000;
    working.rate_of_return = 0.045 / 12;

    retire_info retired;
    retired.months = 384;
    retired.contribution = -4000;
    retired.rate_of_return = 0.01 / 12;

    int startAge = 327;
    double balance = 21345;

    retirement(startAge, balance, working, retired);
    return EXIT_SUCCESS;
}
