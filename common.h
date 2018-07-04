#ifndef COMMON_H
#define COMMON_H

#define MAX_REMINDERS 100
//reminder struct
typedef struct reminder{
  char title[32];
  char message[128];
  int time_hr;
  int time_min;
  int time_date;
  int time_month;
  int time_year;
  char file[24];
  bool finished;
}reminder_t;

//all reminders stored here after loading or creating
reminder_t reminders[MAX_REMINDERS];

int number_of_reminders = 0;

void print_reminder(int i)
{
  if(i<number_of_reminders)
  {
    printf("(%d)\tTitle: %s\n",i,reminders[i].title);
    printf("\tMessage: %s\n",reminders[i].message);
    printf("\tDate: %d/%d/%d at %d:%d\n",reminders[i].time_date,reminders[i].time_month,reminders[i].time_year,reminders[i].time_hr,reminders[i].time_min);
    printf("\tAudio file: %s\n",reminders[i].file);
  }
}

#endif
