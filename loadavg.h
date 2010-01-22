#ifndef LOADAVG_H
#define LOADAVG_H

int write_log();

int write_log_entry(long int time, double loadavg);

int write_lock_file(char *file_name);

int is_locked(char *file_name);

int unlock_file(char *file_name);

void lock_file(char *file_name);

#endif
