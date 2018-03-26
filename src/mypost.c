#include <mypost.h>
#include <date.h>


typedef struct mypost *MYPOST;


struct mypost {
	long 		id;
	int			typeid;
	long 		parent_id;
	Date		cdate;
	int 		score;
	long 		ownerid;
	char *		ownername;
	char *		title;
	char **		tags;
	int 		anscount;
	int			commcount;
	int			favcount;
	int			votecount;			//contruir ao dar load
	//lista de votos (so com o id do user)
};



/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o Id de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o id do post.
 */
void getId(MYPOST post, long * id){
  *id = post->id;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que altera o Id de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo ID do post.
 */
void setId(MYPOST post, long  id){
  post->id=id;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o TypeId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o TypeId do post.
 */
void getPostTypeId(MYPOST post, int * id){
  *id = post->typeid;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que altera o TypeId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo TypeId do post.
 */
void setPostTypeId(MYPOST post, int  id){
  post->typeid = id;
}




/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o Id de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o ParentId do post.
 */
void getPId(MYPOST post, long * p_id){
  *p_id = post->parent_id;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém a data de criação de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador para struct onde a função devolve a data do post.
 */
void getDate(MYPOST post, Date data){
  memcpy(data, post->cdate, date_size());
}




/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o OwnerId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o id do owner post.
 */
void getOwnerId(MYPOST post, long * id){
  *id = post->ownerid;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que inicializa a (nossa) representação de um post na memória.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde afunção devolve o nome do post.
 */
void getOwnerName(MYPOST post, char * name){
	strcpy(name, post->ownername);
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o título de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o titulo do post.
 */
void getTitle(MYPOST post,char* title){
	strcpy(title, post->title);
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém as tags de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador para a lista de strings onde vao ser devolvidas as tags do post.
 */

 // esta merda pode estar a foder testar isto
void getTags(MYPOST post,char** tags){
	int i ;
	for(i= 0; tags[i] != NULL; i++)
		strcpy(tags[i], post->tags[i]);
	tags[i] = NULL;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém as respostas de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o numero de respostas do post.
 */
void getAnswer(MYPOST post,int *answer){
	*answer = post->anscount;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de comentarios de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o numero de comentarios do post.
 */
void getComments(MYPOST post,int *comments){
	*comments = post->commcount;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de favoritos de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o numero de favoritos do post.
 */
void getFavs(MYPOST post,int *fav){
	*fav = post->favcount;
}
/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de votos de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o numero de votos do post.
 */
void getVotes(MYPOST post,int *votes){
	*votes = post->votecount;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que inicializa a (nossa) representação de um user na memória.
 * @return 			Apontador para a struct do user.
 */
MYPOST createpost() {
	MYPOST post = malloc(sizeof(struct mypost));
	return post;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que liberta a memória alocada para um dado post.
 * @param 			Apontador para a struct do post.
 */
void freepost(MYPOST post) {
	free(post->title);
	free(post->ownername);
	free(post->tags);
}
