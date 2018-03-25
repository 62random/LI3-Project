
typedef struct mypost *MYPOST;

struct mypost {
	long 		id;
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
} * MYPOST;

///mudar o resto das funções para void

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
  memcpy(data, post->cdate, sizeof(struct date));
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
 */
char * getTile(MYPOST post){

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
