#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include "config.h"
#include "loadavg.h"

int write_log()
{
  double loadavg [3];
  if (getloadavg(loadavg, 3) == -1)
    return -1;
  
  return write_log_entry(time(NULL), loadavg[0]);
}

int write_log_entry(long int time, double loadavg)
{
  lock_file(OUT_FILE_LOCK);
  FILE * fp = fopen(OUT_FILE_NAME, "a");
  if (fp == NULL)
  {
    unlock_file(OUT_FILE_LOCK);
    return -1;
  }
  fprintf(fp, "%ld %.2f\n",
	  time, loadavg);
  fclose(fp);
  unlock_file(OUT_FILE_LOCK);
  return 0;
}

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

int main()
{
  while (1)
  {
    write_log();
    sleep(SLEEP_TIME);
  }
  return 0;
}
