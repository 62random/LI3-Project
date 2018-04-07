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
	//printf("U:%d,D:%d ,IDP:%d\n",test_TREE_PROP(users),test_TREE_PROP(postsDate),test_TREE_PROP(posts_ID));

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
//3
/**
 * @brief			Função retorna a informacao de um post.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Id do post
*/
STR_pair info_from_post(TAD_community com, long id){
	char * title = NULL;
	char * user = NULL;
	long iduser = -2;
	int tipopost = -1;
	long pai = -1;
	STR_pair result = NULL;

	MYPOST post = search_POSTID(com->posts_Id,id);

	if(!post){
		freepost(post);
		return result;
	}

	getPostTypeIdP(post,&tipopost);
	if(tipopost == 2){ // resposta
		getPIdP(post,&pai);
		post = search_POSTID(com->posts_Id,pai); // se for uma respota vai buscar o seu pai( sua pergunta )
	}

	getTitleP(post,&title);
	getOwnerIdP(post,&iduser);
	MYUSER us = search_USER(com->users,iduser);
	user = getUsername(us);
	result = create_str_pair(title,user);

	return result;


}

void filtraPerguntasRespostas(void * nodo ,void * perguntas, void *respostas){

	if (nodo){
		MYPOST post =(MYPOST) nodo;
		int type;
		long aux;
		getPostTypeIdP(post,&type);
		if (type == 1){ // pergunta
			aux = *(long*)perguntas;
			aux++;
			*(long*)perguntas = aux;
		}
		if (type == 2){ // respotas
			aux = *(long*)respostas;
			aux++;
			*(long*)respostas = aux;
		}
	}
}


/**
 * @brief			Função que dado um intervalo de tempo obtem o numero total de perguntas e respostas.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Data inicial da procura
 * @param			Data final da procura
*/
LONG_pair total_posts(TAD_community com, Date begin, Date end){
	long res1, res2 ;
	res1 = res2 = 0;
	all_nodes_With_Condition(com->posts_Date,begin,end,&(filtraPerguntasRespostas),&res1,&res2);
	LONG_pair result = create_long_pair(res1,res2);
	return result;
}



/**
 * @brief			Função que dado um id de um user devolve informacao sobre este mesmo.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Id do post
*/
USER get_user_info(TAD_community com, long id){
	MYUSER user = search_USER(com->users,id);
	int aux = 0;
	long * posts;
	posts = getNposts(user,10,&aux);
	if(aux != 10){
		for(aux;aux < 10; aux ++)
			posts[aux] = -1;
	}
	USER info = create_user(getBiography(user),posts);
	return info;
}
