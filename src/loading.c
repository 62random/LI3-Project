/**
 * @file 	loading.c
 * @date 	24 Mar 2018
 * @brief	Ficheiro contendo funções utilizadas na gestão do carregamento do dump para memória.
 */
#include <loading.h>

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
Date 	xmlToDate				(xmlAttrPtr cur, xmlDocPtr doc){return NULL;}
char * 	xmlToString				(xmlAttrPtr cur, xmlDocPtr doc){return NULL;}
char ** xmlToStringArray		(xmlAttrPtr cur, xmlDocPtr doc){return NULL;};



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
 * @date 			25 Mar 2018
 * @brief 			Função que copia informação de um nodo da estrutura do libxml2 para o análogo da nossa estrutura.
 * @param post		O apontador da nossa estrutura.
 * @param xml 		O apontador da estrutura resultante do parsing do ficheiro xml.
 */
void xmltoMYPOST(MYPOST post, xmlNodePtr xml, xmlDocPtr doc) {
	xmlAttrPtr cur;

	char flag[12] = {0};
	//int i;

	for(cur = xml->properties; cur; cur = cur->next) {

				//temos de definir uma nomenclatura para não haver funções
				//de users e posts com o mesmo nome


		//	for(int i = 0; i < 12; i++) {											//podíamos fazer isto num ciclo for
		//		if(!flag[i] && xmlStrcmp(cur->name, str_matrix[i])) { 			//com dois arrays de apontadores para
		//			fun1_matrix[i](post, fun2_matrix[i](cur));					//as funções correspondentes a cada
		//			flag[i] = 1;												//atritbuto (tb num array de strings)
		//			break;														//teriam de ser static, mas ficava uma
		//		}																//cena bem feita, é ver se compensa
		//	}



				if(!flag[0] && xmlStrcmp(cur->name, (xmlChar *) "Id") == 0) {
					setIdP(post, xmlToLong(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[1] && xmlStrcmp(cur->name, (xmlChar *) "PostTypeId") == 0) {
					setPostTypeIdP(post, xmlToInt(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[2] && xmlStrcmp(cur->name, (xmlChar *) "ParentId") == 0) {
					setPIdP(post, xmlToLong(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[3] && xmlStrcmp(cur->name, (xmlChar *) "CreationDate") == 0) {
					setDateP(post, xmlToDate(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[4] && xmlStrcmp(cur->name, (xmlChar *) "Score") == 0) {
					setScoreP(post, xmlToInt(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[5] && xmlStrcmp(cur->name, (xmlChar *) "OwnerUserId") == 0) {
					setOwnerIdP(post, xmlToLong(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[6] && xmlStrcmp(cur->name, (xmlChar *) "OwnerDisplayName") == 0) {
					setOwnerNameP(post, xmlToString(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[7] && xmlStrcmp(cur->name, (xmlChar *) "Title") == 0) {
					setTitleP(post, xmlToString(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[8] && xmlStrcmp(cur->name, (xmlChar *) "Tags") == 0) {
					setTagsP(post, xmlToStringArray(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[9] && xmlStrcmp(cur->name, (xmlChar *) "AnswerCount") == 0) {
					setAsnwersP(post, xmlToInt(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[10] && xmlStrcmp(cur->name, (xmlChar *) "CommentCount") == 0) {
					setCommentsP(post, xmlToInt(cur, doc));
					flag[0] = 1;
					continue;
				}

				if(!flag[11] && xmlStrcmp(cur->name, (xmlChar *) "FavoriteCount") == 0) {
					setFavsP(post, xmlToInt(cur, doc));
					flag[0] = 1;
					continue;
				}

   //falta inserir votos
 
	}

}
