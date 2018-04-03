#include "interface.h"

#define MAX_DUMP_PATH_SIZE 300

struct TCD_community {
	TREE users;
	TREE posts_Date;
	TREE posts_Id;
	MYLIST user_ord;
};

/**
 * @brief			Função que dita a ordem de uma lista.
 * @param			Apontador para o primeiro elemento.
 * @param			Apontador para o segundo elemento.
*/


int ord_menor(void * data1,void * data2){
	int key1 = *(int *) data1;
	int key2 = *(int *) data2;

	return key2 > key1;
}

/**
 * @brief			Função que adiciona um elemento a uma lista.
 * @param			Apontador para o elemento.
 * @param			Apontador para a lista.
*/


void constroi_list(void * data1,void * data2){
	MYLIST aux = *(MYLIST *) data2;
	MYUSER use = (MYUSER) data1;
	MYLIST use_list = getMYLISTuser(use);

	int * key = malloc(sizeof(int));
	*key = get_NUM_ele(use_list);
	aux = insere_list(aux,key,use);
	*(MYLIST *)data2 = aux;
}

/**
 * @brief			Função que monta a lista dos users ordenada.
 * @param			Estrutura onde está contiga a árvore.
*/


MYLIST monta_N_resp_user(TREE users){
	MYLIST aux = init_MYLIST(&ord_menor,&free,NULL);

	all_nodes_TREE(users,&constroi_list,&aux);

	return aux;
}

/**
 * @brief			Função inicializa a estrutura da comunidade.
*/


TAD_community init(){
	TAD_community aux = malloc(sizeof(struct TCD_community));
	return aux;
}

/**
 * @brief			Função dá load aos ficheiros xml.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			String com a diretoria onde se encontram os ficheiros.
*/

TAD_community load(TAD_community com, char * dump_path){
	char path [MAX_DUMP_PATH_SIZE];
	TREE users,postsDate = NULL,posts_ID = NULL;

	sprintf(path,"%s/Users.xml",dump_path);
	users = createMYUSERS_TREE(path);

	sprintf(path,"%s/Posts.xml",dump_path);
	createMYPOST_TREES(path, &posts_ID, &postsDate, users);

	sprintf(path,"%s/Votes.xml",dump_path);
	xmlVotes(path, posts_ID);

	com->users = users;
	com->posts_Date = postsDate;
	com->posts_Id = posts_ID;
	com->user_ord = monta_N_resp_user(users);

	return com;
}

/**
 * @brief			Função que liberta a memória da estrutura.
 * @param			Estrutura que guarda as outras estruturas.
*/

TAD_community clean(TAD_community com){
	freeTreeUSER(com->users);
	freeTREE_AVL(com->posts_Id);
	freeTREE_AVL(com->posts_Date);

	return com;
}
