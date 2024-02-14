#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

typedef struct _person_profile {
  int p_age;
  double p_balance;
} person_profile;

person_profile balance_updater(int age, double balance, retire_info info) {
  for (int i = 0; i < info.months; i++) {
    int month = age % 12;
    printf("Age %3d month %2d you have $%.2f\n", age / 12, month, balance);
    age++;
    balance = balance + info.contribution + balance * info.rate_of_return;
  }
  person_profile my_person;
  my_person.p_age = age;
  my_person.p_balance = balance;
  return my_person;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  person_profile working_person = balance_updater(startAge, initial, working);
  person_profile retired_person =
      balance_updater(working_person.p_age, working_person.p_balance, retired);
  retired_person.p_age += 0;
}

int main(void) {
  int me_age = 327;
  double me_balance = 21345;
  retire_info me_working;
  me_working.months = 489;
  me_working.contribution = 1000;
  me_working.rate_of_return = 0.045 / 12;
  retire_info me_retired;
  me_retired.months = 384;
  me_retired.contribution = -4000;
  me_retired.rate_of_return = 0.01 / 12;
  retirement(me_age, me_balance, me_working, me_retired);
  return EXIT_SUCCESS;
}
