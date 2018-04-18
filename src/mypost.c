#include <common.h>
#include <mypost.h>
#include <date.h>

struct mypost {
	long 		id;
	int			typeid;
	long 		parent_id;
	MYDATE		cdate;
	int 		score;
	long 		ownerid;
	char *		ownername;
	char *		title;
	char **		tags;
	int 		anscount;
	int			commcount;
	int			favcount;
	STACKPOST	filhos;
};

struct stackpost {
	long counter1;
	long counter2;
	long n_elem;
	long size;
	MYPOST * array;
};

/**
 * @brief			Função que inicializa um stackpost.
 * @param			Tamanho original da stackpost.
*/

STACKPOST initSTACKPOST(long size){
	STACKPOST a = malloc(sizeof(struct stackpost));
	a->counter1 = 0;
	a->counter2 = 0;
	a->n_elem = 0;
	a->size = size;
	a->array = malloc(size*sizeof(MYPOST));

	return a;
}

/**
 * @brief			Função que insere um elemento numa stackpost.
 * @param			STACKPOST.
 * @param			Post a inserir.
*/

void insereSTACKPOST(STACKPOST st, MYPOST post){
	long i;
	MYPOST * aux;
	if (st->n_elem >= st->size){
		st->size *= 2;
		aux = malloc(st->size*sizeof(MYPOST));
		for(i=0; i < st->n_elem; i++)
			aux[i] = st->array[i];
		free(st->array);
		st->array = aux;
	}
	st->array[st->n_elem++] = post;

}

/**
 * @brief			Função que calcula o número de elementos de uma stackpost.
 * @param			STACKPOST.
*/

long get_NUM_eleSTACKPOST(STACKPOST st){
	return st ? st->n_elem : 0;
}

/**
 * @brief			Função que devolve o elemento na posição dada.
 * @param			STACKPOST.
 * @param			Indice a consultar.
*/

MYPOST get_ele_index_STACKPOST(STACKPOST st, long i){
	if (i >= st->n_elem)
		return NULL;
	return st->array[i];
}

/**
 * @brief			Função que dá free a uma stackpost.
 * @param			STACKPOST.
*/

void freeSTACKPOST_SEM_CLONE(STACKPOST st){
	if (st){
		free(st->array);
		free(st);
	}
}



/**
 * @brief 			Função que verifica se existe uma data tag num post.
 * @param 			Apontador para a struct do post.
 * @param			Tag a verificar.
 */
int	existeTag(MYPOST post,char * tag){
	int i;
	if(!post->tags)
		return 0;
	for(i=0;post->tags[i] != NULL;i++){
//	printf("%s == %s\n",post->tags[i],tag );
		if(strcmp(post->tags[i],tag) == 0 )
			{printf("YUPI , %ld\n",post->id);
			return 1;
			}
		}
	return 0;
}

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
	if(post)
  		*score = post->score;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém os filhos de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve os filhos do post.
 */

//quebra o encap
void getFilhosP(MYPOST post, STACKPOST * filhos){
	if(post)
		(*filhos) = post->filhos;
}

/**
 * @brief				Função mete um post nos filhos desse mesmo post.
 * @param				Árvore de posts.
 * @param				Identificador do post.
 * @param				Key do filhos a inserir.
 * @param				Informação do post.
*/

int setPostToPost(TREE tree,long id,MYPOST data){
		MYPOST post;
		post = search_POSTID(tree,id);
		if (post == NULL)
			return -1;
		insereSTACKPOST(post->filhos,data);
		return 1;
}

/**
 * @brief				Função mete um post nos filhos desse mesmo post.
 * @param				Identificador do post.
 * @param				Key do filhos a inserir.
 * @param				Informação do post.
*/

void setFilhosNoPost(MYPOST post,MYPOST data){
		if (post == NULL)
			return;
		insereSTACKPOST(post->filhos,data);
}




/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o Id de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o id do post.
 */
void getIdP(MYPOST post, long * id){
	if(post)
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
	if(post)
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
	if(post)
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
	if(post){
		MYDATE date;
		date = createMYDate(get_MYday(post->cdate),
							get_MYmonth(post->cdate),
					 		get_MYyear(post->cdate));
  		*data = date;
	}
}


/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera a data de criação de um post.
 * @param 			Apontador para a struct do post.
 * @param			Nova data do post.
 */
void setDateP(MYPOST post, MYDATE data){
	MYDATE date;

	date = createMYDate(get_MYday(data),
	get_MYmonth(data),
	get_MYyear(data));

  	post->cdate = date;
}



/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o OwnerId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Apontador onde a função devolve o id do owner post.
 */
void getOwnerIdP(MYPOST post, long * id){
	if(post)
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
void getOwnerNameP(MYPOST post, char ** name){
	if(post)
		*name = mystrdup(post->ownername);
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o OwnerName de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo OwnerName do post.
 */
void setOwnerNameP(MYPOST post, char *  name){
	post->ownername = mystrdup(name);
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o título de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o titulo do post.
 */
void getTitleP(MYPOST post,char ** title){
	if(post)
		*title = mystrdup(post->title);
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o título de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo titulo do post.
 */
void setTitleP(MYPOST post, char* title){
	post->title = mystrdup(title);
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém as tags de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador para a lista de strings onde vao ser devolvidas as tags do post.
 */
void getTagsP(MYPOST post,char *** tags){
	if(post){
		if(post->tags == NULL) {
			*tags = NULL;
			return;
		}

		int i ;

		for(i= 0; post->tags[i] != NULL; i++)
			;
			*tags = malloc(sizeof(char *)*(i + 1));

		for(i= 0; post->tags[i] != NULL; i++){
			(*tags)[i] = mystrdup(post->tags[i]);
		}


		(*tags)[i] = NULL;


//		for(i=0;(*tags)[i] != NULL;i++)
	//		printf("%s , %i\n",(*tags)[i],i );
	}
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera a lista de tags de um post.
 * @param 			Apontador para a struct do post.
 * @param			Nova lista de tags do post.
 */
void setTagsP(MYPOST post, char ** tags){
	if(tags == NULL) {
		post->tags = NULL;
		return;
	}

	int i ;

	for(i= 0; tags[i] != NULL; i++)
		;
	post->tags = malloc(sizeof(char *)*(i + 1));

	for(i= 0; tags[i] != NULL; i++)
		post->tags[i] = mystrdup(tags[i]);
	post->tags[i] = NULL;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de respostas de um post.
 * @param 			Apontador para a struct do post.
 * @param 			Apontador onde a funcao devolve o numero de respostas do post.
 */
void getAnswersP(MYPOST post,int *answer){
	if(post)
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
	if(post)
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
	if(post)
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
 * @brief 			Função que inicializa a (nossa) representação de um post na memória.
 * @return 			Apontador para a struct do post.
 */
MYPOST createpost() {
	MYPOST post = malloc(sizeof(struct mypost));
	post->ownername = NULL;
	post->tags 	= NULL;
	post->cdate	= NULL;
	post->title	= NULL;
	post->ownerid = -2;
	post->parent_id = -2;
	post->favcount	= 0;
	post->anscount	= 0;
	post->filhos = initSTACKPOST(1);
	return post;
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

	free_StringArray(post->tags);
	free_MYdate(post->cdate);
	freeSTACKPOST_SEM_CLONE(post->filhos);

	free(post);
}


/**
 * @date 			29 Mar 2018
 * @brief 			Função que liberta um array de strings.
 * @param value		O array de strings.
 */
void free_StringArray(char ** arr) {
	if(arr == NULL)
		return;

	int i;
	for(i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
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
 * @brief			Função que imprime os ids das respostas a um post.
 * @param			Apontador para o post.
*/

void print_posts_MYPOST(MYPOST post){
	MYPOST post2 = NULL;
	MYDATE data = NULL;
	long ld=0;
	int i = 0;
	printf("Ne:%ld\n",post->filhos->n_elem);
	for(i=0; i < post->filhos->n_elem; i++){
		post2 = get_ele_index_STACKPOST(post->filhos,i);
		if (post2 != NULL){
			getIdP(post2,&ld);
			getDateP(post2,&data);
			if (data != NULL){
				printf("Data-> D:%d M:%d A:%d || ID:%ld \n",get_MYday(data),get_MYmonth(data),get_MYyear(data),ld);
				free_MYdate(data);
			}
		}
	}
	printf("I=%d\n",i);
}
