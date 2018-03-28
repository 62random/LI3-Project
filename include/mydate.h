#ifndef __MYDATE_H__
#define __MYDATE_H__

#include <stdlib.h>

typedef struct mydate * MYDATE;

MYDATE createMYDate(int day, int month, int year);
int get_MYday(MYDATE d);
int get_MYmonth(MYDATE d);
int get_MYyear(MYDATE d);
void free_MYdate(MYDATE d);
int MYdate_size();
int compare_MYDATE(void * data1, void * data2);

#endif
