#ifndef MENU_H
#define MENU_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"
#include "store.h"

// first menu, choices happen here
int main_menu()
{
  int options = 5;
  int choice = 0;

  printf("@@@@@@@@@@@@@@@@@@ Main Menu @@@@@@@@@@@@@@@@@@\n");
  printf("Select any one option from the following\n");
  printf("1) Create Reminder\n");
  printf("2) Delete Reminder\n");
  printf("3) View Reminder\n");
  printf("4) Execute Reminders\n");
  printf("5) Exit from application\n");

  printf("\nWaiting for input\n\n");
  printf("input : ");
  scanf("%d", &choice);
  getchar();
  if( options >= choice && 1 <= choice) //choice is valid and with in the limits
    return choice;
  else
    return -1;
}

//create reminder until user don't put correct input
reminder_t create_reminder()
{
  int options = 7;
  int choice = 0;
  bool done = false;
  bool confirm = false;
  int date_val[3];
  int time_val[2];
  reminder_t C_reminder;
  if( !(number_of_reminders<MAX_REMINDERS) )
    {
      printf("******** Reminder space full **********\n");
      return C_reminder;
    }
  do{
    printf("\n\n****************** Create Reminder ******************\n");
    printf("\n********** Follow steps to create Reminder **********\n");
    printf("\n** Enter Title (Note: no use of \",\" in the title) **\n");
    scanf("%[^\n]s",C_reminder.title);
    getchar();

    printf("\n\n** Type message (lenght within 128 charaters only) **\n");
    scanf("%[^\n]s",C_reminder.message);
    getchar();

    do{
      printf("\n\n*********** Provide date (DD/MM/YYYY) ************\n");
      char date[12];
      scanf("%[^\n]s",date);
      printf("Date: %s\n",date);
      getchar();
      char *p;
      p = strtok(date,"/");

      int itr=0;
      date_val[itr] = atoi(p);
      itr++;
      while(p!=NULL && itr<3){
        p = strtok(NULL,"/");
        date_val[itr] = atoi(p);
        itr++;
      }
      //validating the Range of values the date should have
      if( date_val[0]>0 && date_val[1]>0 && date_val[2]>0 && date_val[0]<32 && date_val[1]<13 && date_val[2]<3000 ){
        done = true;
        C_reminder.time_date = date_val[0];
        C_reminder.time_month = date_val[1];
        C_reminder.time_year = date_val[2];
      }
      if(!done)
      {
        printf("value input are not valid, try again\n");
      }
    }while(!done);


    done = false;
    do{
      printf("\n\n******* Enter time (HH:MM - 24 hrs format) *******\n");
      char r_time[7];
      scanf("%[^\n]s",r_time);
      printf("Time: %s\n",r_time);
      getchar();
      char *t_p;
      t_p = strtok(r_time,":");

      int itr=0;
      time_val[itr] = atoi(t_p);
      itr++;
      while( t_p!=NULL && itr<2 ){
        t_p = strtok(NULL,":");
        time_val[itr] = atoi(t_p);
        itr++;
      }
      ////validating the Range of values the date should have
      if( time_val[0]>=0 && time_val[1]>=0 && time_val[0]<24 && time_val[1]<60 ){
        done = true;
        C_reminder.time_hr = time_val[0];
        C_reminder.time_min = time_val[1];
      }
      if(!done)
      {
        printf("value input are not valid, try again\n");
      }
    }while(!done);
    done = false;

    printf("\n\n*** Name audio file to save(32 characters only) ***\n");
    scanf("%[^\n]s",C_reminder.file);
    getchar();
    printf("\n\n** Confirm following Reminder with Y(Yes)/N(No) **\n\n");
    printf("Title: %s\n",C_reminder.title);
    printf("Message: %s\n",C_reminder.message);
    printf("Date: %d/%d/%d at %d:%d\n",C_reminder.time_date,C_reminder.time_month,C_reminder.time_year,C_reminder.time_hr,C_reminder.time_min);
    printf("Audio file: %s\n",C_reminder.file);
    printf("\n\n Y/N:");
    char con[5];
    scanf("%s",con);
    getchar();
    if(con[0]=='Y' || con[0]=='y')
    {
      confirm = true;
      reminders[number_of_reminders]=C_reminder;
      number_of_reminders++;
      save_data(reminders);

      printf("\n**Thank you, saving the reminder.**\n\n");
    }else
    {
      printf("\n**Ok reset the reminder again.**\n\n");
    }

  }while(!confirm);
return C_reminder;
}


void view_reminders()
{
  if(number_of_reminders == 0)
    {
      printf("***************** No Reminders to Show *****************\n");
      return;
    }
 for (int i=0;i<number_of_reminders;i++)
 {
   printf("\n(%d)\tTitle: %s\n",i,reminders[i].title);
   printf("\tMessage: %s\n",reminders[i].message);
   printf("\tDate: %d/%d/%d at %d:%d\n",reminders[i].time_date,reminders[i].time_month,reminders[i].time_year,reminders[i].time_hr,reminders[i].time_min);
   printf("\tAudio file: %s\n",reminders[i].file);
 }
 printf("\n\n***************** Thats all Reminders *****************\n");
}
//delete a reminder
void delete_reminder(int i)
{
  if(i<number_of_reminders){
    printf("\n***************** Deleting Reminder number: %d ****************\n",i);
    print_reminder(i);
    printf("***************** Is deleted *********************\n\n");
    for(int j = i;j<number_of_reminders-1;j++)
      {
        //can be copied with memcpy() also .. but to make it simple to understand.
        strcpy(reminders[j].title, reminders[j+1].title);
        strcpy(reminders[j].message, reminders[j+1].message);
        reminders[j].time_hr = reminders[j+1].time_hr;
        reminders[j].time_min = reminders[j+1].time_min;
        reminders[j].time_date = reminders[j+1].time_date;
        reminders[j].time_month = reminders[j+1].time_month;
        reminders[j].time_year = reminders[j+1].time_year;
        strcpy(reminders[j].file, reminders[j+1].file);
      }
    number_of_reminders--;
  printf("***************** Total Reminders are : %d *****************\n",number_of_reminders);
  save_data(reminders);
  }
}


#endif
