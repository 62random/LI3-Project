#include "mytree.h"

#define MAX(a,b) a > b ? a : b;
#define MAX_SIZE 40

struct AVBin {
    int altura;
    void * key;
	void * data;
    struct AVBin * esq, * dir;
};

struct tree{
    AVL arv;
    int nnodes;
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

TREE insere_tree(TREE gl, void * key, void * data){

    AVL queue[MAX_SIZE];
    AVL a = gl->arv;

    int idx = 0;
    queue[idx++] = NULL;

    if (!a){
        a = create_new_node(key,data);
    }
    else{
        while(1){
            if ((gl->f_compare(a->key,key)>0)){
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

}

/**
 * @brief			Função cria a estrutura que contêm a árvore.
 * @param			Apontador para a função de comparação.
 * @param			Apontador para a função que dá free à key.
 * @param			Apontador para a função que dá free à data.
*/

TREE createTREE(void * f_compare,void * destroy_key,void * destroy_data){
    TREE a = malloc(sizeof(struct tree));
    a->nnodes = 0;
    a->heigth = 0;
    a->arv = NULL;
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
		destroy_key(a->key);
		destroy_data(a->data);
		freeAVL(a->esq,destroy_key,destroy_data);
		freeAVL(a->dir,destroy_key,destroy_data);
		free(a);
	}
};



/**
 * @brief			Função liberta a memória referente às chaves de uma AVL.
 * @param			Apontador para a AVL.
 * @param			Apontador para a função que destroi a key.
*/
static void freeAVL_keyOnly(AVL a,void (*destroy_key)(void *)){
	if (a){
		destroy_key(a->key);
		freeAVL_keyOnly(a->esq,destroy_key);
		freeAVL_keyOnly(a->dir,destroy_key);
		free(a);
	}
};

/**
 * @brief			Função liberta a memória referente aos dados de uma AVL, quando a sua chave está contida neles.
 * @param			Apontador para a AVL.
 * @param			Apontador para a função que destroi os dados.
*/
static void freeAVL_dataOnly(AVL a,void (*destroy_data)(void *)){
	if (a){
		destroy_data(a->data);
		freeAVL_dataOnly(a->esq,destroy_data);
		freeAVL_dataOnly(a->dir,destroy_data);
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
 * @brief			Função liberta a memória das estruturas TREE dos posts.
 * @param			Apontador para a tree ordenada por id.
 * @param			Apontador para a tree ordenada por data de criação.
*/

void freeTREES_POSTS(TREE postTreeId, TREE postTreeData) {
	if(postTreeData) {
		freeAVL_dataOnly(postTreeData->arv, postTreeData->destroy_data);
		free(postTreeData);
	}

	if(postTreeId) {
		freeAVL_keyOnly(postTreeId->arv, postTreeId->destroy_key);
		free(postTreeId);
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
 *@brief			Função que testa as propriedas da tree.
 *@param			Estrutura que contém a árvore.
*/

int test_TREE_PROP(TREE tree){
	int nodos,alturas,procura,balanceada;
	nodos = tree->nnodes == count_nodes(tree->arv);
	balanceada = isBalanced(tree->arv);
	alturas = check_altura(tree->arv);
	procura = isSearch(tree->arv,tree);


	return nodos && balanceada && alturas && procura;
}
