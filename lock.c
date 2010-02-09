#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include "lock.h"

int write_lock_file(char *file_name)
{
  FILE *fp = fopen(file_name, "w");
  if (fp != NULL)
  {
    fprintf(fp, "%d", (int)getpid());
    fclose(fp);
    return 0;
  }
  else
    return -1;
}


int is_locked(char *file_name)
{
  FILE *fp = fopen(file_name, "r");
  if (fp != NULL)
  {
    int pid;
    fscanf(fp, "%d", &pid);
    fclose(fp);
    return pid != getpid();
  }
  else
    return 0;
}

int unlock_file(char *file_name)
{
  return remove(file_name);
}

void lock_file(char *file_name)
{
  while (is_locked(file_name))
    sleep(1);
  write_lock_file(file_name);      
}
