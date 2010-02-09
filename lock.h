#ifndef LOCK_H
#define LOCK_H

int write_lock_file(char *file_name);

int is_locked(char *file_name);

int unlock_file(char *file_name);

void lock_file(char *file_name);

#endif
