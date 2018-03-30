#include <mypost.h>
#include <date.h>


typedef struct mypost *MYPOST;


struct mypost {
	long 		id;
	int		typeid;
	long 		parent_id;
	MYDATE		cdate;
	int 		score;
	long 		ownerid;
	char *		ownername;
	char *		title;
	char **		tags;
	int 		anscount;
	int		commcount;
	int		favcount;
	int		votecount;			//contruir ao dar load
	//lista de votos (so com o id do user)
};
/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o score de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo score do post.
 */
void setScoreP(MYPOST post, int  score){
  post->score=score;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o score de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o score do post.
 */
void getScoreP(MYPOST post, int * score){
  *score = post->score;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o Id de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o id do post.
 */
void getIdP(MYPOST post, long * id){
  *id = post->id;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que altera o Id de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo ID do post.
 */
void setIdP(MYPOST post, long  id){
  post->id=id;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o TypeId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o TypeId do post.
 */
void getPostTypeIdP(MYPOST post, int * id){
  *id = post->typeid;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o TypeId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo TypeId do post.
 */
void setPostTypeIdP(MYPOST post, long  id){
  post->typeid=id;
}



/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o ParentId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o ParentId do post.
 */
void getPIdP(MYPOST post, long * p_id){
  *p_id = post->parent_id;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o ParentId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo ParendId do post.
 */
void setPIdP(MYPOST post, long  id){
  post->parent_id=id;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém a data de criação de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador para struct onde a função devolve a data do post.
 */
void getDateP(MYPOST post, MYDATE * data){
  *data = post->cdate;
}


/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera a data de criação de um post.
 * @param 			Apontador para a struct do post.
 * @param			Nova data do post.
 */
void setDateP(MYPOST post, MYDATE data){
  post->cdate=data;
}



/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o OwnerId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o id do owner post.
 */
void getOwnerIdP(MYPOST post, long * id){
  *id = post->ownerid;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o OwnerId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo OwnerId do post.
 */
void setOwnerIdP(MYPOST post, long  id){
  post->ownerid = id;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que inicializa a (nossa) representação de um post na memória.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde afunção devolve o nome do post.
 */
void getOwnerNameP(MYPOST post, char * name){
	if(post->ownername == NULL) {
		*name = '\0';
		return;
	}
	strcpy(name, post->ownername);
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o OwnerName de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo OwnerName do post.
 */
void setOwnerNameP(MYPOST post, char *  name){
  post->ownername = name;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o título de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o titulo do post.
 */
void getTitleP(MYPOST post,char* title){
	if(post->title == NULL) {
		*title = '\0';
		return;
	}
	strcpy(title, post->title);
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o título de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo titulo do post.
 */
void setTitleP(MYPOST post, char* title){
  post->title=title;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém as tags de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador para a lista de strings onde vao ser devolvidas as tags do post.
 */
void getTagsP(MYPOST post,char *** tags){
	if(post->tags == NULL) {
		*tags = NULL;
		return;
	}

	int i ;

	for(i= 0; post->tags[i] != NULL; i++)
		;
	*tags = malloc(sizeof(char *)*(i + 1));

	for(i= 0; post->tags[i] != NULL; i++) {
		(*tags)[i] = malloc(strlen(post->tags[i]) + 1);
		strcpy((*tags)[i], post->tags[i]);
	}
	(*tags)[i] = NULL;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera a lista de tags de um post.
 * @param 			Apontador para a struct do post.
 * @param			Nova lista de tags do post.
 */
void setTagsP(MYPOST post, char** tags){
  post->tags=tags;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de respostas de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o numero de respostas do post.
 */
void getAnswersP(MYPOST post,int *answer){
	*answer = post->anscount;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o numero de respostas de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo numero de respostas do post.
 */
void setAsnwersP(MYPOST post, int answer){
  post->anscount=answer;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de comentarios de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o numero de comentarios do post.
 */
void getCommentsP(MYPOST post,int *comments){
	*comments = post->commcount;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o numero de comentarios de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo comentarios de respostas do post.
 */
void setCommentsP(MYPOST post, int comments){
  post->commcount=comments;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de favoritos de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o numero de favoritos do post.
 */
void getFavsP(MYPOST post,int *fav){
	*fav = post->favcount;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o numero de favoritos de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo favoritos de respostas do post.
 */
void setFavsP(MYPOST post, int fav){
  post->favcount=fav;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de votos de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o numero de votos do post.
 */
void getVotesP(MYPOST post,int *votes){
	*votes = post->votecount;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o numero de votos de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo numero de votos do post.
 */
void setVotesP(MYPOST post, int votes){
  post->votecount=votes;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que inicializa a (nossa) representação de um user na memória.
 * @return 			Apontador para a struct do user.
 */
MYPOST createpost() {
	MYPOST post = malloc(sizeof(struct mypost));
	post->ownername = NULL;
	post->tags 	= NULL;
	post->cdate	= NULL;
	post->title	= NULL;
	post->parent_id = 0;
	post->votecount = 0;
	return post;
}




/**
 * @date 			24 Mar 2018
 * @brief 			Função que liberta a memória alocada para as tags de um post.
 * @param  array		Apontador para o array de strings que representa as tags.
 */
void freeTags(char ** array) {
	if(array == NULL)
		return;

	int i;
	for(i = 0; array[i]; i++)
		if(array[i] != NULL)
			free(array[i]);

	if(array[i] != NULL)
		free(array[i]);

	free(array);
}



/**
 * @date 			24 Mar 2018
 * @brief 			Função que liberta a memória alocada para um dado post.
 * @param 			Apontador para a struct do post.
 */
void freepost(MYPOST post) {
	if(post == NULL)
		return;

	if(post->title != NULL)
		free(post->title);

	if(post->ownername != NULL)
		free(post->ownername);

	freeTags(post->tags);
	free_MYdate(post->cdate);

	free(post);
}




/**
 * @brief				Função que compara 2 datas de posts diferentes para inserir numa AVL.
 * @param				Apontador para a primeira data.
 * @param				Apontador para a segunda data.
*/


int compare_mypostsAVLDate(void * data1, void * data2,void * data){
	return  compare_MYDATE_AVL(data1,data2);

}

/**
 * @brief				Função que compara 2 keys de posts diferentes para inserir numa AVL.
 * @param				Apontador para o 1 key.
 * @param				Apontador para o 2 key.
*/


int compare_mypostsAVLID(void * key1, void * key2,void * data){
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
 * @brief				Função que compara 2 data de posts diferentes para inserir numa LIST.
 * @param				Apontador para a primeira data.
 * @param				Apontador para a segunda data.
*/


int compare_mypostsLISTDate(void * data1, void * data2){
	return  compare_MYDATE_LIST(data1,data2);

}


/**
 * @brief				Função que procura um post pelo id na estrutura.
 * @param				Id do post a procurar.
*/

MYPOST search_POSTID(TREE tree,long id){
	int valid;

	MYPOST post = search_AVL(tree, &id, &valid);
	if (valid)
		return post;
	return NULL;
}


/**
 * @brief				Função que procura um post pela data de criação na estrutura.
 * @param				Id do post a procurar.
*/

MYPOST search_POSTDATA(TREE tree,MYDATE date){
	int valid;

	MYPOST post = search_AVL(tree, date, &valid);
	if (valid)
		return post;
	return NULL;
}
