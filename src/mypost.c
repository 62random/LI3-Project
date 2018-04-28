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
	int  		type;
};

struct stackpost {
	long counter1;
	long counter2;
	long n_elem;
	long size;
	MYPOST * array;
};

// STACKPOST

/**
 * @brief			Função percorre um array e aplica a cada nodo uma função.
 * @param			Array a ser percorrido.
 * @param			Função a ser aplicada (cujo o primeiro argumento é o nodo a que ela é aplicada).
 * @param			Segundo argumento da função a ser aplicada.
 * @param			Terceiro argumento da função a ser aplicada.
 * @param			Quarto argumento da função a ser aplicada.

*/
void trans_arr(STACKPOST arr, void (*f_box)(void *, void *, void *, void *, void *), void * data1, void * data2, void * data3, void * data4){
	if(arr == NULL)
		return;

	for(int i = 0;i < arr->n_elem; i++)
		f_box((void *) arr->array[i],data1, data2, data3, data4);
}

/**
 * @brief				Função que calcula o valor da nova ordenação.
 * @param				MYPOST 1;
 * @param				MYPOST 2;
*/

int ordenaPOST_MYUSER(const void * data1, const void * data2){
	MYPOST a1 = (MYPOST) data1;
	MYPOST a2 = (MYPOST) data2;

	int x = compare_MYDATE_AVL(a1->cdate,a2->cdate);

	return x;
}

/**
 * @brief			Função que troca dois elementos do array.
 * @param			Array.
 * @param			Indice 1.
 * @param			Indice 2.
*/


static void swapMYPOST(MYPOST * array, long i, long d){
	MYPOST aux = array[i];

	array[i] = array[d];
	array[d] = aux;
}

/**
 * @brief			Função que executa uma partition num Array de MYPOST.
 * @param 			Array a partir.
 * @param			Número de elementos.
 * @param			Função de comparação.
*/

static long partition(MYPOST * v, long N, int (*f_compare)(MYPOST,MYPOST)){
	long i,j;
	for(i=0,j=0; i < N-1; i++){
		if (f_compare(v[i],v[N-1]) < 0)
			swapMYPOST(v,i,j++);
	}
	swapMYPOST(v,N-1,j);
	return j;
}

/**
 * @brief			Função que ordena um array com quicksort.
 * @param			Array a ordenar.
 * @param			Número de elementos.
 * @param			Função de comparação.
*/

static void quicksort(MYPOST * v, long N,void * func){
	long i;
	if (N > 1){
		i = partition(v,N,func);
		quicksort(v,i,func);
		quicksort(v+i+1,N-i-1,func);
	}
}


/**
 * @brief			Função que ordena uma stackpost.
 * @param			STACKPOST.
 * @param			Função de comparação.
*/

void order_STACKPOST(STACKPOST st, void * func){
	quicksort(st->array,st->n_elem,func);
}

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
	a->array = malloc(size*sizeof(struct mypost *));

	return a;
}

/**
 * @brief			Função que adiciona um valor ao counter2.
 * @param			STACKPOST.
 * @param 			Conter 2.
*/

void incCounter2_STACKPOST(STACKPOST st,long i){
	if (st){
		st->counter2 += i;
	}
}

/**
 * @brief			Função que adiciona um valor ao counter1.
 * @param			STACKPOST.
 * @param 			Conter 1.
*/

void incCounter1_STACKPOST(STACKPOST st,long i){
	if (st){
		st->counter1 += i;
	}
}

/**
 * @brief			Função que devolve o counter 1.
 * @param			STACKPOST.
*/

long getCounter1_STACKPOST(STACKPOST st){
	return (st) ? st->counter1 : 0;
}

/**
 * @brief			Função que devolve o counter 2.
 * @param			STACKPOST.
*/

long getCounter2_STACKPOST(STACKPOST st){
	return (st) ? st->counter2 : 0;
}

/**
 * @brief			Função que insere um elemento numa stackpost.
 * @param			STACKPOST.
 * @param			Post a inserir.
*/

void insereSTACKPOST(STACKPOST st, MYPOST post){
	long i;
	int type = 0;
	MYPOST * aux;
	if (st->n_elem >= st->size){
		st->size *= 2;
		aux = malloc(st->size*sizeof(struct mypost *));
		for(i=0; i < st->n_elem; i++)
			aux[i] = st->array[i];
		free(st->array);
		st->array = aux;
	}
	st->array[st->n_elem++] = post;
	type = getPostTypeIdP(post);
	if (type == 1){
		st->counter1 += 1;
	}
	else if (type == 2){
		st->counter2 += 1;
	}

}

/**
 * @brief			Função que insere um elemento sem repetidos numa stackpost.
 * @param			STACKPOST.
 * @param			Post a inserir.
*/

void insere_sem_rep_STACKPOST(STACKPOST st, MYPOST post){
	long i;
	MYPOST * aux;
	if (st->n_elem >= st->size){
		st->size *= 2;
		aux = malloc(st->size*sizeof(struct mypost *));
		for(i=0; i < st->n_elem; i++)
			aux[i] = st->array[i];
		free(st->array);
		st->array = aux;
	}
	for(i=0; i < st->n_elem ; i++){
		if (getIdP(post) == getIdP(st->array[i]))
			break;
	}
	if (i == st->n_elem)
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
 * @brief			Função que dá free a um clone stackpost.
 * @param			STACKPOST.
*/

void freeSTACKPOST_COM_CLONE(STACKPOST st){
	if (st){
		long i;
		for(i=0; i < st->n_elem; i++)
			freepost(st->array[i]);
		free(st->array);
		free(st);
	}
}
// end STACKPOST

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o Id de um post.
 * @param 			Apontador para a struct do post.
 */
long getIdP(MYPOST post){
  	return post ? post->id : -2;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que altera o Id de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo ID do post.
 */
static void setIdP(MYPOST post, long  id){
  post->id = id;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o TypeId de um post.
 * @param 			Apontador para a struct do post.
 */
int getPostTypeIdP(MYPOST post){
	return post ? post->typeid : 0;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o TypeId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo TypeId do post.
 */
static void setPostTypeIdP(MYPOST post, long  id){
  post->typeid = id;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que verifica se um post é clone ou não.
 * @param 			Apontador para a struct do post.
 */

int getTYPECLONEP(MYPOST post){
	return post ? post->type : 0;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o OwnerId de um post.
 * @param 			Apontador para a struct do post.
 */
long getOwnerIdP(MYPOST post){
  	return post ? post->ownerid : -2;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o OwnerId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo OwnerId do post.
 */
static void setOwnerIdP(MYPOST post, long  id){
	post->ownerid = id;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém a data de criação de um post.
 * @param 			Apontador para a struct do post.
 */
MYDATE getDateP(MYPOST post){
	if(post){
		MYDATE date;
		date = createMYDate(get_MYday(post->cdate),
							get_MYmonth(post->cdate),
					 		get_MYyear(post->cdate));
  		return date;
	}

	return NULL;
}


/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera a data de criação de um post.
 * @param 			Apontador para a struct do post.
 * @param			Nova data do post.
 */
static void setDateP(MYPOST post, MYDATE data){
	MYDATE date;

	date = createMYDate(get_MYday(data),
	get_MYmonth(data),
	get_MYyear(data));

  	post->cdate = date;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que inicializa a (nossa) representação de um post na memória.
 * @param 			Apontador para a struct do post.
 */
char * getOwnerNameP(MYPOST post){
		return post ? mystrdup(post->ownername) : NULL;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o OwnerName de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo OwnerName do post.
 */
static void setOwnerNameP(MYPOST post, char *  name){
	post->ownername = mystrdup(name);
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o título de um post.
 * @param 			Apontador para a struct do post.
 */
char * getTitleP(MYPOST post){
	return post ? mystrdup(post->title) : NULL;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o título de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo titulo do post.
 */
static void setTitleP(MYPOST post, char* title){
	post->title = mystrdup(title);
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém as tags de um post.
 * @param 			Apontador para a struct do post.
 */
char ** getTagsP(MYPOST post){
	if(post){
		if(post->tags == NULL)
			return NULL;

		int i ;
		char ** tags;

		for(i= 0; post->tags[i] != NULL; i++)
			;
			tags = malloc(sizeof(char *)*(i + 1));

		for(i= 0; post->tags[i] != NULL; i++){
			tags[i] = mystrdup(post->tags[i]);
		}


		tags[i] = NULL;
		return tags;
	}

	return NULL;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera a lista de tags de um post.
 * @param 			Apontador para a struct do post.
 * @param			Nova lista de tags do post.
 */
static void setTagsP(MYPOST post, char ** tags){
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
 */
int getAnswersP(MYPOST post){
	return post ? post->anscount : 0;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o numero de respostas de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo numero de respostas do post.
 */
static void setAnswersP(MYPOST post, int answer){
  	post->anscount=answer;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de comentarios de um post.
 * @param 			Apontador para a struct do post.
 */
int getCommentsP(MYPOST post){
		return post ? post->commcount : 0;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o numero de comentarios de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo comentarios de respostas do post.
 */
static void setCommentsP(MYPOST post, int comments){
  	post->commcount = comments;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o numero de favoritos de um post.
 * @param 			Apontador para a struct do post.
 */
int getFavsP(MYPOST post){
		return post ? post->favcount : 0;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o numero de favoritos de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo favoritos de respostas do post.
 */
static void setFavsP(MYPOST post, int fav){
  	post->favcount = fav;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o ParentId de um post.
 * @param 			Apontador para a struct do post.
 */
long getPIdP(MYPOST post){
  		return post ? post->parent_id : -2;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o ParentId de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo ParendId do post.
 */
static void setPIdP(MYPOST post, long  id){
  post->parent_id = id;
}

/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém o score de um post.
 * @param 			Apontador para a struct do post.
 */
int getScoreP(MYPOST post){
  		return post ? post->score : 0;
}

/**
 * @date 			27 Mar 2018
 * @brief 			Função que altera o score de um post.
 * @param 			Apontador para a struct do post.
 * @param			Novo score do post.
 */
static void setScoreP(MYPOST post, int  score){
  post->score=score;
}


/**
 * @date 			24 Mar 2018
 * @brief 			Função que obtém os filhos de um post.
 * @param 			Apontador para a struct do post.
 */

STACKPOST getFilhosP(MYPOST post){
		return post ? post->filhos : NULL;
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
 * @brief 			Função que inicializa a (nossa) representação de um post na memória.
 * @return 			Apontador para a struct do post.
 */
MYPOST createpost(int type) {
	MYPOST post = malloc(sizeof(struct mypost));
	post->ownername = NULL;
	post->tags 	= NULL;
	post->cdate	= NULL;
	post->title	= NULL;
	post->ownerid = -2;
	post->parent_id = -2;
	post->favcount	= 0;
	post->anscount	= 0;
	post->type = type;
	if (type)
		post->filhos = initSTACKPOST(1);
	else post->filhos = NULL;

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

	if (post->type == 1){

		if(post->title != NULL)
			free(post->title);

		if(post->ownername != NULL)
			free(post->ownername);

		free_StringArray(post->tags);
		free_MYdate(post->cdate);
		freeSTACKPOST_SEM_CLONE(post->filhos);
	}
	else {
		freeSTACKPOST_COM_CLONE(post->filhos);
	}

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
 * @brief				Função que produz o clone de um post sem profundidade.
 * @param				Apontador para o post.
*/

MYPOST clone_MYPOST_NODEEP(MYPOST post){
	MYPOST novo = createpost(0);
	novo->id = post->id;
	novo->typeid = post->typeid;
	novo->parent_id = post->parent_id;
	novo->cdate = post->cdate;
	novo->score = post->score;
	novo->ownerid = post->ownerid;
	novo->ownername = post->ownername;
	novo->title = post->title;
	novo->tags = post->tags;
	novo->anscount = post->anscount;
	novo->commcount = post->commcount;
	novo->favcount = post->favcount;

	return novo;
}

/**
 * @brief				Função que clona uma STACKPOST.
 * @param				Apontador para a stackpost.
*/


STACKPOST clone_STACKPOST(STACKPOST st){
	STACKPOST novo = initSTACKPOST(st->n_elem);
	novo->counter1 = st->counter1;
	novo->counter2 = st->counter2;
	novo->n_elem = st->n_elem;
	novo->size = st->n_elem;

	long i;
	MYPOST aux;
	for(i = 0; i < st->n_elem; i++){
		aux = clone_MYPOST_NODEEP(st->array[i]);
		novo->array[i] = aux;
	}

	return novo;
}

/**
 * @brief				Função que produz o clone de um post com profundidade.
 * @param				Apontador para o post.
*/

MYPOST clone_MYPOST_DEEP(MYPOST post){
	MYPOST novo = clone_MYPOST_NODEEP(post);
	novo->filhos = clone_STACKPOST(post->filhos);

	return novo;
}


/**
 * @brief				Função que procura um post pelo id na estrutura com clone.
 * @param				Id do post a procurar.
*/

MYPOST search_POSTID(TREE tree,long id){
	int valid;

	MYPOST post = search_AVL(tree, &id, &valid);
	if (valid)
		return clone_MYPOST_DEEP(post);
	return NULL;
}

/**
 * @brief				Função que procura um post pelo id na estrutura sem clone.
 * @param				Id do post a procurar.
*/

static MYPOST search_POSTID_internal(TREE tree,long id){
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
	int i = 0;
	printf("Ne:%ld\n",post->filhos->n_elem);
	for(i=0; i < post->filhos->n_elem; i++){
		post2 = get_ele_index_STACKPOST(post->filhos,i);
		if (post2 != NULL){

			data = getDateP(post2);
			if (data != NULL){
				printf("Data-> D:%d M:%d A:%d || ID:%ld \n",get_MYday(data),get_MYmonth(data),get_MYyear(data), getIdP(post2));
				free_MYdate(data);
			}
		}
	}
	printf("I=%d\n",i);
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
		if(strcmp(post->tags[i],tag) == 0 )
			return 1;
		}
	return 0;
}

/**
 * @date 			29 Mar 2018
 * @brief 			Função que processa a string correspondente ao valor Creation date e a transforma numa struct mydate.
 * @param value		A string com o valor CreationDate.
 */
MYDATE xmlToMYDATE(char * value) {
	int yy, mm, dd;
	sscanf(value, "%d-%d-%dT", &yy, &mm ,&dd);

	MYDATE date = createMYDate(dd, mm, yy);

	return date;
}




/**
 * @date 			29 Mar 2018
 * @brief 			Função que processa a string correspondente ao valor Tags a transforma num array de strings.
 * @param value		A string com o valor Tags.
 */
char ** xmlToStringArray(char * value) {

	int i, n = strlen(value);
	int tag_counter = 0;

	for(i = 0; i < n; i++)									//Conta o número de tags
		if(value[i] == '<')
			tag_counter++;

	if(tag_counter == 0)									//Retorna NULL se não há tags
		return NULL;

	char ** arr = malloc((tag_counter + 1)*sizeof(char *));	//Aloca memória para o numero de apontadores necessários para as tags.

	int j = 0, k = 0;
	int starts[tag_counter];
	char format[10];

	for(i = 0; i < n; i++) {								//Percrre a string value que contém as tags
		if(value[i] == '<') {								//Se for  início de outra tag, dá reset ao contador de tamanho
			j = 0;											//regista o início desta tag
			starts[k] = i + 1;
		}
		else if (value[i] == '>') {							//Se for o fim de uma tag
			arr[k] = malloc((sizeof(char) + 1)*j);			//Aloca a memória necessária para a mesma
			sprintf(format, "%%%ds", j);					//Regista o formato auxiliar ao sscanf
			sscanf(&value[starts[k]], format, arr[k]);		//Copia a tag para a string do array
			arr[k][j] = '\0';								//Sinaliza o final da string de cada tag com EOF.
			k++;											//Incrementa o índice do array de strings
		}
		else
			j++;											//Incrementa o registo do tamanho da tag atual
	}

	arr[k] = NULL;											//O último apontador deste array aponta para NULL

	return arr;
}


/**
 * @date 			25 Mar 2018
 * @brief 			Função que copia informação de um nodo da estrutura do libxml2 para o análogo da nossa estrutura.
 * @param post		O apontador da nossa estrutura.
 * @param xml 		O apontador da estrutura resultante do parsing do ficheiro xml.
 * @param doc		O apontador para o documento xml. (libxml2)
 * @param treeid	O apontador para a àrvore de posts ordenada por id.
 * @param treeusers O apontador para a árvore de users.
 */
void xmltoMYPOST(MYPOST post, xmlNodePtr xml, xmlDocPtr doc, TREE treeid, TREE treeusers) {
	xmlAttrPtr cur;

	char flag[12] = {0};	//flags para não estar constantemente a chamar a strcmp()
	char * value;
	char ** arr;
	MYDATE date;
	MYPOST parent = NULL;
	long l;

	for(cur = xml->properties; cur; cur = cur->next) {
				value = (char *) xmlNodeListGetString(doc, cur->children, 1);

				if(!flag[0] && strcmp((char *) cur->name, "Id") == 0) {
					setIdP(post, atol(value));
					flag[0] = 1;
					free(value);
					continue;
				}

				if(!flag[1] && strcmp((char *) cur->name, "PostTypeId") == 0) {
					setPostTypeIdP(post, atoi(value));
					flag[1] = 1;
					free(value);
					continue;

				}

				if(!flag[2] && strcmp((char *) cur->name, "ParentId") == 0) {
					l = atol(value);
					parent = search_POSTID_internal(treeid, l);
					setPIdP(post, l);
					flag[2] = 1;
					free(value);
					continue;
				}

				if(!flag[3] && strcmp((char *) cur->name, "CreationDate") == 0) {
					date = xmlToMYDATE(value);
					setDateP(post, date);
					flag[3] = 1;
					free(value);
					free_MYdate(date);
					continue;
				}


				if(!flag[4] && strcmp((char *) cur->name, "Score") == 0) {
					setScoreP(post, atoi(value));
					flag[4] = 1;
					free(value);
					continue;
				}

				if(!flag[5] && strcmp((char *) cur->name, "OwnerUserId") == 0) {
					l = atol(value);
					setOwnerIdP(post, l);
					flag[5] = 1;
					free(value);
					continue;
				}

				if(!flag[6] && strcmp((char *) cur->name, "OwnerDisplayName") == 0) {
					setOwnerNameP(post, value);
					flag[6] = 1;
					free(value);
					continue;
				}

				if(!flag[7] && strcmp((char *) cur->name, "Title") == 0) {
					setTitleP(post, value);
					flag[7] = 1;
					free(value);
					continue;
				}

				if(!flag[8] && strcmp((char *) cur->name, "Tags") == 0) {
					arr = xmlToStringArray(value);
					setTagsP(post, arr);
					flag[8] = 1;
					free(value);
					free_StringArray(arr);
					continue;
				}

				if(!flag[9] && strcmp((char *) cur->name, "AnswerCount") == 0) {
					setAnswersP(post, atoi(value));
					flag[9] = 1;
					free(value);
					continue;
				}

				if(!flag[10] && strcmp((char *) cur->name, "CommentCount") == 0) {
					setCommentsP(post, atoi(value));
					flag[10] = 1;
					free(value);
					continue;
				}

				if(!flag[11] && strcmp((char *) cur->name, "FavoriteCount") == 0) {
					setFavsP(post, atoi(value));
					flag[11] = 1;
					free(value);
					continue;
				}

				free(value);
	}

	if(parent)
		setFilhosNoPost(parent,post);

}
