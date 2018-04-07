#include <stdlib.h>
#include <stdio.h>
#include "mylist.h"

struct llligada{
	void * key;
	void * data;
	struct llligada * next;
};

struct mylist{
	int (*f_compare)(void *,void *);
	void (*destroy_key)(void *);
	void (*destroy_data)(void *);
	int num_elementos;
	LList lista;
};

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
	head->num_elementos = 0;

	return head;
}

/**
 * @brief			Função liberta a memória da lista.
 * @param			Apontador para a estrutura da lista.
*/

void free_MYLIST(MYLIST r){
	if (r){
		LList aux2;
		LList aux = r->lista;
		while(aux){
			if (r->destroy_key != NULL)
				r->destroy_key(aux->key);
			if (r->destroy_data != NULL)
				r->destroy_data(aux->data);
			aux2 = aux;
			aux = aux ->next;
			free(aux2);
		}
		free(r);
	}
}

/**
 * @brief			Função cria uma caixa para a lista.
 * @param			Apontador para a chave a inserir.
 * @param			Apontador para a data a inserir.
*/

LList create_box(void * key,void * data){
	LList novo = malloc(sizeof(struct llligada));
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
 * @brief			Função que insere um novo elemento na lista com comparador.
 * @param			Apontador para a chave a inserir.
 * @param			Apontador para a data a inserir.
*/

static MYLIST insere_with_comp(MYLIST r,void * key,void * data){
	LList ant = NULL,novo;
	LList percorre = r->lista, pai = r->lista;

	if (!pai){
		r->lista = create_box(key,data);
		r->num_elementos++;
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
	r->num_elementos++;

	return r;
}

/**
 * @brief			Função que insere um novo elemento na lista sem comparador.
 * @param			Apontador para a chave a inserir.
 * @param			Apontador para a data a inserir.
*/

static MYLIST insere_with_no_comp(MYLIST r,void * key,void * data){
	LList pai = r->lista;
	LList novo;

	novo = create_box(key,data);
	novo->next = pai;

	r->lista = novo;
	r->num_elementos++;
	return r;
}

/**
 * @brief			Função que insere um novo elemento na lista.
 * @param			Apontador para a chave a inserir.
 * @param			Apontador para a data a inserir.
*/

MYLIST 	insere_list	(MYLIST r,void * key,void * data){
	if (r->f_compare != NULL)
		r = insere_with_comp(r,key,data);
	else r = insere_with_no_comp(r,key,data);

	return r;
}

/**
 * @brief			Função devolve a data da caixa de uma lista.
 * @param			Caixa de onde se vai tirar o elemento.
*/

void * getElemente_LList(LList r){
	if (r){
		return r->data;
	}
	return NULL;
}

/**
 * @brief			Função devolve a data da caixa de uma lista.
 * @param			Caixa de onde se vai tirar o elemento.
*/

LList getNext_LList(LList r){
	if (r){
		return r->next;
	}
	return NULL;
}

/**
 * @brief			Função a lista dentro do MYLIST.
 * @param			Caixa inicial.
*/

LList getFirst_BOX(MYLIST r){
	if (r)
		return r->lista;
	return NULL;
}

/**
 * @brief			Função que retorna o número de elementos na lista.
 * @param			Lista.
*/

int get_NUM_ele(MYLIST r){
	if (r) return r->num_elementos;
	return 0;
}

/**
 * @brief			Função que retorna a key de uma box.
 * @param			Box.
*/

void * get_key_box(LList aux){
	if (aux)
		return aux->key;
	return NULL;
}

/**
 * @brief			Função concateneia duas listas.
 * @param			Lista 1.
 * @param			Lista 2.
*/


MYLIST concat_LIST(MYLIST r1, MYLIST r2){
	LList aux,ant = NULL,pai;
	if (r1 != NULL && r2 != NULL){
		aux = r2->lista;
		pai = r1->lista;

		while(aux){
			ant = aux;
			aux = aux->next;
		}
		if (ant != NULL){
			ant->next = pai;
			pai = r2->lista;
		}
		r1->lista = pai;
		r1->num_elementos +=r2->num_elementos;
		free(r2);

		return r1;
	}
	if (!r1)
		return r2;
	if (!r2)
		return r1;
	return NULL;
}

/**
 * @brief			Função conta o número de elementos de uma lista.
 * @param			Lista 1.
*/

long count_ELE_MYLIST(MYLIST r){
	long i = 0;
	if(r){
		LList aux = r->lista;
		while(aux){
			i++;
			aux = aux->next;
		}
	}
	return i;
}
