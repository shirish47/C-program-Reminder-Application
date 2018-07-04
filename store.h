#ifndef STORE_H
#define STORE_H
#include <stdio.h>
#include "common.h"

#define FILE_NAME "reminders.csv"

void load_data(reminder_t reminders[])
{
  FILE *fp;
  fp =  fopen(FILE_NAME,"r");
  if (fp == NULL){
      printf("Could not open file %s",FILE_NAME);
      return ;
  }
  char str[250] ;//="0,hello,hi this is me,11,12,11,11,1102,test.wav";
  int i = 0;

  char *p;
  //get id
  //printf("loding data %s\n",str);
  while(fgets(str,250,fp)!=NULL)
  {

    p=strtok(str,",");
    i=atoi(p);

    if(p!=NULL)
    {
      p=strtok(NULL,",");
      strcpy(reminders[i].title,p);
      //printf("%s\n",p);
    }
    if(p!=NULL)
    {
      p=strtok(NULL,",");
      strcpy(reminders[i].message,p);
      //printf("%s\n",p);
    }
    if(p!=NULL)
    {
      p=strtok(NULL,",");
      reminders[i].time_hr= atoi(p);
      //printf("%s\n",p);
    }
    if(p!=NULL)
    {
      p=strtok(NULL,",");
      reminders[i].time_min= atoi(p);
      //printf("%s\n",p);
    }
    if(p!=NULL)
    {
      p=strtok(NULL,",");
      reminders[i].time_date= atoi(p);
      //printf("%s\n",p);
    }
    if(p!=NULL)
    {
      p=strtok(NULL,",");
      reminders[i].time_month= atoi(p);
      //printf("%s\n",p);
    }
    if(p!=NULL)
    {
      p=strtok(NULL,",");
      reminders[i].time_year= atoi(p);
      //printf("%s\n",p);
    }
    if(p!=NULL)
    {
      p=strtok(NULL,",");
      strcpy(reminders[i].file,p);
      //printf("%s\n",p);
    }
    reminders[i].finished= false;
    number_of_reminders++;
    //print_reminder(i);
  }
  fclose(fp);
}

void save_data(reminder_t reminders[])
{
  char buffer[250];
  FILE *fp;
  fp =  fopen(FILE_NAME,"w");


  for(int i=0;i<number_of_reminders;i++)
  {
    sprintf(buffer,"%d,%s,%s,%d,%d,%d,%d,%d,%s", i, reminders[i].title, reminders[i].message, reminders[i].time_hr, reminders[i].time_min, reminders[i].time_date, reminders[i].time_month, reminders[i].time_year, reminders[i].file);
    //printf("String string to file is : %s\n",buffer);
    fprintf(fp,"%s\n",buffer);
  }
fclose(fp);
}
#endif
