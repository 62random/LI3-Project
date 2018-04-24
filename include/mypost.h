#ifndef __MYPOST_H__
#define __MYPOST_H__

#include "mydate.h"
#include "mytree.h"
#include "/usr/include/libxml2/libxml/parser.h"
#include "/usr/include/libxml2/libxml/xmlwriter.h"
#include "/usr/include/libxml2/libxml/tree.h"
#include "/usr/include/libxml2/libxml/xmlmemory.h"
#include <stdlib.h>




typedef struct mypost * MYPOST;

typedef struct stackpost * STACKPOST;

//Stackpost
void 		trans_arr				(STACKPOST arr, void (*f_box)(void *, void *, void *, void *), void * data1, void * data2, void * data3);
int 		ordenaPOST_MYUSER		(const void * data1, const void * data2);
void 		order_STACKPOST			(STACKPOST st, void * func);
STACKPOST	initSTACKPOST			(long size);
void		insereSTACKPOST			(STACKPOST st, MYPOST post);
void 		incCounter2_STACKPOST	(STACKPOST st,long i);
void 		incCounter1_STACKPOST	(STACKPOST st,long i);
long 		getCounter1_STACKPOST	(STACKPOST st);
long 		getCounter2_STACKPOST	(STACKPOST st);
long		get_NUM_eleSTACKPOST	(STACKPOST st);
MYPOST 		get_ele_index_STACKPOST	(STACKPOST st, long i);
void 		freeSTACKPOST_SEM_CLONE	(STACKPOST st);
void 		freeSTACKPOST_COM_CLONE	(STACKPOST st);

void 		getIdP					(MYPOST post, long * id);
void 		getPostTypeIdP			(MYPOST post, int * id);
int 		getTYPECLONEP			(MYPOST post);
void 		getOwnerIdP				(MYPOST post, long * id);
void 		getDateP				(MYPOST post, MYDATE * data);
void 		getOwnerNameP			(MYPOST post, char ** name);
void 		getTitleP				(MYPOST post, char ** title);
void 		getTagsP				(MYPOST post, char *** tags); // tem codigo a comm
void 		getAnswersP				(MYPOST post, int *answer);
void 		getCommentsP			(MYPOST post, int *comments);
void 		getFavsP				(MYPOST post, int *fav);
void 		getPIdP					(MYPOST post, long * p_id);
void 		getScoreP				(MYPOST post, int * score);
void 		getFilhosP				(MYPOST post, STACKPOST * filhos);
void 		setFilhosNoPost			(MYPOST post,MYPOST data);

MYPOST 		createpost				(int type);
void 		freepost				(MYPOST post);
void 		free_StringArray		(char ** arr);


STACKPOST 	clone_STACKPOST			(STACKPOST st);
MYPOST 		clone_MYPOST_DEEP		(MYPOST post);
MYPOST 		search_POSTID			(TREE tree, long id);
void 		print_posts_MYPOST		(MYPOST post);
int			existeTag				(MYPOST post,char * tag); // tem printf
//XML
void 		xmltoMYPOST				(MYPOST post, xmlNodePtr xml, xmlDocPtr doc, TREE treeid, TREE treeusers);
MYDATE 		xmlToMYDATE				(char * value);
char ** 	xmlToStringArray		(char * value);
STACKPOST 	search_POSTDATA			(TREE tree,MYDATE data);
void 		trans_arr				(STACKPOST arr, void (*f_box)(void *, void *, void *, void *), void * data1, void * data2, void * data3);
#endif
