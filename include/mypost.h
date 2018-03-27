#include <string.h>
#include <stdlib.h>
#include "date.h"


typedef struct mypost * MYPOST;

void getIdP(MYPOST post, long * id);
void setIdP(MYPOST post, long  id);
void getPostTypeIdP(MYPOST post, int * id);
void setPostTypeIdP(MYPOST post, long  id);
void getOwnerIdP(MYPOST post, long * id);
void setOwnerIdP(MYPOST post, long  id);
void getDateP(MYPOST post, Date data);
void setDateP(MYPOST post, Date data);
void getOwnerIdP(MYPOST post, long * id);
void setIdP(MYPOST post, long  id);
void getOwnerNameP(MYPOST post, char * name);
void setOwnerNameP(MYPOST post, char *  name);
void getTitleP(MYPOST post,char* title);
void setTitleP(MYPOST post, char* title);
void getTagsP(MYPOST post,char** tags);
void setTagsP(MYPOST post, char* tags);
void getAnswersP(MYPOST post,int *answer);
void setAsnwersP(MYPOST post, int answer);
void getCommentsP(MYPOST post,int *comments);
void setCommentsP(MYPOST post, int comments);
void getFavsP(MYPOST post,int *fav);
void setFavsP(MYPOST post, int fav);
void getVotesP(MYPOST post,int *votes);
void setVotesP(MYPOST post, int votes);
MYPOST createpost();
void freepost(MYPOST post);
