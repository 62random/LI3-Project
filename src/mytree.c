#include "mytree.h"

#define MAX(a,b) a > b ? a : b;
#define MAX_SIZE 40

struct AVBin {
    int altura;
    void * key;
	void * data;
    struct AVBin * esq, * dir;
};

typedef struct AVBin * AVL;

struct tree{
    AVL arv;
    long nnodes;
	void * (*replace_fun)(void *,void *);
    int (*f_compare)(void *,void *);
	void (*destroy_key)(void *);
	void (*destroy_data)(void *);
    int heigth;
};

/**
 * @brief			Função calcula a altura de um novo.
 * @param			Apontador para a árvore.
*/

static int altura(AVL a) {
    return a ? a-> altura : 0;
}

/**
 * @brief			Função calcula o balanço de um novo.
 * @param			Apontador para a árvore.
*/

static int balanceDEEP(AVL a) {
    int balance = 0;
    if (a){
        balance = altura(a->dir) - altura(a->esq);
    }

    return balance;
}

/**
 * @brief			Função calcula a altura de uma árvore.
 * @param			Apontador para a árvore.
*/

static int cal_altura(AVL a){
    int h = 0;
    int h1, h2;
    if(a){
        h1 = cal_altura(a->esq);
        h2 = cal_altura(a->dir);

        h = h1 > h2 ? h1 + 1 : h2 +1;
    }

    return h;
}

/**
 * @brief			Função verifica se a árvore é balanceada.
 * @param			Apontador para a árvore.
*/

static int isBalanced(AVL a){
    int r = 1;
    int b;
    if(a){
        b = cal_altura(a->dir) - cal_altura(a->esq);
        if ((b >= -1) && (b <= 1))
            r = isBalanced(a->esq) && isBalanced(a->dir);
        else r = 0;
    }

    return r;
}

/**
 * @brief			Função verifica se a arvore da estrutura é balanceada.
 * @param			Apontador para a estrutura.
*/

int TREE_balance(TREE tre){
	return isBalanced(tre->arv);
}

/**
 * @brief			Função efetua uma rotação para a direita da árvore.
 * @param			Apontador para a árvore.
*/

static AVL rotate_rigth(AVL a){

    int ha_r, ha_l;

    AVL aux = a -> esq;
    a->esq = aux -> dir;
    aux -> dir = a;


    ha_r = altura(a->dir);
    ha_l = altura(a->esq);
    a->altura = ha_r > ha_l ? ha_r + 1 : ha_l + 1;

    ha_l = altura(aux->esq);
    ha_r = a->altura;
    aux->altura = ha_r > ha_l ? ha_r + 1 : ha_l + 1;

    return aux;
}

/**
 * @brief			Função efetua uma rotação para a esquerda da árvore.
 * @param			Apontador para a árvore.
*/

static AVL rotate_left(AVL a){

    int ha_r, ha_l;

    AVL aux = a->dir;
    a->dir = aux -> esq;
    aux->esq = a;

    ha_l = altura(a->esq);
    ha_r = altura(a->dir);
    a->altura = ha_r > ha_l ? ha_r + 1 : ha_l + 1;

    ha_r = altura(aux->dir);
    ha_l = a->altura;
    aux->altura = ha_r > ha_l ? ha_r + 1 : ha_l + 1;


    return aux;
}

/**
 * @brief			Função efetua o balanceamento da árvore.
 * @param			Apontador para a árvore.
*/

static AVL balance(AVL a){

    int hd, hl;

    hd = altura(a->dir);
    hl = altura(a->esq);

    int bal = hd -hl;


    if (bal == -2){
        if (balanceDEEP(a->esq) == 1)
            a->esq = rotate_left(a->esq);
        a = rotate_rigth(a);
    }
    if (bal == 2){
        if (balanceDEEP(a->dir) == -1)
            a->dir = rotate_rigth(a->dir);
        a = rotate_left(a);
    }

    return a;
}

/**
 * @brief			Função que implementa a nova altura de um dado nodo.
 * @param			Apontador para a árvore.
*/

static void implementa_alt(AVL * a){

    int hl,hr;

    AVL aux = * a;
    hr = altura(aux->dir);
    hl = altura(aux->esq);
    aux->altura = hr > hl ? hr + 1 : hl + 1;

}

/**
 * @brief			Função que cria um novo nodo.
 * @param			Apontador a key.
 * @param			Apontador para a data.
*/

static AVL create_new_node(void * key, void * data){
    AVL a;
    a = malloc(sizeof(struct AVBin));
    a -> altura = 1;
    a -> key = key;
	a -> data = data;
    a -> esq = NULL;
    a -> dir = NULL;

    return a;
}

/**
 * @brief			Função conta o número de nodos da árvore.
 * @param			Apontador para a árvore.
*/

static int count_nodes(AVL a){
    int r = 0;
    if (a){
        r = 1 + count_nodes(a->esq) + count_nodes(a->dir);
    }

    return r;
}

/**
 * @brief			Função insere um elemento na árvore.
 * @param			Apontador para a estrutura que guarda a árvore.
 * @param			Apontador para a key a inserir.
 * @param			Apontador para a data a inserir.
*/
/*
TREE insere_tree(TREE gl, void * key, void * data){

    AVL queue[MAX_SIZE];
    AVL a = gl->arv;
	int replace = 0;
	int side;

    int idx = 0;
    queue[idx++] = NULL;

    if (!a){
        a = create_new_node(key,data);
    }
    else{
        while(1){
			side = (gl->f_compare(a->key,key);
            if (side > 0){
                if (a->dir){
                    queue[idx++] = a;
                    a = a->dir;
                }
                else {
                    a->dir = create_new_node(key,data);
                    break;
                }
            }
            else {
                if (a->esq){
                    queue[idx++] = a;
                    a = a->esq;
                }
                else{
                    a->esq = create_new_node(key,data);
                    break;
                }
            }
        }

        AVL pai;
        int check_side, balan;

        while(1){
            pai = queue[--idx];
            check_side = ((!pai) ||pai->esq == a);
            implementa_alt(&a);
            balan = altura(a->dir) - altura(a->esq);
            if (balan < -1 || balan > 1){
                a = balance(a);
                if (!pai)
                    break;
                else if (check_side)
                    pai->esq = a;
                else pai->dir = a;
            }
            if(!pai)
                break;
            a = pai;
        }
    }

    gl->nnodes++;
    gl->arv = a;

    return gl;

}*/

TREE insere_tree(TREE gl, void * key, void * data){

    AVL queue[MAX_SIZE];
    AVL a = gl->arv;
	int replace = 0;
	int side;

    int idx = 0;
    queue[idx++] = NULL;

    if (!a){
        a = create_new_node(key,data);
		gl->arv = a;
    }
    else{
        while(1){
			side = (gl->f_compare(a->key,key));
			if (side == 0){
				if (gl->replace_fun != NULL){
					replace = 1;
					a->data=gl->replace_fun(a->data,data);
					if (gl->destroy_key != NULL)
						gl->destroy_key(key);
					break;
				}
			}
            if (side > 0){
                if (a->dir){
                    queue[idx++] = a;
                    a = a->dir;
                }
                else {
                    a->dir = create_new_node(key,data);
                    break;
                }
            }
            else {
                if (a->esq){
                    queue[idx++] = a;
                    a = a->esq;
                }
                else{
                    a->esq = create_new_node(key,data);
                    break;
                }
            }
        }

        AVL pai;
        int check_side, balan;
		if (replace == 0){
        	while(1){
            	pai = queue[--idx];
            	check_side = ((!pai) ||pai->esq == a);
            	implementa_alt(&a);
            	balan = altura(a->dir) - altura(a->esq);
            	if (balan < -1 || balan > 1){
                	a = balance(a);
                	if (!pai)
                    	break;
                	else if (check_side)
                    	pai->esq = a;
                	else pai->dir = a;
            	}
            	if(!pai)
                	break;
            	a = pai;
        	}
			gl->arv = a;
		}
    }
	gl->nnodes++;

    return gl;

}

/**
 * @brief			Função cria a estrutura que contêm a árvore.
 * @param			Apontador para a função de comparação.
 * @param			Apontador para a função que dá free à key.
 * @param			Apontador para a função que dá free à data.
*/

TREE createTREE(void * f_compare,void * destroy_key,void * destroy_data,void * replace){
    TREE a = malloc(sizeof(struct tree));
    a->nnodes = 0;
    a->heigth = 0;
    a->arv = NULL;
	a->replace_fun = replace;
    a->f_compare = f_compare;
	a->destroy_key = destroy_key;
	a->destroy_data = destroy_data;

    return a;
}

/**
 * @brief			Função liberta a memória de uma AVL.
 * @param			Apontador para a AVL.
 * @param			Apontador para a função que destroi a key.
 * @param			Apontador para a função que destroi a data.
*/


static void freeAVL(AVL a,void (*destroy_key)(void *),void (*destroy_data)(void *)){
	if (a){
		if (destroy_key != NULL)
			destroy_key(a->key);
		if (destroy_data != NULL)
			destroy_data(a->data);
		freeAVL(a->esq,destroy_key,destroy_data);
		freeAVL(a->dir,destroy_key,destroy_data);
		free(a);
	}
};





/**
 * @brief			Função liberta a memória da estrutura Tree.
 * @param			Apontador para a tree.
*/

void freeTREE_AVL(TREE tre){
	if(tre){
		freeAVL(tre->arv,tre->destroy_key,tre->destroy_data);
		free(tre);
	}
}





/**
 *@brief			Função que procura um elemento na árvore.
 *@param			Estrutura que contém a árvore.
 *@param			Apontador para a key a procurar.
*/

void * search_AVL(TREE tree, void * key,int * valid){
	AVL node = tree->arv;
	int result = 0;

	while((!result) && node){
		if (tree->f_compare(node->key,key) == 0){
			result = 1;
		}
		else if (tree->f_compare(node->key,key) == 1)
			node = node->dir;
		else node = node ->esq;
	}
	*valid = result;
	if (result)
		return node->data;
	return NULL;
}

/**
 *@brief			Função que testa se os nodos da AVL têm as alturas direitas
 *@param			Apontador para a AVL.
*/

static int check_altura(AVL a){
    int r = 1;
    int b;
    if (a){
        b = cal_altura(a);
        if (a->altura == b){
            r = cal_altura(a->esq) && cal_altura(a->dir);
        }
    }

    return r;
}

/**
 *@brief			Função que testa a AVL é de procura.
 *@param			Apontador para a AVL.
 *@param			Apontador para a estrutura com a função de comparação.
*/

static int isSearch(AVL a,TREE tree){
    int r = 1;
    if (a){
        if (a->dir == NULL && a->esq == NULL)
            r = 1;
        else if (a->dir == NULL && (tree->f_compare(a->key,a->esq->key) < 0))
            r = isSearch(a->esq,tree);
        else if (a->esq == NULL && (tree->f_compare(a->key,a->dir->key) > 0))
            r = isSearch(a->dir,tree);
        else if ((tree->f_compare(a->key,a->dir->key) > 0) && (tree->f_compare(a->key,a->esq->key) < 0))
            r = isSearch(a->dir,tree) && isSearch(a->esq,tree);
        else r = 0;
    }
    return r;
}

/**
 *@brief			Função que vai ser aplicada a todos os nodos.
 *@param			Apontador para a arvore.
 *@param			Função a aplicar a cada nodo.
 *@param			Apontador a passar à função a aplicar.
*/

static void all_nodes_trans(AVL aux,void (*f_nodo)(void *,void *),void * data1){
	if (aux){
		f_nodo(aux->data,data1);
		all_nodes_trans(aux->esq,f_nodo,data1);
		all_nodes_trans(aux->dir,f_nodo,data1);
	}
}

/**
 *@brief			Função que vai ser aplicada a todos os nodos.
 *@param			Apontador para a estrutura que contem a AVL.
 *@param			Função a aplicar a cada nodo.
 *@param			Apontador a passar à função a aplicar.
*/

void all_nodes_TREE(TREE e,void (*f_nodo)(void *,void *),void * data1){
	if (f_nodo != NULL)
		all_nodes_trans(e->arv,f_nodo,data1);
}

/**
 *@brief			Função que conta o número de nodos que satisfazem uma condição.
 *@param			Apontador para a AVL.
 *@param			Apontador para a data1 a comparar.
 *@param			Apontador para a data2 a comparar.
 *@param			Apontador para a função que compara.
 *@param			Função a aplicar em todos os nodos.
 *@param			Aparametro 1 a passar à função que aplica nos nodos.
 *@param			Aparametro 2 a passar à função que aplica nos nodos.
*/

static void all_nodes_With_key_Condition(AVL aux,void * inicio,void * fim,int (*f_compare)(void *,void *),void (*f_nodo)(void *,void *,void *),void * data3,void * data4){
	int a1,a2;
	if(aux){
		a1 =f_compare(inicio,aux->key);
		a2 =f_compare(fim,aux->key);
		if ((a1 > 0 && a2 < 0) || (a1==0) || (a2==0)){
			f_nodo(aux->data,data3,data4);
			all_nodes_With_key_Condition(aux->esq,inicio,fim,f_compare,f_nodo,data3,data4);
			all_nodes_With_key_Condition(aux->dir,inicio,fim,f_compare,f_nodo,data3,data4);
		}
		else if (a1 > 0)
			all_nodes_With_key_Condition(aux->esq,inicio,fim,f_compare,f_nodo,data3,data4);
		else if (a2 < 0)
			all_nodes_With_key_Condition(aux->dir,inicio,fim,f_compare,f_nodo,data3,data4);
	}
}

/**
 *@brief			Função que conta o número de nodos que satisfazem uma condição.
 *@param			Apontador para a estrutura que contém a árvore.
 *@param			Apontador para a data1 a comparar.
 *@param			Apontador para a data2 a comparar.
 *@param			Função a aplicar em todos os nodos.
 *@param			Aparametro 1 a passar à função que aplica nos nodos.
 *@param			Aparametro 2 a passar à função que aplica nos nodos.
*/

void all_nodes_With_Condition(TREE tree, void * data1, void * data2,void (*f_nodo)(void *,void *,void *),void * data3,void * data4){
	all_nodes_With_key_Condition(tree->arv,data1,data2,tree->f_compare,f_nodo,data3,data4);
}


/**
 *@brief			Função que testa as propriedas da tree.
 *@param			Estrutura que contém a árvore.
*/

int test_TREE_PROP(TREE tree){
	int nodos,alturas,procura,balanceada;
	nodos = tree->nnodes == count_nodes(tree->arv);
	balanceada = isBalanced(tree->arv);
	alturas = check_altura(tree->arv);
	procura = isSearch(tree->arv,tree);


	//return nodos && balanceada && alturas && procura;
	return balanceada && alturas && procura;
}

/**
 *@brief			Função que devolve o número de nodos da árvore.
 *@param			Estrutura que contém a árvore.
*/

long NUM_nodes(TREE t){
	return t->nnodes;
}

/**
 *@brief			Função que faz uma travessia inorder na árvore.
 *@param			Apontador para a arvore.
 *@param			Função a aplicar a cada nodo.
 *@param			Apontador a passar à função a aplicar.
*/

static void trans_inorder(AVL aux,void (*f_nodo)(void *,void *),void * data1){
	if (aux){
		trans_inorder(aux->esq,f_nodo,data1);
		f_nodo(aux->data,data1);
		trans_inorder(aux->dir,f_nodo,data1);
	}
}

/**
 *@brief			Função que faz uma travessia postorder na árvore.
 *@param			Apontador para a arvore.
 *@param			Função a aplicar a cada nodo.
 *@param			Apontador a passar à função a aplicar.
*/

static void trans_posorder(AVL aux,void (*f_nodo)(void *,void *),void * data1){
	if (aux){
		trans_posorder(aux->esq,f_nodo,data1);
		trans_posorder(aux->dir,f_nodo,data1);
		f_nodo(aux->data,data1);
	}
}

/**
 *@brief			Função que faz uma travessia preorder na árvore.
 *@param			Apontador para a arvore.
 *@param			Função a aplicar a cada nodo.
 *@param			Apontador a passar à função a aplicar.
*/

static void trans_preorder(AVL aux,void (*f_nodo)(void *,void *),void * data1){
	if (aux){
		f_nodo(aux->data,data1);
		trans_preorder(aux->esq,f_nodo,data1);
		trans_preorder(aux->dir,f_nodo,data1);
	}
}

/**
 *@brief			Função que faz uma travessia na árvore.
 *@param			Apontador para a estrutura arvore.
 *@param			Função a aplicar a cada nodo.
 *@param			Apontador a passar à função a aplicar.
 *@param			Tipo de travessia.
*/


void trans_tree(TREE e,void (*f_nodo)(void *,void *),void * data1,int travessia){
	if (!e)
		return;
	if (travessia == 1)
		trans_posorder(e->arv,f_nodo,data1);
	else if (travessia == 2)
		trans_inorder(e->arv,f_nodo,data1);
	else if (travessia == 3)
		trans_preorder(e->arv,f_nodo,data1);
}
