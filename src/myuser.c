#include "myuser.h"

struct myuser{
    long id;
    int rep;
    char * username;
    char * bio;
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
 * @brief				Função que procura um user na estrutura.
 * @param				Id do user a procurar.
*/

MYUSER search_USER(GTree * tree,long id){

	MYUSER use = g_tree_lookup(tree,&id);
	return use;
}

/**
 * @brief				Função lê o ficheiro User.xml e cria uma arvore.
*/

GTree * createTREE(const char * path){

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


	return tree;

}
