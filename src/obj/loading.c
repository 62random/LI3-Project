/**
 * @file 	loading.c
 * @date 	24 Mar 2018
 * @brief	Ficheiro contendo funções utilizadas na gestão do carregamento do dump para memória.
 */
#include <stdlib.h>
#include <stdio.h>
#include "/usr/include/libxml2/libxml/parser.h"
#include "/usr/include/libxml2/libxml/xmlwriter.h"
#include "/usr/include/libxml2/libxml/tree.h"
#include "/usr/include/libxml2/libxml/xmlmemory.h"


/*
	Aqui vai ficar definida as funções que carregam
	dos ficheiros do dump a informação para a nossa estrutura
	de dados, e etc.
	Funções neste ficheiro (ver tipagem de argumentos no interface.h):
		-> TAD_community init();
		-> TAD_community load();#include "gmodule.h"
		-> TAD_community clean();


/*

	defines para os file paths dos ficheiros do dump

#define				F_USERS
#define				F_POSTS
*/


/**
 * @date 			24 Mar 2018
 * @brief 			Função que (recorrendo à biblioteca libxml2) efetua o parsing de um ficheiro xml.
 * @param doc		O apontador do ficheiro xml.
 * @param ptr 		O apontador da estrutura resultante do parsing do ficheiro xml.
 * @param filepath 	O filepath do ficheiro xml a ser lido e carregado.
 */
void xml_file_to_struct(xmlDocPtr * doc, xmlNodePtr * ptr, char * filepath) {

	*doc = xmlParseFile(filepath);

	if (!(*doc)) {
		fprintf(stderr, "Document %s not parsed successfully\n", filepath);
		return -1;
	}

	*ptr = xmlDocGetRootElement(doc);

	if (!(*ptr)) {
		fprintf(stderr, "%s is an empty document\n", filepath);
		return -2;
	}

	return 1;
}
