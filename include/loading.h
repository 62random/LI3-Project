#include <stdlib.h>
#include <stdio.h>
#include "/usr/include/libxml2/libxml/parser.h"
#include "/usr/include/libxml2/libxml/xmlwriter.h"
#include "/usr/include/libxml2/libxml/tree.h"
#include "/usr/include/libxml2/libxml/xmlmemory.h"
#include <mypost.h>
#include <myuser.h>



//Estes protótipos são temporários, apenas para que os ficheiros compilem
//alguns destes protótipos são de funções que já existem, porém pus um nome
//diferente para se saber do que estamos a falar

int 	xml_file_to_struct		(xmlDocPtr * doc, xmlNodePtr * ptr, char * filepath);
long 	xmlToLong				(xmlAttrPtr cur, xmlDocPtr doc);
void 	xmltoMYPOST				(MYPOST post, xmlNodePtr xml, xmlDocPtr doc);
void 	postSetId				(MYPOST post, long l);
void 	postSetPostTypeId		(MYPOST post, int n);
void 	postSetParentId			(MYPOST post, long l);
void 	postSetCreationDate		(MYPOST post, Date d);
void 	postSetScore			(MYPOST post, int n);
void 	postSetOwnerUserId		(MYPOST post, long l);
void 	postSetOwnerDisplayName	(MYPOST post, char * str);
void 	postSetTitle			(MYPOST post, char * str);
void 	postSetTags				(MYPOST post, char ** strs);
void 	postSetAnswerCount		(MYPOST post, int n);
void 	postSetCommentCount		(MYPOST post, int n);
void 	postSetFavoriteCount	(MYPOST post, int n);
int 	xmlToInt				(xmlAttrPtr cur, xmlDocPtr doc);
Date 	xmlToDate				(xmlAttrPtr cur, xmlDocPtr doc);
char * 	xmlToString				(xmlAttrPtr cur, xmlDocPtr doc);
char ** xmlToStringArray		(xmlAttrPtr cur, xmlDocPtr doc);
