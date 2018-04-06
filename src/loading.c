/**
 * @file 	loading.c
 * @date 	24 Mar 2018
 * @brief	Ficheiro contendo funções utilizadas na gestão do carregamento do dump para memória.
 */
#include <loading.h>



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
 * @param treeusers A árvore de users.
 */
int createMYPOST_TREES(char * path, TREE * tree_id, TREE * tree_date, TREE treeusers) {
	xmlDocPtr 	doc;
	xmlNodePtr	cur = NULL;

	if( !xml_file_to_struct(&doc, &cur, path)) {							//Load para a estrutura do libxml2 a partir do ficheiro.
		fprintf(stderr, "Could not create user tree from %s\n", path);
		return -1;
	}

	MYPOST	post;
	long * 	keyid;
	MYDATE 	keydate = NULL;
	TREE 	treeid 		= createTREE(&compare_user, &freeKey, &freepost,NULL);
	TREE	treedate	= createTREE(&compare_MYDATE_AVL, &free_MYdate, NULL,NULL);

	for(cur = cur->children; cur; cur = cur->next) {						// Percorre os posts todos.
		if(strcmp("row", (char *) cur->name) == 0) {
			post 	= createpost();											//Cria um nodo post.
			xmltoMYPOST(post, cur, doc, treeid, treeusers);					//Preenche essa struct post.

			keyid 	= malloc(sizeof(long));
			getIdP(post, keyid);
			getDateP(post, &keydate);

			insere_tree(treeid, keyid, post);								//Insere este nodo na árvore ordenada por id's.
			insere_tree(treedate, keydate, post);							//Insere este nodo na árvore ordenada cronológicamente.
		}
	}

	*tree_id 	= treeid;
	*tree_date 	= treedate;

	xmlFreeDoc(doc);
	xmlFreeNode(cur);
	xmlCleanupParser();

	return 1;
}



/**
 * @date 			31 Mar 2018
 * @brief 			Função que processa a informação necessária relativa aos votes.
 * @param path		O ficheiro Votes.xml.
 * @param tree_id 	A árvore ordenada segundo id's.
 */
int xmlVotes(char * path, TREE treeid) {
	xmlDocPtr 	doc;
	xmlNodePtr	cur = NULL;

	if( !xml_file_to_struct(&doc, &cur, path)) {							//Load para a estrutura do libxml2 a partir do ficheiro.
		fprintf(stderr, "Could process votes from %s\n", path);
		return -1;
	}

	for(cur = cur->children; cur; cur = cur->next)  						// Percorre os votes todos.
		if(strcmp("row", (char *) cur->name) == 0)
			xmlVoteToPost(cur, doc, treeid);

	xmlFreeDoc(doc);
	xmlFreeNode(cur);
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

	int i, n = strlen(value);
	int tag_counter = 0;

	for(i = 0; i < n; i++)									//Conta o número de tags
		if(value[i] == '<')
			tag_counter++;

	if(tag_counter == 0)									//Retorna NULL se não há tags
		return NULL;

	char ** arr = malloc((tag_counter + 1)*sizeof(char *));	//Aloca memória para o numero de apontadores necessários para as tags.

	int j = 0, k = 0;
	int starts[tag_counter];
	char format[10];

	for(i = 0; i < n; i++) {								//Percrre a string value que contém as tags
		if(value[i] == '<') {								//Se for  início de outra tag, dá reset ao contador de tamanho
			j = 0;											//regista o início desta tag
			starts[k] = i + 1;
		}
		else if (value[i] == '>') {							//Se for o fim de uma tag
			arr[k] = malloc((sizeof(char) + 1)*j);			//Aloca a memória necessária para a mesma
			sprintf(format, "%%%ds", j);					//Regista o formato auxiliar ao sscanf
			sscanf(&value[starts[k]], format, arr[k]);		//Copia a tag para a string do array
			arr[k][j] = '\0';								//Sinaliza o final da string de cada tag com EOF.
			k++;											//Incrementa o índice do array de strings
		}
		else
			j++;											//Incrementa o registo do tamanho da tag atual
	}

	arr[k] = NULL;											//O último apontador deste array aponta para NULL

	return arr;
}



/**
 * @date 			31 Mar 2018
 * @brief 			Função que modifica a informação de um post para registar um vote.
 * @param ptr 		O apontador da estrutura resultante do parsing do ficheiro xml.
 * @param doc		O apontador para o documento xml. (libxml2)
 * @param treeid	O apontador para a àrvore de posts ordenada por id.
 */
void xmlVoteToPost(xmlNodePtr ptr, xmlDocPtr doc, TREE treeid){
	xmlAttrPtr cur;

	char * value;
	int type = 0;
	long postid = 0;
	char flag_id = 0, flag_type = 0;

	for(cur = ptr->properties; (!flag_id || !flag_type) && cur; cur = cur->next) {
		value = (char *) xmlNodeListGetString(doc, cur->children, 1);

		if((!flag_id) && strcmp((char *) cur->name, "PostId") == 0) {
			postid = atol(value);
			flag_id = 1;
			free(value);
			continue;
		}

		if((!flag_type) && strcmp((char *) cur->name, "VoteTypeId") == 0) {
			type = atoi(value);
			flag_type = 1;
			free(value);
			continue;
		}

		free(value);
	}

	MYPOST post = NULL;
	post = search_POSTID(treeid, postid);


	if(post) {
		if(type == 2)
			sumVotesP(post, 1);
		else if(type == 3)
			sumVotesP(post, -1);
	}

}

/**
 * @date 			25 Mar 2018
 * @brief 			Função que copia informação de um nodo da estrutura do libxml2 para o análogo da nossa estrutura.
 * @param post		O apontador da nossa estrutura.
 * @param xml 		O apontador da estrutura resultante do parsing do ficheiro xml.
 * @param doc		O apontador para o documento xml. (libxml2)
 * @param treeid	O apontador para a àrvore de posts ordenada por id.
 * @param treeusers O apontador para a árvore de users.
 */
void xmltoMYPOST(MYPOST post, xmlNodePtr xml, xmlDocPtr doc, TREE treeid, TREE treeusers) {
	xmlAttrPtr cur;

	char flag[12] = {0};	//flags para não estar constantemente a chamar a strcmp()
	char * value;
	char ** arr;
	MYDATE date;
	MYPOST parent = NULL;
	long l;
	int n = 0;

	for(cur = xml->properties; cur; cur = cur->next) {
				value = (char *) xmlNodeListGetString(doc, cur->children, 1);

				if(!flag[0] && strcmp((char *) cur->name, "Id") == 0) {
					setIdP(post, atol(value));
					flag[0] = 1;
					free(value);
					continue;
				}

				if(!flag[1] && strcmp((char *) cur->name, "PostTypeId") == 0) {
					setPostTypeIdP(post, atoi(value));
					flag[1] = 1;
					free(value);
					continue;

				}

				if(!flag[2] && strcmp((char *) cur->name, "ParentId") == 0) {
					l = atol(value);
					parent = search_POSTID(treeid, l);
					if(parent) {
						getAnswersP(parent, &n);
						setAsnwersP(parent, n + 1);
					}
					setPIdP(post, l);
					flag[2] = 1;
					free(value);
					continue;
				}

				if(!flag[3] && strcmp((char *) cur->name, "CreationDate") == 0) {
					date = xmlToMYDATE(value);
					setDateP(post, date);
					flag[3] = 1;
					free(value);
					free_MYdate(date);
					continue;
				}


				if(!flag[4] && strcmp((char *) cur->name, "Score") == 0) {
					setScoreP(post, atoi(value));
					flag[4] = 1;
					free(value);
					continue;
				}

				if(!flag[5] && strcmp((char *) cur->name, "OwnerUserId") == 0) {
					l = atol(value);
					setOwnerIdP(post, l);
					getDateP(post, &date);
					setPostToUSER(treeusers, l, date, post);
					flag[5] = 1;
					free(value);
					continue;
				}

				if(!flag[6] && strcmp((char *) cur->name, "OwnerDisplayName") == 0) {
					setOwnerNameP(post, value);
					flag[6] = 1;
					free(value);
					continue;
				}

				if(!flag[7] && strcmp((char *) cur->name, "Title") == 0) {
					setTitleP(post, value);
					flag[7] = 1;
					free(value);
					continue;
				}

				if(!flag[8] && strcmp((char *) cur->name, "Tags") == 0) {
					arr = xmlToStringArray(value);
					setTagsP(post, arr);
					flag[8] = 1;
					free(value);
					free_StringArray(arr);
					continue;
				}

				if(!flag[9] && strcmp((char *) cur->name, "AnswerCount") == 0) {
					setAsnwersP(post, atoi(value));
					flag[9] = 1;
					free(value);
					continue;
				}

				if(!flag[10] && strcmp((char *) cur->name, "CommentCount") == 0) {
					setCommentsP(post, atoi(value));
					flag[10] = 1;
					free(value);
					continue;
				}

				if(!flag[11] && strcmp((char *) cur->name, "FavoriteCount") == 0) {
					setFavsP(post, atoi(value));
					flag[11] = 1;
					free(value);
					continue;
				}

				free(value);
	}

	if(parent){
		getDateP(post,&date);
		getPIdP(post,&l);
		setFilhosNoPost(parent,date,post);
	}
}
