#include <stdlib.h>
#include <stdio.h>
#include "/usr/include/libxml2/libxml/parser.h"
#include "/usr/include/libxml2/libxml/xmlwriter.h"
#include "/usr/include/libxml2/libxml/tree.h"
#include "/usr/include/libxml2/libxml/xmlmemory.h"






void xml_file_to_struct(xmlDocPtr * doc, xmlNodePtr * ptr, char * filepath);
