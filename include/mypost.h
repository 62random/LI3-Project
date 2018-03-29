#ifndef __MYPOST_H__
#define __MYPOST_H__

#include <string.h>
#include <stdlib.h>
#include "date.h"
#include "mydate.h"



typedef struct mypost * MYPOST;

void getIdP(MYPOST post, long * id);
void setIdP(MYPOST post, long  id);
void getPostTypeIdP(MYPOST post, int * id);
void setPostTypeIdP(MYPOST post, long  id);
void getOwnerIdP(MYPOST post, long * id);
void setOwnerIdP(MYPOST post, long  id);
void getDateP(MYPOST post, MYDATE data);
void setDateP(MYPOST post, MYDATE data);
void getOwnerIdP(MYPOST post, long * id);
void setIdP(MYPOST post, long  id);
void getOwnerNameP(MYPOST post, char * name);
void setOwnerNameP(MYPOST post, char *  name);
void getTitleP(MYPOST post,char* title);
void setTitleP(MYPOST post, char* title);
void getTagsP(MYPOST post,char** tags);
void setTagsP(MYPOST post, char** tags);
void getAnswersP(MYPOST post,int *answer);
void setAsnwersP(MYPOST post, int answer);
void getCommentsP(MYPOST post,int *comments);
void setCommentsP(MYPOST post, int comments);
void getFavsP(MYPOST post,int *fav);
void setFavsP(MYPOST post, int fav);
void getVotesP(MYPOST post,int *votes);
void setVotesP(MYPOST post, int votes);
void getPIdP(MYPOST post, long * p_id);
void setPIdP(MYPOST post, long  id);
void setScoreP(MYPOST post, int  score);
void getScoreP(MYPOST post, int * score);
MYPOST createpost();
void freepost(MYPOST post);
<<<<<<< HEAD
int compare_mypostsAVL(void * data1, void * data2,void * data);
int compare_mypostsLIST(void * data1, void * data2);
void freeKeyId(void * a);
void freeKeyDate(void * a);
=======
int compare_mypostsAVLDate(void * data1, void * data2,void * data);
int compare_mypostsLISTDate(void * data1, void * data2);
int compare_mypostsAVLID(void * post1, void * post2,void * data);

>>>>>>> d79d180900734dcf25e34f75d5b9385a5de75820
#endif
