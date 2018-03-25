#include <stdlib.h>
#include <stdio.h>
#include "/usr/include/libxml2/libxml/parser.h"
#include "/usr/include/libxml2/libxml/xmlwriter.h"
#include "/usr/include/libxml2/libxml/tree.h"
#include "/usr/include/libxml2/libxml/xmlmemory.h"
#include <mypost.h>
#include <myuser.h>



int xml_file_to_struct(xmlDocPtr * doc, xmlNodePtr * ptr, char * filepath);
