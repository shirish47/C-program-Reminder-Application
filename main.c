#include <stdio.h>
#include "menu.h"
#include "common.h"
#include "store.h"
#include <time.h>

int main(void)
{
 time_t rawtime;
 struct tm * timeinfo;

 // load reminders from file
 load_data(reminders);
 printf("************* Event Reminder Application *************\n");
 int choice;
 bool exe_reminder=false;
 while (choice != -1 ){  //run menu

  if(choice>=0){
    //get choice from main menu
    choice = main_menu();
    //do as user input(create reminder, delete reminder and view reminder)
    switch(choice){
      case 1: // create reminder
            create_reminder();
            choice =0;
      break;
      case 2: // delete reminder
            printf("******* Delete a reminder (select a number) *******\n");
            view_reminders();
            printf("************ Select from above a number ************\n");
            scanf("%d",&choice);
            getchar();
            if(choice <number_of_reminders)
              delete_reminder(choice);
            else
              printf("@@@@@@@@@@@@@@@@@@ wrong Choice @@@@@@@@@@@@@@@@@@\n");
            choice =0;
      break;
      case 3: // view reminders
            printf("\n************* View Reminders *************\n\n");
            view_reminders();
            choice =0;
      break;
      case 4: //execute reminders
          choice = -1;
          exe_reminder=true;
          printf("************* You choose Executing Reminders *************\n");
        break;
      case 5: //exit from application
          choice = -1;
          printf("************* Exited out of application *************\n\n");

      break;
      default:
          choice =0;
          printf("@@@@@@@@@@@@@@@@@@ wrong Choice @@@@@@@@@@@@@@@@@@\n");
    }//switch
    printf("press enter to continue.\n");
    getchar();
 }//if
}//while
if(exe_reminder)
  printf("@@@@@@@@@@@@@@@@@@ Executing Reminders @@@@@@@@@@@@@@@@@@\n");
while(exe_reminder)
{
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  //printf ( "\rCurrent local time and date: %s", asctime (timeinfo) );

  for(int i=0;i<number_of_reminders;i++)
    {
      if(reminders[i].time_date==timeinfo->tm_mday && reminders[i].time_month==(timeinfo->tm_mon+1) && reminders[i].time_year==(1900+timeinfo->tm_year) && reminders[i].time_hr==timeinfo->tm_hour && reminders[i].time_min==timeinfo->tm_min && !reminders[i].finished )
      {
        //show the reminder
        reminders[i].finished = true;
        printf("$$$$$$$$$$$$$ ALERT : you have a reminder $$$$$$$$$$$$$\n");
        print_reminder(i);
      }
    }
}
 return 0;
}
