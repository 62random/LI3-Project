#include "myheap.h"


struct generico {
	long key;
	long data;
};

struct heap{
	int size;
	int n_elem;
	GEN * array;
};

struct stack{
	long size;
	long n_elem;
	long * array;
};

/**
 * @brief			Função troca 2 elementos no array.
 * @param			Posição do 1 elemento.
 * @param			Posição do 2 elemento.
*/

void swap(GEN * v,int i, int d){
	long aux1 = v[i].key;
	long aux2 = v[i].data;

	v[i].key = v[d].key;
	v[i].data = v[d].data;

	v[d].key = aux1;
	v[d].data = aux2;
}

/**
 * @brief			Função que inicializa um heap.
 * @param			Tamanho original da heap.
*/


HEAP initHEAP(long size){
	HEAP aux = malloc(sizeof(struct heap));
	aux->size = size;
	aux->n_elem = 0;
	aux->array = malloc(sizeof(struct generico));

	return aux;
}

/**
 * @brief			Função que coloca o último elemento adicionado na sua posição correta.
 * @param			Apontador para a heap.
*/

void bubble_up(HEAP * main){
	HEAP h = * main;
	int pai,i;
	if (h->n_elem >= 2){
		i = h->n_elem -1;
		pai = i / 2;
		while(h->array[i].key>h->array[pai].key && i > 0){
			swap(h->array,pai,i);
			i = pai;
			pai = i / 2;
		}
	}
	*main = h;
}

/**
 * @brief			Função que realiza as operações necessárias depois de se retirar um elemento.
 * @param			Apontador para a heap.
*/

void bubble_down(HEAP * main){
	HEAP h = * main;
	int fd,fe,i = 0;
	if (h->n_elem >= 2){
		h->n_elem--;
		h->array[i] = h->array[h->n_elem];
		fd = 2*i + 2;
		fe = 2*i + 1;

		while(i <= h->n_elem && fd <= h->n_elem && fe <= h->n_elem && (h->array[i].key < h->array[fe].key || h->array[i].key < h->array[fd].key)){
			if (h->array[fe].key > h->array[fd].key){
				swap(h->array,i,fe);
				i = fe;
			}
			else{
				swap(h->array,i,fd);
				i = fd;
			}
			fe = 2*i + 1;
			fd = 2*i + 2;
		}
	}
	*main = h;
}

/**
 * @brief			Função que insere um novo elemento na heap.
 * @param			Heap.
 * @param			Valor da key a inserir.
 * @param			Valor da data a inserir.
*/

HEAP insere(HEAP h, long key, long data){
	if (h->n_elem > h->size){
		h->array = realloc(h->array,h->size*2);
		h->size *= 2;
	}
	h->array[h->n_elem].key = key;
	h->array[h->n_elem++].data = data;
	bubble_up(&h);

	return h;
}

/**
 * @brief			Função que retira um elemento na heap.
 * @param			Heap.
 * @param			Apontador para o sítio onde a key fica guardada.
 * @param			Apontador para o sítio onde a data fica guardada.
*/

HEAP pop (HEAP h, long * key, long * data){
	if (h->n_elem > 0){
		*key =h->array[0].key;
		*data = h->array[0].data;
		bubble_down(&h);
	}
	return h;
}

/**
 * @brief			Função dá free à heap.
 * @param			Heap.
*/

void freeMYHEAP(HEAP h){
	if (h){
		free(h->array);
		free(h);
	}
}

//STACK initSTACK(long size)
