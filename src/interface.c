#include "interface.h"

#define MAX_DUMP_PATH_SIZE 300

struct TCD_community {
	TREE users;
	TREE posts_Date;
	TREE posts_Id;
	HEAP num_posts;
	STACK pre_posts;
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
	HEAP h = *(HEAP *) dataaux;
	MYUSER user = (MYUSER) data;

	long n_post = get_NUM_ele(getMYLISTuser(user));
	h = insereHEAP(h,n_post,getIdMYUSER(user));
	*(HEAP*) dataaux = h;
}

/**
 * @brief			Função adiciona a informação da data de um nodo MYLIST numa heap para scores.
 * @param			Apontador para a data do nodo.
 * @param			Apontador para a heap.
*/


static void postList_to_HEAP_score(void * data,void * dataaux,void * lal){
	HEAP h = *(HEAP *) dataaux;
	MYLIST l = (MYLIST) data;
	LList aux = getFirst_BOX(l);
	MYPOST post = NULL;
	int type = -1;
	int score = -1;
	long id = -1;

	while(aux){
		post = getElemente_LList(aux);
		if (post){
			getPostTypeIdP(post,&type);
			if (type == 2){
				getScoreP(post,&score);
				getIdP(post,&id);
				h = insereHEAP(h,score,id);
			}
		}
		aux = getNext_LList(aux);
	}
	*(HEAP*) dataaux = h;
}

/**
 * @brief			Função adiciona a informação da data de um nodo MYLIST numa heap para perguntas com mais respostas.
 * @param			Apontador para a data do nodo.
 * @param			Apontador para a heap.
*/

static void postList_to_HEAP_nresp(void * data,void * dataaux,void * lal){
	HEAP h = *(HEAP *) dataaux;
	MYLIST l = (MYLIST) data;
	LList aux = getFirst_BOX(l);
	MYPOST post = NULL;
	int type = -1;
	int n_resp = -1;
	long id = -1;

	while(aux){
		post = getElemente_LList(aux);
		if (post){
			getPostTypeIdP(post,&type);
			if (type == 1){
				getAnswersP(post,&n_resp);
				getIdP(post,&id);
				h = insereHEAP(h,n_resp,id);
			}
		}
		aux = getNext_LList(aux);
	}
	*(HEAP*) dataaux = h;
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

	all_nodes_With_Condition(com->posts_Date,b1,e1,&postList_to_HEAP_nresp,&h,NULL);

	int i;
	long key,data;
	for(i=0; i < N && (get_NUM_eleHEAP(h) > 0); i++){
		h = pop(h,&key,&data);
		set_list(l,i,data);
	}
	/*
	if (i < N){
		for(; i<N ;i++)
			set_list(l,i,-2);
	}*/

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
		h = pop(h,&key,&data);
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
	com->num_posts = initHEAP(NUM_nodes(users));
	com->pre_posts = NULL;
	all_nodes_TREE(users,&num_posts_na_HEAP,&com->num_posts);

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

	return com;
}

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
			com->num_posts = pop(com->num_posts,&key,&id);
			com->pre_posts = insereSTACK(com->pre_posts,id);
			set_list(l,i,id);
		}
	}
	return l;
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

/**
 * @brief			Função que corre num nodo e calcula se é resposta ou pergunta.
 * @param			Apontador para a informação a filtar.
 * @param			Número de perguntas.
 * @param			Número de respostas.
*/

static void filtraPerguntasRespostas(void * data, void * perguntas, void * respostas){
	MYLIST r;
	long aux;
	int type;
	LList lista2;
	MYPOST post;
	if (data != NULL){
		r = (MYLIST) data;
		lista2 = getFirst_BOX(r);
		while(lista2){
			post = (MYPOST) getElemente_LList(lista2);
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
			lista2 = getNext_LList(lista2);
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
	int aux = 0;
	long * posts;
	posts = getNposts(user,10,&aux);
	if(aux != 10){
		for(;aux < 10; aux++)
			posts[aux] = -1;
	}
	USER info = create_user(getBiography(user),posts);
	return info;
}

/**
 * @brief			Função que dado um id de um post devolve a resposta melhor cotada desse post.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Id do post
*/
long better_answer(TAD_community com, long id){
		MYLIST respostas;
		MYUSER men;
		long user;
		int scr,rep,comt;
		int scoreatual,scoremax;
		scr=rep=comt=scoremax=scoreatual=0;
		long	 id2 = -2;
		int type;
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

		getFilhosP(post,&respostas);
		for (aux = getFirst_BOX(respostas); aux; aux=getNext_LList(aux)){
			post = (MYPOST)getElemente_LList(aux);
			getScoreP(post,&scr);
			getCommentsP(post,&scr);
			getOwnerIdP(post,&user);
			men = search_USER(com->users,user);
			rep = getREPMYUSER(men);
			scoreatual =(scr * 0.65 + rep * 0.25  + comt * 0.1);
			if (scoreatual > scoremax){
				scoremax = scoreatual;
				getIdP(post,&id2);
				printf("score = %d ; post = %ld\n",scoreatual,id2 );
			}

		}
		return id2;

}
/**
 * @brief			Função que corre num nodo e verifica a existencia de uma tag.
 * @param			Apontador para a informação a filtar.
 * @param			Lista de posts com essa tag.
 * @param			Tag a verificar.
*/

static void filtraTags(void * data, void * result, void * tag){
	MYLIST resultado,r;
	int existe = 0;
	long idp = -2;
	LList lista2;
	MYPOST post;
	if (data != NULL){
		r = (MYLIST)data;
		lista2 = getFirst_BOX(r	);
		while(lista2){
			post = (MYPOST)getElemente_LList(lista2);
			existe = existeTag(post,tag);

			if (existe){
				getIdP(post,&idp);
				printf("%ld\n",idp );
				resultado =  *(MYLIST*)result;
				resultado = insere_list(resultado,&idp,NULL);
				 *(MYLIST*)result = resultado;
			}
			lista2 = getNext_LList(lista2);
		}
	}
}



/**
 * @brief			Função a aplicar aos posts a ser visitados na travessia, auxiliar á query 8.
 * @param			Post a ser visitado.
 * @param			Lista onde serão guardados os id's dos posts relevantes.
 * @param			Palavra a ser procurada nos títulos.
 * @param			Número máximo de resultados N.
*/
void contains_word_node(void * listbox, void * lista, void * word, void * n){
	if(listbox == NULL || *((int *) n) <= 0)
		return;

	MYPOST cpost = getElemente_LList((LList) listbox);
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

}


/**
 * @brief			Função a aplicar à lista de posts efetuados no mesmo dia, auxiliar á query 8.
 * @param			Lista onde estão armazenados os ids de posts de resposta à query.
 * @param			Número máximo de resultados N.
 * @param			Palavra a ser procurada nos títulos.
 * @param			Número máximo de resultados N.
*/
void contains_word_list(void * lista, void * res, void * word, void * n){
	if(lista == NULL)
		return;

	MYLIST clista = (MYLIST) lista;
	MYLIST cres = (MYLIST) res;
	trans_list(clista, &contains_word_node, cres, word, n);
}

/**
 * @brief			Função que obtém os id's das N perguntas mais recentes cujo título contém uma dada palavra.
 * @param			Estrutura que guarda as outras estruturas.
 * @param			Palavra a ser procurada nos títulos.
 * @param			Número máximo de resultados N.
*/
LONG_list contains_word(TAD_community com, char* word, int N){
	MYLIST lista = init_MYLIST(NULL, &free, NULL);
	trans_tree(com->posts_Date, &contains_word_list, lista, word, 4, N);

	int n = get_NUM_ele(lista) - 1;

	LONG_list res = create_list(n + 1);

	trans_list(lista, &my_tolonglist, res, &n, NULL);


	return res;
}


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
	all_nodes_With_Condition(com->posts_Date,nbegin,nend,&(filtraTags),result, tag);
	free_MYdate(nbegin);
	free_MYdate(nend);

	LONG_list final= create_list(get_NUM_ele(result));
	LList lista2 = getFirst_BOX(result);
	int i=0;
	for(i=0;lista2;lista2=getNext_LList(lista2),i++)
		set_list(final,i,(long)get_key_box(lista2));

	free_MYLIST(result);
	return final;
}
