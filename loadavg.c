#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include "config.h"
#include "loadavg.h"
#include "lock.h"

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

int main()
{
  while (1)
  {
    write_log();
    sleep(SLEEP_TIME);
  }
  return 0;
}
