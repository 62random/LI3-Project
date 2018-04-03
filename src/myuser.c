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
long * getNposts(MYUSER use,int n,int * n_elem){
	long * r = malloc(n*sizeof(long));
	int i = 0;
	MYPOST post = NULL;
	LList aux = getFirst_BOX(use->posts);

	for(i=0; i < n && aux != NULL; i++){
		post = (MYPOST) getElemente_LList(aux);
		if (post != NULL){
			getIdP(post,r+i);
		}
		aux = getNext_LList(aux);
	}
	*n_elem = i;
	return r;
}

/**
 * @brief			Função que imprime os id dos post de um utilizador.
 * @param			Apontador para o user.
*/

void print_post_MYUSER(MYUSER use){
	LList aux = getFirst_BOX(use->posts);
	MYPOST post = NULL;
	MYDATE data;
	long ld=0;
	int i = 0;
	printf("Ne:%d\n",get_NUM_ele(use->posts));
	while(aux){
		post = (MYPOST) getElemente_LList(aux);
		if (post != NULL){
			getIdP(post,&ld);
			getDateP(post,&data);
			if (data != NULL){
				printf("Data-> D:%d M:%d A:%d || ID:%ld \n",get_MYday(data),get_MYmonth(data),get_MYyear(data),ld);
				free_MYdate(data);
			}
		}
		i++;
		aux = getNext_LList(aux);
	}
	printf("I=%d\n",i);
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
	if (bio)
    	use->bio = mystrdup(bio);
	else use->bio = NULL;
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
	conta->bio = NULL;
	conta->username = NULL;
	conta->posts = init_MYLIST(&compare_MYDATE_LIST,&free_MYdate,NULL);
    return conta;
}

/**
 * @brief				Função que liberta a memória de um user.
 * @param 				Memória a libertar.
*/

void freeMYUSER(void * aux){
	MYUSER conta;
    if (aux != NULL){
		conta = (MYUSER) aux;
		if (conta->bio)
        	free(conta->bio);
		if (conta->username)
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

int compare_user(void * key1,void * key2){
    long id1,id2;
    int result;

    id1 = *((long *) key1);
    id2 = *((long *) key2);

    if (id1 == id2)
        result = 0;
    else result = id2 > id1 ? 1 : -1 ;

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

void freeTreeUSER(TREE tree){
	freeTREE_AVL(tree);
}

/**
 * @brief				Função que procura um user na estrutura.
 * @param				Id do user a procurar.
*/

MYUSER search_USER(TREE tree,long id){
	int valid;

	MYUSER use = search_AVL(tree,&id,&valid);
	if (valid)
		return use;
	return NULL;
}

/**
 * @brief				Função mete um post no correspondete user.
 * @param				Árvore de users.
 * @param				Identificador do user.
 * @param				Key do post a inserir.
 * @param				Informação do post.
*/

int setPostToUSER(TREE tree,long id,MYDATE date,void * data){
	MYUSER use;
	use = search_USER(tree,id);
	if (use == NULL)
		return -1;
	use->posts = insere_list(use->posts,date,data);

	return 1;
}

/**
 * @brief				Função lê o ficheiro User.xml e cria uma arvore.
*/

TREE createMYUSERS_TREE(char * path){

    xmlDocPtr doc;
	xmlNodePtr ptr;
	struct _xmlAttr * cur;
	xmlNodePtr aux;

	MYUSER use = NULL;
	TREE tree = createTREE(&compare_user,&freeKey,&freeMYUSER);

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
						if (key == NULL)
							setBio(use,NULL);
						else setBio(use,(char*)key);
                	}

					xmlFree(key);
					cur = cur->next;
				}
				keyid = malloc(sizeof(long));
				*keyid = id;
				tree = insere_tree(tree,keyid,use);
		}
		aux = aux->next;
	}
	xmlFreeDoc(doc);
	xmlCleanupParser();


	return tree;

}
