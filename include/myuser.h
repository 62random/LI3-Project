#include "/usr/include/libxml2/libxml/parser.h"
#include "/usr/include/libxml2/libxml/xmlwriter.h"
#include "/usr/include/libxml2/libxml/tree.h"
#include "/usr/include/libxml2/libxml/xmlmemory.h"
#include <glib.h>
#include <common.h>

typedef struct myuser * MYUSER;

long getId(MYUSER use);

char * getUsername(MYUSER use);

char * getBiography(MYUSER use);

MYUSER createMYUSER();

void freeMYUSER(MYUSER conta);

int compare_user(long * key1, long * key2);

void freeKey(long * a);

void createTREE();
