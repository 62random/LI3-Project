#ifndef __LOADING__
#define __LOADING__

#include <mypost.h>
#include <myuser.h>
#include <mydate.h>
#include "/usr/include/libxml2/libxml/parser.h"
#include "/usr/include/libxml2/libxml/xmlwriter.h"
#include "/usr/include/libxml2/libxml/tree.h"
#include "/usr/include/libxml2/libxml/xmlmemory.h"


//Estes protótipos são temporários, apenas para que os ficheiros compilem
//alguns destes protótipos são de funções que já existem, porém pus um nome
//diferente para se saber do que estamos a falar

int 	xml_file_to_struct		(xmlDocPtr * doc, xmlNodePtr * ptr, char * filepath);
int 	createMYPOST_TREES		(char * path, TREE * tree_id, TREE * tree_date, TREE treeusers);
MYDATE 	xmlToMYDATE				(char * value);
char ** xmlToStringArray		(char * value);
void 	xmltoMYPOST				(MYPOST post, xmlNodePtr xml, xmlDocPtr doc, TREE treeid, TREE treeusers);

#endif
