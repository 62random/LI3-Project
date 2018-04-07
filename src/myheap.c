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

void swap(GEN * v,int i, int d){
	long aux1 = v[i].key;
	long aux2 = v[i].data;

	v[i].key = v[d].key;
	v[i].data = v[d].data;

	v[d].key = aux1;
	v[d].data = aux2;
}

HEAP initHEAP(int size){
	HEAP aux = malloc(sizeof(struct heap));
	aux->size = size;
	aux->n_elem = 0;
	aux->array = malloc(sizeof(struct generico));

	return aux;
}

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

HEAP pop (HEAP h, long * key, long * data){
	if (h->n_elem > 0){
		*key =h->array[0].key;
		*data = h->array[0].data;
		bubble_down(&h);
	}
	return h;
}
