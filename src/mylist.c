#include <stdlib.h>
#include <stdio.h>

/**
 * @brief			Função inicializa a estrutura da lista.
 * @param			Apontador para a função que compara.
 * @param			Apontador para a função que dá free à key.
  * @param			Apontador para a função que dá free à data.
*/

MYLIST init_MYLIST(void * f_comp,void * dest_key,void * dest_data){
	MYLIST head = malloc(sizeof(struct mylist));
	head->f_compare = f_comp;
	head->destroy_key = dest_key;
	head->destroy_data = dest_data;
	head->lista = NULL;

	return head;
}

/**
 * @brief			Função liberta a memória da lista.
 * @param			Apontador para a estrutura da lista.
*/

void free_MYLIST(MYLIST r){
	LList aux = r->lista;
	while(aux){
		r->destroy_key(aux->key);
		r->destroy_data(aux->data);
		free(aux);
		aux = aux ->next;
	}
	free(r);
}

/**
 * @brief			Função cria uma caixa para a lista.
 * @param			Apontador para a chave a inserir.
 * @param			Apontador para a data a inserir.
*/

LList create_box(void * key,void * data){
	LList novo = malloc(sizeof(struct lligada));
	novo->key = key;
	novo->data = data;
	novo->next = NULL;

	return novo;
}

/**
 * @brief			Função que procura um elemento na lista.
 * @param			Apontador para a chave a procurar.
*/

int search_list(MYLIST pai,void * key){
	LList aux = pai->lista;
	int r = 0;
	while(aux && (r == 0)){
		if (pai->f_compare(aux->key,key))
			r = 1;
		aux = aux->next;
	}

	return r;
}

/**
 * @brief			Função que insere um novo elemento na lista.
 * @param			Apontador para a chave a inserir.
 * @param			Apontador para a data a inserir.
*/

MYLIST insere_list(MYLIST r,void * key,void * data){
	LList ant = NULL,novo;
	LList percorre = r->lista, pai = r->lista;

	if (!pai){
		r->lista = create_box(key,data);
		return r;
	}
	else{
		while((percorre != NULL) && (r->f_compare(percorre->key,key))){
			ant = percorre;
			percorre = percorre->next;
		}
		novo = create_box(key,data);
		if (ant == NULL){
			novo->next = pai;
			pai = novo;
		}
		else{
			ant->next = novo;
			novo->next = percorre;
		}
	}
	r->lista = pai;

	return r;
}

/**
 * @brief			Função que imprime uma lista.
 * @param			Apontador para a lista.
*/

void print_List(LList r){
	long aux;
	while(r){
		aux = *((long * ) r->key);
		printf("%ld -> ",aux);
		r = r->next;
	}
}
