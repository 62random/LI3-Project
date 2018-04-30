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
	GHashTable * tags;
};

//++++++++++++++++++++++++++++++++++++++++++++++Init+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função inicializa a estrutura da comunidade.
*/


TAD_community init(){
	TAD_community aux = malloc(sizeof(struct TCD_community));
	return aux;
}

//++++++++++++++++++++++++++++++++++++++++++++++Load+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função adiciona a informação da data de um nodo MYUSER numa heap.
 * @param	data	Apontador para a data do nodo.
 * @param	dataaux	Apontador para a heap.
*/


static void num_posts_na_HEAP(void * data,void * dataaux){
	HEAP h = (HEAP) dataaux;
	MYUSER user = (MYUSER) data;

	STACKPOST st = getMYLISTuser(user);
	long n_post = getCounter1_STACKPOST(st) + getCounter2_STACKPOST(st);
	insereHEAP(h,n_post,getIdMYUSER(user));
}


/**
 * @brief			Função adiciona a informação da data de um nodo MYUSER numa heap para reputação.
 * @param	data	Apontador para a data do nodo.
 * @param	dataaux	Apontador para a heap.
*/

static void num_rep_na_HEAP(void * data,void * dataaux){
	HEAP h = (HEAP) dataaux;
	MYUSER user = (MYUSER) data;

	insereHEAP(h,getREPMYUSER(user),getIdMYUSER(user));
}

/**
 * @brief			Função ordena os posts de um user.
 * @param	data1	Apontador para o user.
*/

static void ordenaMYUSER_ALL_NODES(void * data1,void * data2){
	MYUSER use = (MYUSER) data1;
	if (use){
		order_STACKPOST(getMYLISTuser(use),&ordenaPOST_MYUSER);
	}
}


/**
 * @brief				Função dá load aos ficheiros xml.
 * @param	com			Estrutura que guarda as outras estruturas.
 * @param	dump_path	String com a diretoria onde se encontram os ficheiros.
*/

TAD_community load(TAD_community com, char * dump_path){
	char path [MAX_DUMP_PATH_SIZE];
	TREE users,postsDate = NULL,posts_ID = NULL;

	sprintf(path,"%s/Users.xml",dump_path);
	users = createMYUSERS_TREE(path);

	sprintf(path,"%s/Posts.xml",dump_path);
	createMYPOST_TREES(path, &posts_ID, &postsDate, users);

	sprintf(path,"%s/Tags.xml",dump_path);
	com->tags = createMYTAGS_HASH(path);

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

//++++++++++++++++++++++++++++++++++++++++++++++QUERY 1+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função retorna a informacao de um post.
 * @param	com		Estrutura que guarda as outras estruturas.
 * @param	id		Id do post
*/
STR_pair info_from_post(TAD_community com, long id){
	char * title = NULL;
	char * user = NULL;
	STR_pair result = NULL;

	MYPOST post = search_POSTID(com->posts_Id,id);

	if(!post){
		return result;
	}


	if(getPostTypeIdP(post) == 2){ // resposta
		freepost(post);
		post = search_POSTID(com->posts_Id, getPIdP(post)); // se for uma respota vai buscar o seu pai( sua pergunta )
	}

	title = getTitleP(post);
	MYUSER us = search_USER(com->users, getOwnerIdP(post));
	user = getUsername(us);
	result = create_str_pair(title,user);

	freeMYUSER(us);
	freepost(post);

	free(user);
	free(title);

	return result;


}

//++++++++++++++++++++++++++++++++++++++++++++++QUERY 2+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função que calcula os N utilizadores com mais posts.
 * @param	com		Estrutura que guarda as outras estruturas.
 * @param	N		Número de jogadores.
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
		for(; i < N && get_NUM_eleHEAP(com->num_posts) > 0; i++){
			pop(com->num_posts,&key,&id);
			com->pre_posts = insereSTACK(com->pre_posts,id);
			set_list(l,i,id);
		}
		if (i < N){
			for(; i < N; i++)
				set_list(l,i,-2);
		}

	}
	return l;
}

//++++++++++++++++++++++++++++++++++++++++++++++QUERY 3+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief				Função que corre num nodo e calcula se é resposta ou pergunta.
 * @param	data		Apontador para a informação a filtar.
 * @param	perguntas	Número de perguntas.
 * @param	respostas	Número de respostas.
*/

static void filtraPerguntasRespostas(void * data, void * perguntas, void * respostas){

	STACKPOST arr = (STACKPOST) data;
	if (data != NULL){ //p->1 r->2
		*(long *)perguntas += getCounter1_STACKPOST(arr);
		*(long *)respostas += getCounter2_STACKPOST(arr);
	}
}

/**
 * @brief			Função que dado um intervalo de tempo obtem o numero total de perguntas e respostas.
 * @param	com		Estrutura que guarda as outras estruturas.
 * @param	being	Data inicial da procura
 * @param	end		Data final da procura
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

//++++++++++++++++++++++++++++++++++++++++++++++QUERY 4+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função que corre num nodo e verifica a existencia de uma tag.
 * @param	data	Apontador para a informação a filtar.
 * @param	result	Lista de posts com essa tag.
 * @param	tag		Tag a verificar.
*/

static void filtraTags(void * data, void * result, void * tag){
	STACK resultado;
	STACKPOST arr = (STACKPOST) data;
	int existe = 0,i;
	MYPOST post;
	if (data != NULL){
		int max = get_NUM_eleSTACKPOST(arr);
		for(i=0; i < max; i++){
			post = get_ele_index_STACKPOST(arr,i);
			if (getPostTypeIdP(post) == 1){
				existe = existeTag(post,tag);

				if (existe){
					resultado =  *(STACK*)result;
					resultado = insereSTACK(resultado, getIdP(post));
					*(STACK*) result = resultado;
				}
			}
		}
	}
}



/**
 * @brief			Função que dado um intervalo de tempo retornar todas as perguntas contendo uma determinada tag.
 * @param	com		Estrutura que guarda as outras estruturas.
 * @param	tag		Tag.
 * @param	begin	Data inicial da procura.
 * @param	end		Data final da procura.
*/
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	MYDATE nbegin,nend;
 	nbegin = DatetoMYDATE(begin);
 	nend   = DatetoMYDATE(end);
	STACK result = initSTACK(1);

	all_nodes_With_Condition(com->posts_Date,nbegin,nend,&(filtraTags),&result, tag);
	free_MYdate(nbegin);
	free_MYdate(nend);

	LONG_list final= create_list(get_NUM_eleSTACK(result));

	int i=0;
	int c;
	int max = get_NUM_eleSTACK(result);
	for(i=(max-1), c = 0; i >= 0; i--, c++)
		set_list(final,c,(long)get_ELE_index(result,i));

	freeSTACK(result);
	return final;
}

//++++++++++++++++++++++++++++++++++++++++++++++QUERY 5+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função que dado um id de um user devolve informacao sobre este mesmo.
 * @param	com		Estrutura que guarda as outras estruturas.
 * @param	id		Id do post.
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
	char* aux2 = getBiography(user);
	USER info = create_user(aux2,posts);// leak mem
	freeMYUSER(user);
	free(aux2);
	free(posts);
	return info;

}

//++++++++++++++++++++++++++++++++++++++++++++++QUERY 6+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função adiciona a informação da data de um nodo STACKPOST numa heap para scores.
 * @param	data	Apontador para a data do nodo.
 * @param	dataaux	Apontador para a heap.
*/


static void postList_to_HEAP_score(void * data,void * dataaux,void * lal){
	HEAP h = (HEAP) dataaux;
	STACKPOST arr = (STACKPOST) data;
	MYPOST post = NULL;
	int i;
	long tam = get_NUM_eleSTACKPOST(arr);

	for(i=0; i < tam; i++){
		post = get_ele_index_STACKPOST(arr,i);
		if (post)
			if (getPostTypeIdP(post) == 2)
				insereHEAP(h, getScoreP(post), getIdP(post));
	}
}

/**
 * @brief			Função que dado um intervalo de tempo calcula os N posts com melhor score.
 * @param	com		Apontador para a base de dados.
 * @param	N		Número de respostas.
 * @param	begin	Data do começo do intervalo.
 * @param	end		Data do fim do intervalo.
*/

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	HEAP h = initHEAP(NUM_nodes(com->posts_Id));
	LONG_list l = create_list(N);
	MYDATE b1 = DatetoMYDATE(begin);
	MYDATE e1 = DatetoMYDATE(end);
	all_nodes_With_Condition(com->posts_Date,b1,e1,&postList_to_HEAP_score,h,NULL);

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

//++++++++++++++++++++++++++++++++++++++++++++++QUERY 7+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
- * @brief			Função que conta o número de post num intervalo.
- * @param	st		Apontador para a stack de posts.
- * @param	begin	Apontador para o inicio do intervalo.
- * @param	end		Apontador para o fim do intervalo.
*/

static int how_many_post_interval(STACKPOST st, MYDATE begin, MYDATE end){
	long i, tam = get_NUM_eleSTACKPOST(st);
	int count = 0,r1,r2;
	MYDATE pdate;
	MYPOST post;
	if (st){
		for(i=0; i < tam; i++){
			post = get_ele_index_STACKPOST(st,i);
			pdate = getDateP(post);

			if (getPostTypeIdP(post) == 2){
				r1 = compare_MYDATE_AVL(begin,pdate);
				r2 = compare_MYDATE_AVL(end,pdate);
				if (r1 >= 0 && r2 <= 0)
					count++;
			}
			free_MYdate(pdate);
		}
	}
	return count;
}


/**
 * @brief			Função adiciona a informação da data de um nodo STACKPOST numa heap para perguntas com mais respostas.
 * @param	data	Apontador para a data do nodo.
 * @param	dataaux	Apontador para a heap.
 * @param	begin	Apontador para a inicio do intervalo.
 * @param	fim		Apontador para o fim do intervalo.
*/

static void postList_to_HEAP_nresp(void * data,void * dataaux,void * begin, void * end){
	HEAP h = (HEAP) dataaux;
	STACKPOST arr = (STACKPOST) data;
	MYPOST post = NULL;
	int i;
	long tam = get_NUM_eleSTACKPOST(arr);

	for(i=0; i < tam; i++){
		post = get_ele_index_STACKPOST(arr,i);
		if (post)
			if (getPostTypeIdP(post) == 1)
				insereHEAP(h, how_many_post_interval(getFilhosP(post),(MYDATE) begin,(MYDATE) end), getIdP(post));
				//insereHEAP(h,getAnswersP(post),getIdP(post));
	}
}

/**
 * @brief			Função que dado um intervalo de tempo calcula as N perguntas com mais respostas.
 * @param	com		Apontador para a base de dados.
 * @param	N		Número de posts a calcular.
 * @param	begin	Data do começo do intervalo.
 * @param	end		Data do fim do intervalo.
*/

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	HEAP h = initHEAP(NUM_nodes(com->posts_Id));
	LONG_list l = create_list(N);
	MYDATE b1 = DatetoMYDATE(begin);
	MYDATE e1 = DatetoMYDATE(end);

	trans_tree(com->posts_Date,&postList_to_HEAP_nresp,h,NULL,begin,end,5,0);

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

//++++++++++++++++++++++++++++++++++++++++++++++QUERY 8+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função a aplicar aos posts a ser visitados na travessia, auxiliar á query 8.
 * @param	post	Post a ser visitado.
 * @param	arr 	Array onde serão guardados os id's dos posts relevantes.
 * @param	word	Palavra a ser procurada nos títulos.
 * @param	n		Número máximo de resultados N.
*/

static void contains_word_node(void * post, void * arr, void * word, void * n, void * nulla){
	if(post == NULL || *((int *) n) <= 0)
		return;

	MYPOST cpost = (MYPOST) post;
										// se não for uma pergunta
	if(getPostTypeIdP(cpost) != 1)		// então
		return;							// retornar

	STACK carr = (STACK) arr;
	char * cword = (char *) word, * title;

	title = getTitleP(cpost);
	if(strstr(title, cword) != NULL) {	// se o titulo contem a palavra
		insereSTACK(carr, getIdP(cpost));
		int * cn = (int *) n;
		(*cn)--;
	}

	free(title);

}


/**
 * @brief			Função a aplicar ao array de posts efetuados no mesmo dia, auxiliar á query 8.
 * @param	arr		Array onde estão armazenados os ids de posts efetuados no mesmo dia.
 * @param	res		Array onde estão a ser guardados os ids dos posts de resposta à query.
 * @param	word	Palavra a ser procurada nos títulos.
 * @param	n		Número máximo de resultados N.
*/

static void contains_word_arr(void * arr, void * res, void * word, void * n){
	if(arr == NULL)
		return;

	trans_arr(arr, &contains_word_node, res, word, n, NULL);
}


/**
 * @brief				Função passa a key (neste caso do tipo long) de um nodo da nossa estrutura MYLIST para lista de longs dos professores.
 * @param	num			LList cuja key será passadas.
 * @param	longlist	LONG_list onde serão guardadas as keys.
 * @param	n			Índice onde será inserida a key.
*/
static void stack_tolonglist(long num, void * longlist, void * n, void * nulla) {

	LONG_list clonglist = (LONG_list) longlist;
	int * cn = (int *) n;

	set_list(clonglist, *cn, num);
	(*cn)--;
}

/**
 * @brief			Função que obtém os id's das N perguntas mais recentes cujo título contém uma dada palavra.
 * @param	com		Estrutura que guarda as outras estruturas.
 * @param	word	Palavra a ser procurada nos títulos.
 * @param	N		Número máximo de resultados N.
*/

LONG_list contains_word(TAD_community com, char* word, int N){
	STACK arr = initSTACK(1);
	trans_tree(com->posts_Date, &contains_word_arr, arr, word, NULL, NULL, 4, N);
	int n = get_NUM_eleSTACK(arr) - 1;

	LONG_list res = create_list(n + 1);

	trans_stack(arr, &stack_tolonglist, res, &n, NULL);
	if(res)
		sort_list(res, &cmp_longs);

	freeSTACK(arr);

	return res;
}

//++++++++++++++++++++++++++++++++++++++++++++++QUERY 9+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função que compara duas keys e diz que os seus valores são iguais.
 * @param data1		Apontador para a primeira key.
 * @param data2		Apontador para a segunda key.
*/

static int hash_long_equals(const void * data1, const void * data2){
	long id1 = *(long *) data1;
	long id2 = *(long *) data2;
	return (id1 == id2);
}

/**
 * @brief			Função que insere posts uma hashtable.
 * @param com		Apontador para estrutura da comunidade.
 * @param table		Apontador para a hashtable.
 * @param l_aux		Lista de posts.
 * @param size_f	Tamanho máximo da lista.
*/


static void preenche_hash_table(TAD_community com, GHashTable * table, STACKPOST l_aux, int size_f){
	MYPOST novo,novo2,post;
	long * id;

	int i;

	for(i = 0; i < size_f; i++){					//criar a hash_table com o posts do user com menos posts.
		post = get_ele_index_STACKPOST(l_aux,i);
		if (getPostTypeIdP(post) == 1){
			novo = clone_MYPOST_NODEEP(post);
			id = malloc(sizeof(long));
			*id = getIdP(post);
			g_hash_table_insert(table,id,novo);
		}
		else if (getPostTypeIdP(post) == 2){
			novo2 = search_POSTID(com->posts_Id,getPIdP(post)); // procura o pai
			if (novo2){
				novo = clone_MYPOST_NODEEP(novo2); //cria clone simples do pai
				freepost(novo2);// free clone complexo
				id = malloc(sizeof(long));
				*id = getIdP(novo);
				g_hash_table_insert(table,id,novo); // insere
			}
		}
	}
}

/**
 * @brief			Função que retira posts de uma hashtable.
 * @param com		Apontador para estrutura da comunidade.
 * @param table		Apontador para a hashtable.
 * @param queue		Array para guardar os posts.
 * @param l_aux2	Lista de comparação.
 * @param size_f	Tamanho máximo da lista.
*/

static void preenche_stackpost(TAD_community com,GHashTable * table , STACKPOST queue , STACKPOST l_aux2 , int size2){
	MYPOST post,novo;
	int i;
	long idaux;

	for(i = 0; i < size2; i++){
		post = get_ele_index_STACKPOST(l_aux2,i);
		if (getPostTypeIdP(post) == 1){
			idaux = getIdP(post);
			novo = (MYPOST) g_hash_table_lookup(table,&idaux);
			if (novo){
				insere_sem_rep_STACKPOST(queue,novo);
			}
		}
		else if (getPostTypeIdP(post) == 2){
			novo = search_POSTID(com->posts_Id,getPIdP(post));
			if (novo){
					idaux = getIdP(novo);
					freepost(novo);
					novo = g_hash_table_lookup(table,&idaux);
					if (novo){
						insere_sem_rep_STACKPOST(queue,novo);
					}
				}
			}
	}
}

/**
 * @brief			Função que dado 2 users retorna as N perguntas em que ambos participaram.
 * @param com		Estrutura que guarda as outras estruturas.
 * @param id1		ID1
 * @param id2		ID2
 * @param N			Número máximo de N
*/

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	MYUSER user1 = search_USER(com->users,id1);
	MYUSER user2 = search_USER(com->users,id2);
	STACKPOST lista1 = getMYLISTuser(user1);// são clones
	STACKPOST lista2 = getMYLISTuser(user2);// são clones


	int size1, size2, size_f,i;
	size1 = get_NUM_eleSTACKPOST(lista1);
	size2 = get_NUM_eleSTACKPOST(lista2);


	if ((!user1) || (!user2) || size1 == 0 || size2 == 0 || N == 0){
		freeMYUSER(user1);
		freeMYUSER(user2);
		return NULL;
	}

	GHashTable * table = g_hash_table_new_full(&g_int_hash,&hash_long_equals,&free,&free);
	LONG_list l = create_list(N);

	STACKPOST l_aux = size1 < size2 ? lista1 : lista2;
	STACKPOST l_aux2 = size1 < size2 ? lista2 : lista1;

	size_f = size1 < size2 ? size1 : size2;
	size2 = size1 < size2 ? size2 : size1;

	preenche_hash_table(com,table,l_aux,size_f);

	STACKPOST queue = initSTACKPOST(size_f+1);


	preenche_stackpost(com,table,queue,l_aux2,size2);
	order_STACKPOST(queue,&ordenaPOST_MYUSER);

	MYPOST post;

	for(i = 0; i < get_NUM_eleSTACKPOST(queue) &&  i < N; i++){
		post = get_ele_index_STACKPOST(queue,i);
		set_list(l,i,getIdP(post));
	}
	if (i < N){
		for(; i < N; i++)
			set_list(l,i,-2);
	}

	freeMYUSER(user1);
	freeMYUSER(user2);
	g_hash_table_destroy(table);
	freeSTACKPOST_SEM_CLONE(queue);


	return l;
}

/*
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

	MYLIST result = init_MYLIST(&(compare_MYDATE_LIST),&(free_MYdate),NULL);

	for (i1 = 0; i1<max1 ; i1++){
		post1 = get_ele_index_STACKPOST(lista1,i1);
		type = getPostTypeIdP(post1);
		if(type == 2)
			pid1 = getPIdP(post1);
		else if(type == 1)
			pid1 = getIdP(post1);
		else
			continue;

		for (i2 = 0; i2<max2; i2++){
			post2 = get_ele_index_STACKPOST(lista2,i2);
			type = getPostTypeIdP(post2);

			if(type == 2)
				pid2 = getPIdP(post2);
			else if(type == 1)
				pid2 = getIdP(post2);
			else
				continue;

				if(pid1 == pid2){
					if (type == 2){
						post2 = search_POSTID(com->posts_Id,pid2);
						if(!post2){
							printf("post sem coiso\n");
							break;
						}
						result = insere_list(result, getDateP(post2), (void*) pid2);
						freepost(post2);
					}
					else
						result = insere_list(result, getDateP(post2), (void*) pid2);

					flag--;
					break;
				}




		}
	}
	int max = count_ELE_MYLIST(result);
	if (max == 0){
		freeMYUSER(user1);
		freeMYUSER(user2);
		free_MYLIST(result);
		return NULL;
	}
	LONG_list final= create_list(max);
	LList lista3 = getFirst_BOX(result);
	int i=0;
	for(i=0;i<max ;lista3=getNext_LList(lista3),i++)
		set_list(final,i,(long)getElemente_LList(lista3));

	freeMYUSER(user1);
	freeMYUSER(user2);

	free_MYLIST(result);
	return final;

}*/



//++++++++++++++++++++++++++++++++++++++++++++++QUERY 10+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * @brief			Função que dado um id de um post devolve a resposta melhor cotada desse post.
 * @param	com		Estrutura que guarda as outras estruturas.
 * @param	id		Id do post
*/
long better_answer(TAD_community com, long id){
		STACKPOST arr = NULL;
		MYUSER men;
		int scoreatual, scoremax;
		scoremax = scoreatual = 0;
		int n, i,result = -2;

		MYPOST pergunta = search_POSTID(com->posts_Id,id);
		MYPOST resposta = NULL;
		if (!pergunta){
			freepost(pergunta);
			printf("Post inexistente\n");
			return -3;
		}

		if(getPostTypeIdP(pergunta) != 1){
			freepost(pergunta);
			printf("Post não é uma pergunta\n");
			return -4;
		}

		arr = getFilhosP(pergunta);
		if(arr == NULL){
			freepost(pergunta);
			return -2;
		}
		n = get_NUM_eleSTACKPOST(arr);

		for(i = 0; i < n; i++){
			resposta = get_ele_index_STACKPOST(arr, i);
			men = search_USER(com->users, getOwnerIdP(resposta));
			scoreatual =(getScoreP(resposta) * 0.65 + getREPMYUSER(men) * 0.25  + getCommentsP(resposta) * 0.1);
			freeMYUSER(men);

			if (scoreatual > scoremax){
				scoremax = scoreatual;
				result = getIdP(resposta);
			}
		}
		freepost(pergunta);
		return result;

}





//++++++++++++++++++++++++++++++++++++++++++++++QUERY 11+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/**
 * @brief			Função que calcula os N utilizadores com melhor rep.
 * @param	com		Estrutura que guarda as outras estruturas.
 * @param	N		Número de jogadores.
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
		for(; i < N && (get_NUM_eleHEAP(com->rep_users) > 0); i++){
			pop(com->rep_users,&key,&id);
			com->pre_rep = insereSTACK(com->pre_rep,id);
			array[i] = get_ELE_index(com->pre_rep,i);
		}
		array[i] = -2;
	}

	return array;
}


/**
 * @brief				Função auxiliar à query 11 que será aplicada a cada nodo da lista de posts em cada nodo da árvore organizada por datas, durante a travessia.
 * @param vpost			Nodo atual.
 * @param vcom			Apontador para a comunidade (para podermos aceder à hash table das tags)
 * @param ocorrencias	Hash table criada para registar as ocorrencias de cada tag.
 * @param begin			Data de início do período de tempo da query11.
 * @param end			Data de fim do período de tempo da query11.
*/
static void most_used_best_rep_node(void * vpost, void * vcom, void * ocorrencias, void * begin, void * end){
	if(vpost == NULL)
		return;

	MYPOST post = (MYPOST) vpost;
	int i;

	if(getPostTypeIdP(post) != 1)
		return;
	MYDATE date = getDateP(post);
	int r1 = compare_MYDATE_AVL((MYDATE) begin,  date);
	int r2 = compare_MYDATE_AVL((MYDATE) end, date);
	free_MYdate(date);
	if(r1 < 0 || r2 > 0)
		return;

	char ** tags;
	tags = getTagsP(post);
	long * keyid;
	int * oc;
	TAD_community com = (TAD_community) vcom;

	for(i = 0; tags[i]; i++)
		if((keyid = g_hash_table_lookup(com->tags, tags[i])) != NULL){
			if((oc = g_hash_table_lookup(ocorrencias, keyid)) != NULL){
				(*oc)++;
			}
			else {
				oc = malloc(sizeof(int));
				(*oc) = 1;
				g_hash_table_insert(ocorrencias, keyid, oc);
			}
		}


	free_StringArray(tags);

}



/**
 * @brief			Funão compatível com a API do glib para inserir numa heap os dados da hashtable com as ocorrencias de cada tag.
 * @param key		Chave da entrada atual, ou seja, o id da tag.
 * @param value		Valor a entrada atual, ou seja, o número de ocorrencias da tag.
 * @param data		Apontador para a heap para a qual queremos passar a informação.
*/
void hash_to_heap(gpointer key, gpointer value, gpointer data) {
	HEAP heap = (HEAP) data;
	long ocorrencias, id;
	ocorrencias = *((int *) value);
	id = *((long *) key);
	insereHEAP(heap, ocorrencias, id);
}


/**
 * @brief			Função que obtém o número de ocorrencias das N tags mais usadas num dado período de tempo pelos N users com maior reputação.
 * @param	com		Estrutura que guarda as outras estruturas.
 * @param	N		Número máximo de tags.
 * @param	begin	Início do período de tempo.
 * @param	end		Final do período de tempo.
*/
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	GHashTable * ocorrencias = g_hash_table_new_full(&g_direct_hash,&g_direct_equal, NULL,&free);
	MYDATE mybegin = DatetoMYDATE(begin);										//transformar Date no nosso tipo
	MYDATE myend = DatetoMYDATE(end);											// de dados MYDATE

	long * users = n_users_with_more_rep(com, N);								//preencher array com N
	int i;																		//users com  maior reputação
	MYUSER user;
	STACKPOST posts;
	for(i = 0; i < N && users[i] != -2; i++){
		user = search_USER(com->users, users[i]);
		if(user) {
			posts = getMYLISTuser(user);
			trans_arr(posts, &most_used_best_rep_node, com, ocorrencias, mybegin, myend);
			freeMYUSER(user);
		}
	}

	free_MYdate(mybegin);
	free_MYdate(myend);

	int size = g_hash_table_size(ocorrencias);
	HEAP heap = initHEAP((long) size);

	g_hash_table_foreach(ocorrencias, &hash_to_heap, heap);


	if(size > N)
		size = N;
	LONG_list res = create_list(size);

	long id, oc;

	for(i = 0; i < size; i++) {
		pop(heap, &oc, &id);
		printf("Id:%ld->Oc:%ld\n",id,oc);
		set_list(res, i, id);
	}

	freeMYHEAP(heap);
	g_hash_table_destroy(ocorrencias);
	free(users);
	return res;
}

/**
 * @brief			Função que liberta a memória da estrutura.
 * @param	com		Estrutura que guarda as outras estruturas.
*/

TAD_community clean(TAD_community com){
	freeTreeUSER(com->users);

	freeTREE_AVL(com->posts_Id);
	freeTREE_AVL(com->posts_Date);
	freeSTACK(com->pre_posts);
	freeMYHEAP(com->num_posts);
	freeSTACK(com->pre_rep);
	freeMYHEAP(com->rep_users);

	freeHASH_TAGS(com->tags);

	return com;
}
