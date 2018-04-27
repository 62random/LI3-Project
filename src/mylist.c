#include <stdlib.h>
#include <stdio.h>
#include "mylist.h"
#include "list.h"


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
 * @param f_comp	Apontador para a função que compara.
 * @param dest_key	Apontador para a função que dá free à key.
 * @param dest_data	Apontador para a função que dá free à data.
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
 * @param r			Apontador para a estrutura da lista.
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
 * @param key		Apontador para a chave a inserir.
 * @param data 		Apontador para a data a inserir.
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
 * @param key		Apontador para a chave a procurar.
 * @param pai		Apontador a lista a procurar.
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
 * @brief			Função que procura um elemento na lista e retorna apontador para os seus dados.
 * @param key		Apontador para a chave a procurar.
 * @param pai		Apontador a lista a procurar.
*/

void * search_list_data(MYLIST pai,void * key){
	LList aux = pai->lista;
	void * r = NULL;
	while(aux && (r == NULL)){
		if (pai->f_compare(aux->key,key))
			r = &(aux->data);
		aux = aux->next;
	}

	return r;
}

/**
 * @brief			Função que insere um novo elemento na lista com comparador.
 * @param r 		Apontador para a lista.
 * @param key		Apontador para a chave a inserir.
 * @param data		Apontador para a data a inserir.
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
		if (percorre && !(r->f_compare(percorre->key,key))){
			r->destroy_key(key);
			return r;
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
 * @param r 		Apontador para a lista.
 * @param key		Apontador para a chave a inserir.
 * @param data		Apontador para a data a inserir.
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
 * @param r 		Apontador para a lista.
 * @param key		Apontador para a chave a inserir.
 * @param data		Apontador para a data a inserir.
*/

MYLIST 	insere_list	(MYLIST r,void * key,void * data){
	if (r->f_compare != NULL)
		r = insere_with_comp(r,key,data);
	else r = insere_with_no_comp(r,key,data);

	return r;
}

/**
 * @brief			Função devolve a data da caixa de uma lista.
 * @param r			Caixa de onde se vai tirar o elemento.
*/

void * getElemente_LList(LList r){
	if (r){
		return r->data;
	}
	return NULL;
}

/**
 * @brief			Função devolve a data da caixa de uma lista.
 * @param r 		Caixa de onde se vai tirar o elemento.
*/

LList getNext_LList(LList r){
	if (r){
		return r->next;
	}
	return NULL;
}

/**
 * @brief			Função a lista dentro do MYLIST.
 * @param r			Caixa inicial.
*/

LList getFirst_BOX(MYLIST r){
	if (r)
		return r->lista;
	return NULL;
}

/**
 * @brief			Função que retorna o número de elementos na lista.
 * @param r			Lista.
*/

int get_NUM_ele(MYLIST r){
	if (r) return r->num_elementos;
	return 0;
}

/**
 * @brief			Função que retorna a key de uma box.
 * @param	r		Box.
*/

void * get_key_box(LList aux){
	if (aux)
		return aux->key;
	return NULL;
}

/**
 * @brief			Função concateneia duas listas.
 * @param r1		Lista 1.
 * @param r2		Lista 2.
*/

MYLIST concat_LIST(MYLIST r1, MYLIST r2){
	LList aux;
	if (r1 != NULL && r2 != NULL){
		aux = r2->lista;

		while(aux && aux->next != NULL){
			aux = aux->next;
		}
		if (aux != NULL){
			aux->next = r1->lista;
			r1->lista = r2->lista;
		}

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
 * @param r			Lista 1.
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

/**
 * @brief			Função que dá reverse a uma lista.
 * @param l			Lista.
*/


MYLIST reverse(MYLIST l){
	if (l){
		LList aux1 = l->lista;
		LList aux2,final = NULL;
		while(aux1){
			aux2 = aux1;
			aux2->next = final;
			final = aux2;
			aux1 = aux1->next;
		}
		l->lista = final;
	}
	return l;
}



/**
 * @brief			Função percorre uma lista e aplica a cada nodo uma função.
 * @param	lista	Lista a ser percorrida.
 * @param	f_box	Função a ser aplicada (cujo o primeiro argumento é o nodo a que ela é aplicada).
 * @param	data1	Segundo argumento da função a ser aplicada.
 * @param	data2	Terceiro argumento da função a ser aplicada.
 * @param	data3	Quarto argumento da função a ser aplicada.

*/
void trans_list(MYLIST lista, void (*f_box)(void *, void *, void *, void *), void * data1, void * data2, void * data3){
	if(lista == NULL)
		return;

	LList aux = lista->lista;

	while(aux){
		f_box(aux, data1, data2, data3);
		aux = aux->next;
	}

}
