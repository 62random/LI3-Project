#include "myuser.h"

struct myuser{
    long id;
    int rep;
    char * username;
    char * bio;
	MYLIST posts;
};

/**
 * @brief			Função que devolve o id do user.
 * @param			Apontador para o user.
*/

long getIdMYUSER(MYUSER use){
	return use->id;
}

/**
 * @brief			Função que devolve a rep do user.
 * @param			Apontador para o user.
*/

int getREPMYUSER(MYUSER use){
	return use->rep;
}

/**
 * @brief			Função que devolve o Username do user.
 * @param			Apontador para o user.
*/

char * getUsername(MYUSER use){
	if (use)
		return mystrdup(use->username);
	return NULL;
}

/**
 * @brief			Função que devolve a biografia do user.
 * @param			Apontador para o user.
*/

char * getBiography(MYUSER use){
	if (use)
		return mystrdup(use->bio);
	return NULL;
}

/**
 * @brief			Função que devolve os ultimos N posts de um dado utilizador.
 * @param			Apontador para o user.
 * @param			Número de posts.
*/

long * getNposts(MYUSER use,int n){
	long * r = malloc(n*sizeof(long));
	int i = 0;
	LList aux = use->posts->lista;
	while(aux && i != n){
		//r[i++] = getId(aux->data)
		//aux=aux->next;
	}
	return r;
}

/**
 * @brief 			Função que altera o Id de um user.
 * @param 			Apontador para a struct do user.
 * @param			Id do user a colocar.
 */

static void setIdUSER(MYUSER use, long id){
    use->id = id;
}

/**
 * @brief 			Função que altera a reputação de um user.
 * @param 			Apontador para a struct do user.
 * @param			Reputação do user a colocar.
 */

static void setRp(MYUSER use, int rep){
    use->rep = rep;
}

/**
 * @brief 			Função que altera a biografia de um user.
 * @param 			Apontador para a struct do user.
 * @param			Biografia a colocar no user.
 */

static void setBio(MYUSER use, char * bio){
    use->bio = mystrdup(bio);
}

/**
 * @brief 			Função que obtém altera o nome de um user.
 * @param 			Apontador para a struct do user.
 * @param			Nome do user a colocar.
*/

static void setUsername(MYUSER use, char * nome){
    use->username = mystrdup(nome);
}

/**
 * @brief 			Função que aloca memória para um user
 */

MYUSER createMYUSER(){
    MYUSER conta = malloc(sizeof(struct myuser));
	conta->posts = init_MYLIST(&compare_MYDATE_LIST,&free_MYdate,NULL);
    return conta;
}

/**
 * @brief				Função que liberta a memória de um user.
 * @param 				Memória a libertar.
*/

void freeMYUSER(void * aux){
	MYUSER conta;
    if (!aux){
		conta = (MYUSER) aux;
        free(conta->bio);
        free(conta->username);
		free_MYLIST(conta->posts);
        free(conta);
    }
}

/**
 * @brief				Função que compara 2 keys de user diferentes.
 * @param				Apontador para a primeira key.
 * @param				Apontador para a segunda key.
*/

int compare_user(const void * key1, const void * key2,void * data){
    long id1,id2;
    int result;

    id1 = *((long *) key1);
    id2 = *((long *) key2);

    if (id1 == id2)
        result = 0;
    else result = id1 > id2 ? 1 : -1 ;

    return result;
}

/**
 * @brief				Função que liberta a memória de um key.
 * @param				Apontador para a key.
*/

void freeKey(void * a){
	long * b;
    if (a){
        b = (long *) a;
		free(b);
	}
}

/**
 * @brief				Função que liberta a memória da arvóre alocada.
*/

void freeTreeUSER(GTree * tree){
	g_tree_destroy(tree);
}

/**
 * @brief				Função que procura um user na estrutura.
 * @param				Id do user a procurar.
*/

MYUSER search_USER(GTree * tree,long id){

	MYUSER use = g_tree_lookup(tree,&id);
	return use;
}

/**
 * @brief				Função mete um post no correspondete user.
 * @param				Árvore de users.
 * @param				Identificador do user.
 * @param				Key do post a inserir.
 * @param				Informação do post.
*/

int setPostToUSER(GTree * tree,long id,MYDATE date,void * data){
	MYUSER use;
	use = search_USER(tree,id);
	if (use == NULL)
		return -1;
	use->posts = insere_list(use->posts,date,data);

	return 1;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que (recorrendo à biblioteca libxml2) efetua o parsing de um ficheiro xml.
 * @param doc		O apontador do ficheiro xml.
 * @param ptr 		O apontador da estrutura resultante do parsing do ficheiro xml.
 * @param filepath 	O filepath do ficheiro xml a ser lido e carregado.
 */

static int xml_file_to_struct(xmlDocPtr * doc, xmlNodePtr * ptr, char * filepath) {

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
 * @brief				Função lê o ficheiro User.xml e cria uma arvore.
*/

GTree * createTREE(char * path){

    xmlDocPtr doc;
	xmlNodePtr ptr;
	struct _xmlAttr * cur;
	xmlNodePtr aux;

	MYUSER use = NULL;
	GTree * tree = g_tree_new_full(&compare_user,NULL,&freeKey,&freeMYUSER);

	if (!(xml_file_to_struct(&doc,&ptr,path)))
		return tree;



    long id;
	long * keyid = NULL;
    int rep;

    aux = ptr->children->next;
    xmlChar *key;
	while (aux != NULL){
		if (strcmp((char*)aux->name,"row")==0){
        	use = createMYUSER();
			cur = aux->properties;
		 		while (cur != NULL) {
					key = xmlNodeListGetString(doc,cur->children,1);

			    	if (strcmp((char*)cur->name,"Id")==0){
                    	id = atoi((char*)key);
                    	setIdUSER(use,id);
                	}
                	if (strcmp((char*)cur->name,"Reputation")==0){
                    	rep = atoi((char*)key);
                    	setRp(use,rep);
                	}
                	if (strcmp((char*)cur->name,"DisplayName")==0){
                    	setUsername(use,(char*)key);
                	}
                	if (strcmp((char*)cur->name,"AboutMe")==0){
                    	setBio(use,(char*)key);
                	}

					cur = cur->next;
				}
				keyid = malloc(sizeof(long));
				*keyid = id;
				g_tree_insert(tree,keyid,use);
		}
		aux = aux->next;
	}
	//falta free da arvore
	xmlCleanupParser();


	return tree;

}
