#ifndef TOYBOX_H
#define TOYBOX_H

char* home();
char* get_dir(const char* HOME, const char* DIR_NAME);
char* get_file(char* ROOT, char* FILE_NAME);

#endif
