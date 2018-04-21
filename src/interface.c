#include "interface.h"

#define MAX_DUMP_PATH_SIZE 300

struct TCD_community {
	TREE users;
	TREE posts_Date;
	TREE posts_Id;
	HEAP num_posts;
	STACK pre_posts;
	HEAP rep_users;
	STACK pre_rep;
};

/// tirar isto depois
TREE bla(TAD_community com){
	return com->posts_Id;
}


/**
 * @brief			Função inicializa a estrutura da comunidade.
*/


TAD_community init(){
	TAD_community aux = malloc(sizeof(struct TCD_community));
	return aux;
}


/**
 * @brief			Função adiciona a informação da data de um nodo MYUSER numa heap.
 * @param			Apontador para a data do nodo.
 * @param			Apontador para a heap.
*/


static void num_posts_na_HEAP(void * data,void * dataaux){
	HEAP h = (HEAP) dataaux;
	MYUSER user = (MYUSER) data;

	long n_post = getNUM_POST_MYUSER(user);
	insereHEAP(h,n_post,getIdMYUSER(user));
}

/**
 * @brief			Função adiciona a informação da data de um nodo MYUSER numa heap para reputação.
 * @param			Apontador para a data do nodo.
 * @param			Apontador para a heap.
*/

static void num_rep_na_HEAP(void * data,void * dataaux){
	HEAP h = (HEAP) dataaux;
	MYUSER user = (MYUSER) data;

	insereHEAP(h,getREPMYUSER(user),getIdMYUSER(user));
}

/**
 * @brief			Função adiciona a informação da data de um nodo MYLIST numa heap para scores.
 * @param			Apontador para a data do nodo.
 * @param			Apontador para a heap.
*/


static void postList_to_HEAP_score(void * data,void * dataaux,void * lal){
	HEAP h = (HEAP) dataaux;
	STACKPOST arr = (STACKPOST) data;
	MYPOST post = NULL;
	int type = -1;
	int score = -1;
	long id = -1;
	int i;
	long tam = get_NUM_eleSTACKPOST(arr);

	for(i=0; i < tam; i++){
		post = get_ele_index_STACKPOST(arr,i);
		if (post){
			getPostTypeIdP(post,&type);
			if (type == 2){
				getScoreP(post,&score);
				getIdP(post,&id);
				insereHEAP(h,score,id);
			}
		}
	}
}

/**
 * @brief			Função adiciona a informação da data de um nodo MYLIST numa heap para perguntas com mais respostas.
 * @param			Apontador para a data do nodo.
 * @param			Apontador para a heap.
*/

static void postList_to_HEAP_nresp(void * data,void * dataaux,void * lal){
	HEAP h = (HEAP) dataaux;
	STACKPOST arr = (STACKPOST) data;
	MYPOST post = NULL;
	int type = -1;
	int n_resp = -1;
	long id = -1;
	int i;
	long tam = get_NUM_eleSTACKPOST(arr);
	for(i=0; i < tam; i++){
		post = get_ele_index_STACKPOST(arr,i);
		if (post){
			getPostTypeIdP(post,&type);
			if (type == 1){
				getAnswersP(post,&n_resp);
				getIdP(post,&id);
				insereHEAP(h,n_resp,id);
			}
		}
	}
}

/**
 * @brief			Função que dado um intervalo de tempo calcula as N perguntas com mais respostas.
 * @param			Número de posts a calcular.
 * @param			Data do começo do intervalo.
 * @param			Data do fim do intervalo.
*/

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	HEAP h = initHEAP(NUM_nodes(com->posts_Id));
	LONG_list l = create_list(N);
	MYDATE b1 = DatetoMYDATE(begin);
	MYDATE e1 = DatetoMYDATE(end);

	all_nodes_With_Condition(com->posts_Date,b1,e1,&postList_to_HEAP_nresp,h,NULL);

	int i;
	long key,data;
	for(i=0; i < N && (get_NUM_eleHEAP(h) > 0); i++){
		pop(h,&key,&data);
		set_list(l,i,data);
	}
	if (i < N){
		for(; i<N ;i++)
			set_list(l,i,-2);
	}

	freeMYHEAP(h);
	free_MYdate(b1);
	free_MYdate(e1);

	return l;
}

/**
 * @brief			Função que dado um intervalo de tempo calcula os N posts com melhor score.
 * @param			Número de posts a calcular.
 * @param			Data do começo do intervalo.
 * @param			Data do fim do intervalo.
*/

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	HEAP h = initHEAP(NUM_nodes(com->posts_Id));
	LONG_list l = create_list(N);
	MYDATE b1 = DatetoMYDATE(begin);
	MYDATE e1 = DatetoMYDATE(end);
	all_nodes_With_Condition(com->posts_Date,b1,e1,&postList_to_HEAP_score,&h,NULL);

	int i;
	long key,data;
	for(i=0; i < N && (get_NUM_eleHEAP(h) > 0); i++){
		pop(h,&key,&data);
		set_list(l,i,data);
	}
	if (i < N){
		for(; i<N ;i++)
			set_list(l,i,-2);
	}

	freeMYHEAP(h);
	free_MYdate(b1);
	free_MYdate(e1);

	return l;
}

/**
 * @brief			Função ordena os posts de um user.
 * @param			Apontador para o user.
*/

static void ordenaMYUSER_ALL_NODES(void * data1,void * data2){
	MYUSER use = (MYUSER) data1;
	if (use){
		order_STACKPOST(getMYLISTuser(use),&ordenaPOST_MYUSER);
	}
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

	com->users = users;

	com->posts_Date = postsDate;
	com->posts_Id = posts_ID;
	all_nodes_TREE(com->users,&ordenaMYUSER_ALL_NODES,NULL);


	com->rep_users = initHEAP(NUM_nodes(users));
	com->pre_rep = NULL;
	all_nodes_TREE(users,&num_rep_na_HEAP,com->rep_users);
	com->num_posts = initHEAP(NUM_nodes(users));
	com->pre_posts = NULL;
	all_nodes_TREE(users,&num_posts_na_HEAP,com->num_posts);

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
	freeSTACK(com->pre_posts);
	freeMYHEAP(com->num_posts);
	freeSTACK(com->pre_rep);
	freeMYHEAP(com->rep_users);

	return com;
}

/**
 * @brief			Função que calcula os N utilizadores com melhor rep.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Número de jogadores.
*/

static long * n_users_with_more_rep(TAD_community com, int N){
	int i;
	long * array = malloc(N*sizeof(long));
	long id,key;

	if (com->pre_rep == NULL)
		com->pre_rep = initSTACK((long)N);

	if (((long) N) <= get_NUM_eleSTACK(com->pre_rep)){
		for(i=0; i < N; i++){
			array[i] = get_ELE_index(com->pre_rep,i);
		}
	}
	else{
		for(i=0; i < get_NUM_eleSTACK(com->pre_rep); i++)
			array[i] = get_ELE_index(com->pre_rep,i);
		for(; i < N; i++){
			pop(com->rep_users,&key,&id);
			com->pre_rep = insereSTACK(com->pre_rep,id);
			array[i] = get_ELE_index(com->pre_rep,i);
		}
	}

	return array;
}

//2
/**
 * @brief			Função que calcula os N utilizadores com mais posts.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Número de jogadores.
*/

LONG_list top_most_active(TAD_community com, int N){
	LONG_list l = create_list(N);
	int i;
	long id,key;

	if (com->pre_posts == NULL)
		com->pre_posts = initSTACK((long)N);

	if (((long) N) <= get_NUM_eleSTACK(com->pre_posts)){
		for(i=0; i < N; i++){
			set_list(l,i,get_ELE_index(com->pre_posts,i));
		}
	}
	else{
		for(i=0;i < get_NUM_eleSTACK(com->pre_posts); i++)
			set_list(l,i,get_ELE_index(com->pre_posts,i));
		for(; i < N; i++){
			pop(com->num_posts,&key,&id);
			//printf("%ld\n",key);
			com->pre_posts = insereSTACK(com->pre_posts,id);
			set_list(l,i,id);
		}
	}
	return l;
}

//1
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
	free(user);
	free(title);

	return result;


}

/**
 * @brief			Função que corre num nodo e calcula se é resposta ou pergunta.
 * @param			Apontador para a informação a filtar.
 * @param			Número de perguntas.
 * @param			Número de respostas.
*/

static void filtraPerguntasRespostas(void * data, void * perguntas, void * respostas){
	long aux;
	int type, i;
	STACKPOST arr = (STACKPOST) data;
	MYPOST post;
	if (data != NULL){ //p->1 r->2
		*(long *)perguntas += getCounter1_STACKPOST(arr);
		*(long *)respostas += getCounter2_STACKPOST(arr);
	}
}
/*
static void filtraPerguntasRespostas(void * data, void * perguntas, void * respostas){
	long aux1 = 0, aux2 = 0;
	int type, i;
	STACKPOST arr = (STACKPOST) data;
	MYPOST post;
	if (data != NULL){ //p->1 r->2
		for(i=0; i < get_NUM_eleSTACKPOST(arr);i++){
			post = get_ele_index_STACKPOST(arr,i);
			getPostTypeIdP(post,&type);
			if (type == 1){
				aux1++;
			}
			else if (type == 2){
				aux2++;
			}
		}
		*(long *)perguntas += aux1;
		*(long *)respostas += aux2;
	}
}*/

//3
/**
 * @brief			Função que dado um intervalo de tempo obtem o numero total de perguntas e respostas.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Data inicial da procura
 * @param			Data final da procura
*/
LONG_pair total_posts(TAD_community com, Date begin, Date end){
	long res1, res2 ;
	res1 = res2 = 0;
	MYDATE nbegin,nend;
	nbegin = DatetoMYDATE(begin);
	nend = DatetoMYDATE(end);
	all_nodes_With_Condition(com->posts_Date,nbegin,nend,&(filtraPerguntasRespostas),&res1,&res2);

	free_MYdate(nbegin);
	free_MYdate(nend);

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
	if(!user)
		return NULL;
	int aux = 0;
	long * posts;
	posts = getNposts(user,10,&aux);
	if(aux != 10){
		for(;aux < 10; aux++)
			posts[aux] = -1;
	}
	USER info = create_user(getBiography(user),posts);// leak mem
	free(posts);
	return info;
}

/**
 * @brief			Função que dado um id de um post devolve a resposta melhor cotada desse post.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Id do post
*/
long better_answer(TAD_community com, long id){
		STACKPOST * arr = NULL;
		MYUSER men;
		long user;
		int scr,rep,comt;
		int scoreatual,scoremax;
		scr=rep=comt=scoremax=scoreatual=0;
		long	 id2 = -2;
		int type,i;
		LList aux;

		MYPOST post = search_POSTID(com->posts_Id,id);
		if (!post){
			printf("Post inexistente\n");
			return -3;
		}
		getPostTypeIdP(post,&type);
		if(type != 1){
			printf("Post não é uma pergunta\n");
			return -4;
		}

		getFilhosP(post,&arr);
		if(arr == NULL)
			return -2;
		type = get_NUM_eleSTACKPOST(arr); // nao me apeteceu defenir outro int
		for(i=0; i < type; i++){
			post = get_ele_index_STACKPOST(arr,i);
			getScoreP(post,&scr);
			getCommentsP(post,&scr);
			getOwnerIdP(post,&user);
			men = search_USER(com->users,user);
			rep = getREPMYUSER(men);
			scoreatual =(scr * 0.65 + rep * 0.25  + comt * 0.1);
			if (scoreatual > scoremax){
				scoremax = scoreatual;
				getIdP(post,&id2);
	//			printf("score = %d ; post = %ld\n",scoreatual,id2 );
			}

		}
		return id2;

}


/**
 * @brief			Função a aplicar aos posts a ser visitados na travessia, auxiliar á query 8.
 * @param			Post a ser visitado.
 * @param			Lista onde serão guardados os id's dos posts relevantes.
 * @param			Palavra a ser procurada nos títulos.
 * @param			Número máximo de resultados N.
*/

static void contains_word_node(void * post, void * lista, void * word, void * n){
	if(post == NULL || *((int *) n) <= 0)
		return;

	MYPOST cpost = (MYPOST) post;
	int i;								// se não for
	getPostTypeIdP(cpost, &i);			// uma pergunta
	if(i != 1)							// então
		return;							// retornar

	MYLIST clista = (MYLIST) lista;
	char * cword = (char *) word, * title;
	long id;

	getTitleP(cpost, &title);
	if(strstr(title, cword) != NULL) {	// se o titulo contem a palavra
		getIdP(cpost, &id);
		insere_list(clista, (void *) id, NULL);
		int * cn = (int *) n;
		(*cn)--;
	}

	free(title);

}


/**
 * @brief			Função a aplicar ao array de posts efetuados no mesmo dia, auxiliar á query 8.
 * @param			Array onde estão armazenados os ids de posts de resposta à query.
 * @param			Número máximo de resultados N.
 * @param			Palavra a ser procurada nos títulos.
 * @param			Número máximo de resultados N.
*/

static void contains_word_arr(void * arr, void * res, void * word, void * n){
	if(arr == NULL)
		return;

	trans_arr(arr, &contains_word_node, res, word, n);
}


/**
 * @brief			Função passa a key (neste caso do tipo long) de um nodo da nossa estrutura MYLIST para lista de longs dos professores.
 * @param			LList cuja key será passadas.
 * @param			LONG_list onde serão guardadas as keys.
 * @param			Índice onde será inserida a key.
*/
static void my_tolonglist(void * llist, void * longlist, void * n, void * nulla) {

	LList cllist = (LList) llist;
	LONG_list clonglist = (LONG_list) longlist;
	int * cn = (int *) n;

	set_list(clonglist, *cn, (long ) get_key_box(cllist));
	(*cn)--;
}

/**
 * @brief			Função que obtém os id's das N perguntas mais recentes cujo título contém uma dada palavra.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Palavra a ser procurada nos títulos.
 * @param			Número máximo de resultados N.
*/

LONG_list contains_word(TAD_community com, char* word, int N){
	MYLIST lista = init_MYLIST(NULL, NULL, NULL);
	trans_tree(com->posts_Date, &contains_word_arr, lista, word, NULL, NULL, 4, N);

	int n = get_NUM_ele(lista) - 1;

	LONG_list res = create_list(n + 1);

	trans_list(lista, &my_tolonglist, res, &n, NULL);
	//sort_list(res, &cmp_longs);

	free_MYLIST(lista);

	return res;
}



/**
 * @brief			Função que corre num nodo e verifica a existencia de uma tag.
 * @param			Apontador para a informação a filtar.
 * @param			Lista de posts com essa tag.
 * @param			Tag a verificar.
*/

static void filtraTags(void * data, void * result, void * tag){
	MYLIST resultado;
	STACKPOST * arr = (STACKPOST *) data;
	int existe = 0,i;
	long idp = -2;
	MYPOST post;
	if (data != NULL){
		int max = get_NUM_eleSTACKPOST(arr);
		for(i=0; i < max; i++){
			post = get_ele_index_STACKPOST(arr,i);
			existe = existeTag(post,tag);

			if (existe){
				getIdP(post,&idp);
					resultado =  *(MYLIST*)result;
				resultado = insere_list(resultado,idp,NULL);
				 *(MYLIST*)result = resultado;
			}

		}
	}
}


/*
static void filtraTags(void * data, void * result, void * tag){
	MYLIST resultado,r;
	long idp = -2;
	LList lista2;
	MYPOST post;
	if (data != NULL){
		r = (MYLIST)data;
		lista2 = getFirst_BOX(r	);
		while(lista2){
			post = (MYPOST)getElemente_LList(lista2);

			if (existeTag(post,tag)){
				getIdP(post,&idp);
				resultado =  *(MYLIST*)result;
				if(resultado){
				resultado = insere_list(resultado,(void*)idp,NULL);
				 *(MYLIST*)result = resultado;
				}
			}
			lista2 = getNext_LList(lista2);
		}
	}
}
*/

/**
 * @brief			Função que dado um intervalo de tempo retornar todas as perguntas contendo uma determinada tag.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Data inicial da procura
 * @param			Data final da procura
*/
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	MYDATE nbegin,nend;
 	nbegin = DatetoMYDATE(begin);
 	nend   = DatetoMYDATE(end);
	MYLIST result = init_MYLIST(NULL,NULL,NULL);
	all_nodes_With_Condition(com->posts_Date,nbegin,nend,&(filtraTags),&result, tag);
	free_MYdate(nbegin);
	free_MYdate(nend);

	LONG_list final= create_list(get_NUM_ele(result));
	LList lista2 = getFirst_BOX(result);
	int i=0;
	for(i=0;lista2;lista2=getNext_LList(lista2),i++){
		set_list(final,i,(long)get_key_box(lista2));
	}

	free_MYLIST(result);
	return final;
}

/**
 * @brief			Função que dado 2 users retorna as N perguntas em que ambos participaram.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			ID1
 * @param			ID2
 * @param			Numero maximo de N
*/
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	MYUSER user1 = search_USER(com->users,id1);
	MYUSER user2 = search_USER(com->users,id2);
	STACKPOST lista1 = getMYLISTuser(user1);
	STACKPOST lista2 = getMYLISTuser(user2);
	int flag=N;

	MYPOST post1,post2;
	long pid1 = -3;
	long pid2 = -4;
	int type = 0;
	int max1 = get_NUM_eleSTACKPOST(lista1);
	int max2 = get_NUM_eleSTACKPOST(lista2);
	int i1,i2;

	MYLIST result = init_MYLIST(&(compare_MYDATE_LIST),&(free_MYdate),NULL);//&(free_MYdate),&(free));

	MYDATE data = NULL;


	for (i1 = 0; i1<max1 && flag; i1++){
		post1 = get_ele_index_STACKPOST(lista1,i1);
		getPostTypeIdP(post1,&type);
		if(type == 2)
			getPIdP(post1,&pid1);
		else if(type == 1)
			getIdP(post1,&pid1);
		else
			break;

		for (i2 = 0; i2<max2; i2++){
			post2 = get_ele_index_STACKPOST(lista2,i2);
			getPostTypeIdP(post2,&type);

			if(type == 2)
				getPIdP(post2,&pid2);
			else if(type == 1)
				getIdP(post2,&pid2);
			else
				break;

				if(pid1==pid2){
					if (type == 2)
						post2 = search_POSTID(com->posts_Id,pid2);

					getDateP(post2,&data);
					result = insere_list(result,data,(void*)pid2);

					flag--;
					break;
				}




		}
	}

	if (get_NUM_ele(result) == 0){
		free_MYLIST(result);
		return NULL;
	}
	LONG_list final= create_list(N-flag);
	printf("%d\n",(N-flag) );
	LList lista3 = getFirst_BOX(result);
	int i=0;
	for(i=0;i < N-flag;lista3=getNext_LList(lista3),i++)
		set_list(final,i,(long)getElemente_LList(lista3));

	free_MYLIST(result);
	return final;

}



//++++++++++++++++++++++++++++++++++++++++++++++QUERY 11+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



/**
 * @brief			Função auxiliar à query 11 que será aplicada a cada nodo da lista de posts em cada nodo da árvore organizada por datas, durante a travessia.
 * @param			Nodo atual.
 * @param			Lista onde são armazenados resultados.
 * @param			Array dos N users com maior reputação.
 * @param			Número N (tamanho do array de users).
*/
static void most_used_best_rep_node(void * vpost, void * res, void * users, void * N){
	if(vpost == NULL)
		return;

	MYPOST post = (MYPOST) vpost;
	int i;												// se não for
	getPostTypeIdP(post, &i);							// uma pergunta
	if(i != 1)											// então
		return;											// retornar

	long id;
	int n = *((int *) N) ;
	getOwnerIdP(post, &id);
	for(i = 0; i < n; i++) {							//se o autor
		if(id == ((long *) users)[i] )					//não é um dos
			break;										//com mais
		if(i == n - 1)									//reputação
			return;										//retornar
	}


	char ** tags;
	getTagsP(post, &tags);
	int * occ;

	for(i = 0; tags[i]; i++)
		if((occ = (int *) search_list_data((MYLIST) res, tags[i])) != NULL)		//se a tag já foi encontrada
			(*occ)++;															//incrementar número de ocorrências
		else																	//caso contrário,
			insere_list((MYLIST) res, (void *) mystrdup(tags[i]), (void *) 1);	//inserir tag na lista das encontradas


	free_StringArray(tags);

}

/**
 * @brief			Função auxiliar à query 11 que será aplicada a cada nodo da árvore de posts organizado por datas, durante a travessia.
 * @param			Array de posts nesse nodo.
 * @param			Lista onde são armazenados resultados.
 * @param			Array dos N users com maior reputação.
 * @param			Número N (tamanho do array de users).
*/
static void most_used_best_rep_arr(void * arr, void * res, void * users, void * n){
	if(arr == NULL)
		return;

	trans_arr(arr, &most_used_best_rep_node, res, users, n);
}


/**
 * @brief			Função passa os dados (do tipo int neste caso) da nossa estrutura MYLIST para um array de longs.
 * @param			LList cujos dados serão passados.
 * @param			Array de longs para onde será passados os dados.
 * @param			Índice onde será colocados os dados.
*/
static void my_data_int_toarray(void * llist, void * longs, void * n, void * nulla) {

	LList cllist = (LList) llist;
	long * clongs = (long *) longs;
	int * cn = (int *) n;

	int occ = (int) getElemente_LList(cllist);
	clongs[*cn] = (long ) occ;
	(*cn)++;
}

/**
 * @brief			Função que obtém o número de ocorrencias das N tags mais usadas num dado período de tempo pelos N users com maior reputação.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Número máximo de tags.
 * @param			Início do período de tempo.
 * @param			Final do período de tempo.
*/
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	MYLIST lista = init_MYLIST(&not_strcmp, &free, NULL);						//criar lista para tags encontradas
	MYDATE mybegin = DatetoMYDATE(begin);										//transformar Date no nosso tipo
	MYDATE myend = DatetoMYDATE(end);											// de dados MYDATE

	long * users = n_users_with_more_rep(com, N);								//preencher array com N
																				//users com  maior reputação

	trans_tree(com->posts_Date, &most_used_best_rep_arr, lista, users, mybegin, myend, 2, N); 	//travessia inorder
																								//na árvore de posts
																								//ordenados por data
																								//aplicando a função
																								//most_used_best_rep_list

	free_MYdate(mybegin);
	free_MYdate(myend);

	int size = get_NUM_ele(lista), i = 0;										//transformar a lista de tags encontradas
	long arr[size];																//num array com as respetivas ocorrencias
	trans_list(lista, &my_data_int_toarray, arr, &i, NULL);						//percorrendo a lista e aplicando a
	 																				//função my_data_int_toarray
	qsort(arr, size, sizeof(long), &cmp_longs);									//ordenar o array inversamente

	free_MYLIST(lista);

	if(size > N)																//determinar o número
		size = N;																//de elementos a retornar

	LONG_list res = create_list(size);											//passar os elementos do array
	for(i = 0; i < size; i++)													//para a LONG_list
		set_list(res, i, arr[i]);												//a retornar

	return res;
}
