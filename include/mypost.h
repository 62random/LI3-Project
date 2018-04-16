#ifndef __MYPOST_H__
#define __MYPOST_H__

#include "mydate.h"
#include "mytree.h"
#include "mylist.h"
#include <glib.h>




typedef struct mypost * MYPOST;

void 	getIdP					(MYPOST post, long * id);
void 	setIdP					(MYPOST post, long  id);
void 	getPostTypeIdP			(MYPOST post, int * id);
void 	setPostTypeIdP			(MYPOST post, long  id);
void 	getOwnerIdP				(MYPOST post, long * id);
void 	setOwnerIdP				(MYPOST post, long  id);
void 	getDateP				(MYPOST post, MYDATE * data);
void 	setDateP				(MYPOST post, MYDATE data);
void 	setIdP					(MYPOST post, long  id);//
void 	getOwnerNameP			(MYPOST post, char ** name);
void 	setOwnerNameP			(MYPOST post, char *  name);
void 	getTitleP				(MYPOST post, char ** title);
void 	setTitleP				(MYPOST post, char * title);
void 	getTagsP				(MYPOST post, char *** tags);
void 	setTagsP				(MYPOST post, char ** tags);
void 	getAnswersP				(MYPOST post, int *answer);
void 	setAsnwersP				(MYPOST post, int answer);
void 	getCommentsP			(MYPOST post, int *comments);
void 	setCommentsP			(MYPOST post, int comments);
void 	getFavsP				(MYPOST post, int *fav);
void 	setFavsP				(MYPOST post, int fav);
void 	getVotesP				(MYPOST post, int *votes);
void 	setVotesP				(MYPOST post, int votes);
void 	sumVotesP				(MYPOST post, int votes);
void 	getPIdP					(MYPOST post, long * p_id);
void 	setPIdP					(MYPOST post, long  id);
void 	setScoreP				(MYPOST post, int  score);
void 	getScoreP				(MYPOST post, int * score);
void 	getFilhosP				(MYPOST post, GArray ** filhos);
MYPOST 	createpost				();
void 	freepost				(MYPOST post);
int 	compare_mypostsAVLDate	(void * data1, void * data2,void * data);
int 	compare_mypostsLISTDate	(void * data1, void * data2);
int 	compare_mypostsAVLID	(void * post1, void * post2,void * data);
void 	setFilhosNoPost			(MYPOST post,void * data);
MYPOST 	search_POSTID			(TREE tree, long id);
MYPOST 	search_POSTDATA			(TREE tree, MYDATE date);
void 	free_StringArray		(char ** arr);
void 	print_posts_MYPOST		(MYPOST post);
int		existeTag				(MYPOST post,char * tag);
#endif
