#ifndef __MYUSER_H__
#define __MYUSER_H__

#include <glib.h>
#include "common.h"
#include <string.h>
#include <stdlib.h>
#include "loading.h"

typedef struct myuser * MYUSER;

long getIdMYUSER(MYUSER use);

int getREPMYUSER(MYUSER use);

char * getUsername(MYUSER use);

char * getBiography(MYUSER use);

MYUSER createMYUSER();

void freeMYUSER(void * aux);

int compare_user(const void * key1, const void * key2,void * data);

void freeKey(void * a);

MYUSER search_USER(GTree * tree,long id);

GTree * createTREE(const char * path);

#endif
