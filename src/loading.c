/**
 * @file 	loading.c
 * @date 	24 Mar 2018
 * @brief	Ficheiro contendo funções utilizadas na gestão do carregamento do dump para memória.
 */
#include <loading.h>

<<<<<<< HEAD
=======
/*
	Aqui vai ficar definida as funções que carregam
	dos ficheiros do dump a informação para a nossa estrutura
	de dados, e etc.
	Funções neste ficheiro (ver tipagem de argumentos no interface.h):
		-> TAD_community init();
		-> TAD_community load();#include "gmodule.h"
		-> TAD_community clean();




	defines para os file paths dos ficheiros do dump

#define				F_USERS
#define				F_POSTS

*/

//isto tá aqui para nao dar erros.
//substituir quando criar as funções
//made by 54
void 	postSetId				(MYPOST post, long l){};
void 	postSetPostTypeId		(MYPOST post, int n){};
void 	postSetParentId			(MYPOST post, long l){};
void 	postSetCreationDate		(MYPOST post, Date d){};
void 	postSetScore			(MYPOST post, int n){};
void 	postSetOwnerUserId		(MYPOST post, long l){};
void 	postSetOwnerDisplayName	(MYPOST post, char * str){};
void 	postSetTitle			(MYPOST post, char * str){};
void 	postSetTags				(MYPOST post, char ** strs){};
void 	postSetAnswerCount		(MYPOST post, int n){};
void 	postSetCommentCount		(MYPOST post, int n){};
void 	postSetFavoriteCount	(MYPOST post, int n){};
int 	xmlToInt				(xmlAttrPtr cur, xmlDocPtr doc){return 0;}
long 	xmlToLong				(xmlAttrPtr cur, xmlDocPtr doc){return 0;}
MYDATE 	xmlToMyDate				(xmlAttrPtr cur, xmlDocPtr doc){return NULL;}
char * 	xmlToString				(xmlAttrPtr cur, xmlDocPtr doc){return NULL;}
char ** xmlToStringArray		(xmlAttrPtr cur, xmlDocPtr doc){return NULL;};

>>>>>>> d79d180900734dcf25e34f75d5b9385a5de75820


/**
 * @date 			24 Mar 2018
 * @brief 			Função que (recorrendo à biblioteca libxml2) efetua o parsing de um ficheiro xml.
 * @param doc		O apontador do ficheiro xml.
 * @param ptr 		O apontador da estrutura resultante do parsing do ficheiro xml.
 * @param filepath 	O filepath do ficheiro xml a ser lido e carregado.
 */
int xml_file_to_struct(xmlDocPtr * doc, xmlNodePtr * ptr, char * filepath) {

	*doc = xmlParseFile(filepath);

	if (!(*doc)) {
		fprintf(stderr, "Document %s not parsed successfully\n", filepath);
		return -1;
	}

	*ptr = xmlDocGetRootElement(*doc);

	if (!(*ptr)) {
		fprintf(stderr, "%s is an empty document\n", filepath);
		return -2;
	}

	return 1;
}

/**
 * @date 			29 Mar 2018
 * @brief 			Função que cria as àrvores balanceadas de posts segundo id e data de criação.
 * @param path		O ficheiro Posts.xml.
 * @param tree_id 	O apontador onde ficará apontada a àrvore ordenada segundo id's.
 * @param tree_date	O apontador onde ficará apontada a àrvore ordenada segundo datas de criação.
 */
int createMYPOST_TREES(char * path, TREE * tree_id, TREE * tree_date) {
	xmlDocPtr 	doc;
	xmlNodePtr	cur = NULL;

	if( !xml_file_to_struct(&doc, &cur, path)) {							//Load para a estrutura do libxml2 a partir do ficheiro.
		fprintf(stderr, "Could not create user tree from %s\n", path);
		return -1;
	}

	MYPOST	post;
	long * 	keyid;
	MYDATE 	keydate = NULL;
	TREE 	treeid 		= createTREE(&compare_user, &freeKey, &freepost);
	TREE	treedate	= createTREE(&compare_MYDATE_AVL, &free_MYdate, &freepost);

	for(cur = cur->children; cur; cur = cur->next) {						// Percorre os posts todos.
		if(strcmp("row", (char *) cur->name) == 0) {
			post 	= createpost();											//Cria um nodo post.
			xmltoMYPOST(post, cur, doc);									//Preenche essa struct post.

			keyid 	= malloc(sizeof(long));
			getIdP(post, keyid);
			getDateP(post, keydate);

			insere_tree(treeid, keyid, post);								//Insere este nodo na árvore ordenada por id's.
			insere_tree(treedate, keydate, post);							//Insere este nodo na árvore ordenada cronológicamente.
		}
	}

	*tree_id 	= treeid;
	*tree_date 	= treedate;

	xmlFreeDoc(doc);
	xmlCleanupParser();

	return 1;
}



/**
 * @date 			29 Mar 2018
 * @brief 			Função que processa a string correspondente ao valor Creation date e a transforma numa struct mydate.
 * @param value		A string com o valor CreationDate.
 */
MYDATE xmlToMYDATE(char * value) {
	int yy, mm, dd;
	sscanf(value, "%d-%d-%dT", &yy, &mm ,&dd);

	MYDATE date = createMYDate(dd, mm, yy);

	return date;
}


/**
 * @date 			29 Mar 2018
 * @brief 			Função que processa a string correspondente ao valor Tags a transforma num array de strings.
 * @param value		A string com o valor Tags.
 */
char ** xmlToStringArray(char * value) {
	/*
	int i, n = strlen(value);
	int tag_counter;

	for(i = 0; i < n; i++)								//Conta o número de tags
		if(value[i] == '<')
			tag_counter++;

	if(tag_counter == 0)								//Retorna NULL se não há tags
		return NULL;

	char ** arr = malloc(tag_counter*sizeof(char *));	//Aloca memória para o numero de apontadores necessários para as tags.

	for(i = 0; i < tag_counter; i++)

	return arr;
	*/
	return NULL;
}




/**
 * @date 			25 Mar 2018
 * @brief 			Função que copia informação de um nodo da estrutura do libxml2 para o análogo da nossa estrutura.
 * @param post		O apontador da nossa estrutura.
 * @param xml 		O apontador da estrutura resultante do parsing do ficheiro xml.
 */
void xmltoMYPOST(MYPOST post, xmlNodePtr xml, xmlDocPtr doc) {
	xmlAttrPtr cur;

	char flag[12] = {0};	//flag para não estar constantemente a chamar a strcmp()
	char * value;

	for(cur = xml->properties; cur; cur = cur->next) {
				value = (char *) xmlNodeListGetString(doc, cur->children, 1);

				if(!flag[0] && strcmp((char *) cur->name, "Id") == 0) {
					setIdP(post, atol(value));
					flag[0] = 1;
					continue;
				}

				if(!flag[1] && strcmp((char *) cur->name, "PostTypeId") == 0) {
					setPostTypeIdP(post, atoi(value));
					flag[1] = 1;
					continue;
				}

				if(!flag[2] && strcmp((char *) cur->name, "ParentId") == 0) {
					setPIdP(post, atol(value));
					flag[2] = 1;
					continue;
				}

<<<<<<< HEAD
				if(!flag[3] && strcmp((char *) cur->name, "CreationDate") == 0) {
					setDateP(post, xmlToMYDATE(value));
					flag[3] = 1;
=======
				if(!flag[3] && xmlStrcmp(cur->name, (xmlChar *) "CreationDate") == 0) {
					setDateP(post, xmlToMyDate(cur, doc));
					flag[0] = 1;
>>>>>>> d79d180900734dcf25e34f75d5b9385a5de75820
					continue;
				}

				if(!flag[4] && strcmp((char *) cur->name, "Score") == 0) {
					setScoreP(post, atoi(value));
					flag[4] = 1;
					continue;
				}

				if(!flag[5] && strcmp((char *) cur->name, "OwnerUserId") == 0) {
					setOwnerIdP(post, atol(value));
					flag[5] = 1;
					continue;
				}

				if(!flag[6] && strcmp((char *) cur->name, "OwnerDisplayName") == 0) {
					setOwnerNameP(post, value);
					flag[6] = 1;
					continue;
				}

				if(!flag[7] && strcmp((char *) cur->name, "Title") == 0) {
					setTitleP(post, value);
					flag[7] = 1;
					continue;
				}

				if(!flag[8] && strcmp((char *) cur->name, "Tags") == 0) {
					setTagsP(post, xmlToStringArray(value));
					flag[8] = 1;
					continue;
				}

				if(!flag[9] && strcmp((char *) cur->name, "AnswerCount") == 0) {
					setAsnwersP(post, atoi(value));
					flag[9] = 1;
					continue;
				}

				if(!flag[10] && strcmp((char *) cur->name, "CommentCount") == 0) {
					setCommentsP(post, atoi(value));
					flag[10] = 1;
					continue;
				}

				if(!flag[11] && strcmp((char *) cur->name, "FavoriteCount") == 0) {
					setFavsP(post, atoi(value));
					flag[11] = 1;
					continue;
				}

<<<<<<< HEAD
				free(value);
=======
   //falta inserir votos
>>>>>>> d79d180900734dcf25e34f75d5b9385a5de75820

	}

}
