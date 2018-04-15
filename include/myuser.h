#ifndef __MYUSER_H__
#define __MYUSER_H__

#include <glib.h>
#include "common.h"
#include <string.h>
#include <stdlib.h>
#include "mylist.h"
#include "mydate.h"
#include "mytree.h"
#include "loading.h"

typedef struct myuser * MYUSER;

long 		getIdMYUSER			(MYUSER use);
int 		getREPMYUSER		(MYUSER use);
char * 		getUsername			(MYUSER use);
char * 		getBiography		(MYUSER use);
GArray *	getMYLISTuser		(MYUSER use); //rever encapl
long * 		getNposts			(MYUSER use,int n,int * n_elem);
void 		print_post_MYUSER	(MYUSER use);
MYUSER 		createMYUSER		();
void 		freeMYUSER			(void * aux);
int 		compare_user		(void * key1,void * key2);
void 		freeKey				(void * a);
void 		freeTreeUSER		(TREE tree);
MYUSER 		search_USER			(TREE tree,long id);
int 		setPostToUSER		(TREE tree,long id,void * data);
long		getNUM_POST_MYUSER	(MYUSER use);
TREE 		createMYUSERS_TREE	(char * path);
#endif
