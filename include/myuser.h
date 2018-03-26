#include <libxml/parser.h>
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <glib.h>
#include <common.h>

typedef struct myuser * MYUSER;

long getIdMYUSER(MYUSER use);

char * getUsername(MYUSER use);

char * getBiography(MYUSER use);

MYUSER createMYUSER();

void freeMYUSER(MYUSER conta);

int compare_user(long * key1, long * key2);

void freeKey(long * a);

void createTREE();
