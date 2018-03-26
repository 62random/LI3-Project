#include <myuser.h>


typedef struct myuser * MYUSER;

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

static void setId(MYUSER use, long id){
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

void freeMYUSER(MYUSER conta){
    if (!conta){
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

int compare_user(long * key1, long * key2){
    long id1,id2;
    int result;

    id1 = *key1;
    id2 = *key2;

    if (id1 == id2)
        result = 0;
    result = id1 > id2 ? 1 : -1 ;

    return result;
}

/**
 * @brief				Função que liberta a memória de um key.
 * @param				Apontador para a key.
*/

void freeKey(long * a){
    if (a)
        free(a);
}

void createTREE(){

    xmlDocPtr doc;
	xmlNodePtr ptr;
	struct _xmlAttr * cur;
	xmlNodePtr aux;

	xml_file_to_struct(doc,ptr,"Users.xml");


    /*
    long id;
    int rep;*/

    aux = ptr->children->next;
    xmlChar *key;
	while (aux != NULL){
        //MYUSER use = createMYUSER();
		cur = aux->properties;
		 	while (cur != NULL) {
				key = xmlNodeListGetString(doc,cur->children,1);
                /*
			    if (strcmp(cur->name,"Id")==0){
                    id = atoi(key);
                    setId(use,id);
                }
                if (strcmp(cur->name,"Reputation")==0){
                    rep = atoi(key);
                    setRp(use,rep);
                }
                if (strcmp(cur->name,"DisplayName")==0){
                    setUsername(use,key);
                }
                if (strcmp(cur->name,"AboutMe")==0){
                    setRp(use,key);
                }*/

				cur = cur->next;
			}
		aux = NULL;
	}



}
