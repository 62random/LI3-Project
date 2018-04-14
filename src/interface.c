#include "interface.h"

#define MAX_DUMP_PATH_SIZE 300

struct TCD_community {
	TREE users;
	TREE posts_Date;
	TREE posts_Id;
	HEAP num_posts;
	STACK pre_posts;
};


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
 * @brief			Função adiciona a informação da data de um nodo MYLIST numa heap.
 * @param			Apontador para a data do nodo.
 * @param			Apontador para a heap.
*/


static void postList_to_HEAP_score(void * data,void * dataaux){
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
 * @brief			Função que dado um intervalo de tempo calcula os N posts com melhor score.
 * @param			Número de posts a calcular.
 * @param			Data do começo do intervalo.
 * @param			Data do fim do intervalo.
*/

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	HEAP h = initHEAP(NUM_nodes(com->posts_Id));
	LONG_list l = create_list(N);
	all_nodes_TREE(com->posts_Date,&postList_to_HEAP_score,&h);

	int i;
	long key,data;
	/*
	for(i=0; i < N; i++){
		h = pop(h,&key,&data);
		printf("%ld\n",key);// tem que sair é só para testar.
		//set_list(l,i,data);
	}*/
	/*
	i = 0;
	while(get_NUM_eleHEAP(h) > 0 && i < 100){
		h = pop(h,&key,&data);
		printf("%ld\n",key);
		i++;
	}
	freeMYHEAP(h);*/
	printf("%d\n", teste_heap(h));

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
			scoreatual =(scr * 0.45 + rep * 0.25 + scr * 0.2 + comt * 0.1);
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
				resultado =  (MYLIST)result;
				resultado = insere_list(resultado,&idp,NULL);
				result = resultado;
			}
			lista2 = getNext_LList(lista2);
		}
	}
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
