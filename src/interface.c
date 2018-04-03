#include "interface.h"

#define MAX_DUMP_PATH_SIZE 300

struct TCD_community {
	TREE users;
	TREE posts_Date;
	TREE posts_Id;
	MYLIST user_ord;
};


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
