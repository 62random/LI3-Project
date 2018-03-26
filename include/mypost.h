#include <string.h>
#include <stdlib.h>
#include "date.h"


typedef struct mypost * MYPOST;

void getId(MYPOST post, long * id);
void setId(MYPOST post, long  id);
void getPostTypeId(MYPOST post, int * id);
void setPostTypeId(MYPOST post, int  id);
void getPId(MYPOST post, long * p_id);
void getDate(MYPOST post, Date data);
void getOwnerId(MYPOST post, long * id);
void getOwnerName(MYPOST post, char * name);
void getTitle(MYPOST post,char* title);
void getTags(MYPOST post,char** tags);
void getAnswer(MYPOST post,int *answer);
void getComments(MYPOST post,int *comments);
void getFavs(MYPOST post,int *fav);
void getVotes(MYPOST post,int *votes);
MYPOST createpost();
void freepost(MYPOST post);
